/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * dat for the build host: Allegro 4 datafiles as Allegro 4's dat writes
 * them, and as allegro4.library reads them, built with build-host.sh on
 * this allegro4. Its own code, not Allegro's. README.md says what it takes
 * and what it leaves out.
 *
 *   dat [-a] [-k] [-t TYPE] [-bpp N] [-c0|-c1|-c2] [-s0|-s1|-s2] [-v] FILE.dat [FILES...]
 *   dat -l FILE.dat
 *
 * Each FILE is added as an object (one of the same NAME is replaced). With
 * no FILES the datafile is written again as it is (packed or stripped as
 * -c and -s say).
 */
#include <allegro.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int a4_write_font_object(PACKFILE *f, FONT *font);    /* a4_font.c, built with A4_WRITERS */

/* ---- bytes ------------------------------------------------------------------------------------ */

typedef struct { unsigned char *p; size_t n, cap; } buf;

static void die(const char *fmt, const char *a)
{
    fprintf(stderr, "dat: ");
    fprintf(stderr, fmt, a);
    fputc('\n', stderr);
    exit(1);
}

static void put(buf *b, const void *p, size_t n)
{
    if (!n) return;
    if (b->n + n > b->cap) {
        size_t c = b->cap ? b->cap : 4096;
        while (c < b->n + n) c *= 2;
        b->p = (unsigned char *)realloc(b->p, c);
        if (!b->p) die("out of memory%s", "");
        b->cap = c;
    }
    memcpy(b->p + b->n, p, n);
    b->n += n;
}
static void put8(buf *b, int v) { unsigned char c = (unsigned char)v; put(b, &c, 1); }
static void putm16(buf *b, int v) { put8(b, v >> 8); put8(b, v); }
static void puti16(buf *b, int v) { put8(b, v); put8(b, v >> 8); }
static void putm32(buf *b, long v) { put8(b, (int)(v >> 24)); put8(b, (int)(v >> 16)); put8(b, (int)(v >> 8)); put8(b, (int)v); }
static long getm32(const unsigned char *p)
{ return (long)(int32_t)(((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) | ((uint32_t)p[2] << 8) | p[3]); }

static int read_file(const char *name, buf *b)
{
    FILE *f = fopen(name, "rb");
    unsigned char tmp[65536];
    size_t n;
    if (!f) return -1;
    while ((n = fread(tmp, 1, sizeof(tmp), f)) > 0) put(b, tmp, n);
    fclose(f);
    return 0;
}

/* ---- Allegro's LZSS: a 4096-byte ring, matches of 3 to 18, flag bits from the lowest, 1 a literal -- */

#define N 4096
#define F 18
#define TH 2

static void lzss_decode(const unsigned char *s, size_t n, size_t want, buf *out)
{
    unsigned char ring[N + F];
    unsigned flags = 0;
    int r = N - F;
    size_t i = 0;
    memset(ring, 0, sizeof(ring));
    while (i < n && out->n < want) {
        flags >>= 1;
        if (!(flags & 256)) flags = s[i++] | 0xFF00u;
        if (flags & 1) {
            if (i >= n) break;
            ring[r] = s[i]; put8(out, s[i++]); r = (r + 1) & (N - 1);
        } else {
            int a, l, k;
            if (i + 1 >= n) break;
            a = s[i] | ((s[i + 1] & 0xF0) << 4);
            l = (s[i + 1] & 0x0F) + TH + 1;
            i += 2;
            for (k = 0; k < l && out->n < want; k++) {
                unsigned char c = ring[(a + k) & (N - 1)];
                put8(out, c); ring[r] = c; r = (r + 1) & (N - 1);
            }
        }
    }
}

/* the encoder: Okumura's binary trees, the LZSS Allegro's packer is */
static unsigned char text[N + F - 1];
static int match_pos, match_len, lson[N + 1], rson[N + 257], dad[N + 1];

static void tree_init(void)
{
    int i;
    for (i = N + 1; i <= N + 256; i++) rson[i] = N;
    for (i = 0; i < N; i++) dad[i] = N;
}

static void tree_insert(int r)
{
    int i, p, cmp = 1;
    unsigned char *key = &text[r];
    p = N + 1 + key[0];
    rson[r] = lson[r] = N;
    match_len = 0;
    for (;;) {
        if (cmp >= 0) {
            if (rson[p] != N) p = rson[p];
            else { rson[p] = r; dad[r] = p; return; }
        } else {
            if (lson[p] != N) p = lson[p];
            else { lson[p] = r; dad[r] = p; return; }
        }
        for (i = 1; i < F; i++) if ((cmp = key[i] - text[p + i]) != 0) break;
        if (i > match_len) {
            match_pos = p;
            if ((match_len = i) >= F) break;
        }
    }
    dad[r] = dad[p]; lson[r] = lson[p]; rson[r] = rson[p];
    dad[lson[p]] = r; dad[rson[p]] = r;
    if (rson[dad[p]] == p) rson[dad[p]] = r; else lson[dad[p]] = r;
    dad[p] = N;
}

static void tree_delete(int p)
{
    int q;
    if (dad[p] == N) return;
    if (rson[p] == N) q = lson[p];
    else if (lson[p] == N) q = rson[p];
    else {
        q = lson[p];
        if (rson[q] != N) {
            do q = rson[q]; while (rson[q] != N);
            rson[dad[q]] = lson[q]; dad[lson[q]] = dad[q];
            lson[q] = lson[p]; dad[lson[p]] = q;
        }
        rson[q] = rson[p]; dad[rson[p]] = q;
    }
    dad[q] = dad[p];
    if (rson[dad[p]] == p) rson[dad[p]] = q; else lson[dad[p]] = q;
    dad[p] = N;
}

static void lzss_encode(const unsigned char *in, size_t n, buf *out)
{
    unsigned char code[17], mask = 1;
    int i, c, len, r, s, last, cp = 1;
    size_t at = 0;
    if (!n) return;
    tree_init();
    code[0] = 0;
    s = 0; r = N - F;
    memset(text, 0, sizeof(text));
    for (len = 0; len < F && at < n; len++) text[r + len] = in[at++];
    for (i = 1; i <= F; i++) tree_insert(r - i);
    tree_insert(r);
    do {
        if (match_len > len) match_len = len;
        if (match_len <= TH) {
            match_len = 1;
            code[0] |= mask;
            code[cp++] = text[r];
        } else {
            code[cp++] = (unsigned char)match_pos;
            code[cp++] = (unsigned char)(((match_pos >> 4) & 0xF0) | (match_len - (TH + 1)));
        }
        if ((mask = (unsigned char)(mask << 1)) == 0) {
            put(out, code, (size_t)cp);
            code[0] = 0; cp = 1; mask = 1;
        }
        last = match_len;
        for (i = 0; i < last && at < n; i++) {
            c = in[at++];
            tree_delete(s);
            text[s] = (unsigned char)c;
            if (s < F - 1) text[s + N] = (unsigned char)c;
            s = (s + 1) & (N - 1); r = (r + 1) & (N - 1);
            tree_insert(r);
        }
        while (i++ < last) {
            tree_delete(s);
            s = (s + 1) & (N - 1); r = (r + 1) & (N - 1);
            if (--len) tree_insert(r);
        }
    } while (len > 0);
    if (cp > 1) put(out, code, (size_t)cp);
}

/* ---- a datafile in memory: each object's properties and its bytes, unpacked -------------------- */

typedef struct { long type; char *val; } prop;
typedef struct { long type; prop *props; int nprops; buf data; } obj;
typedef struct { obj *o; int n; } datafile;

static long id_of(const char *s)
{
    unsigned char c[4] = {' ', ' ', ' ', ' '};
    int i;
    for (i = 0; i < 4 && s[i]; i++) c[i] = (unsigned char)s[i];
    return (long)(int32_t)(((uint32_t)c[0] << 24) | ((uint32_t)c[1] << 16) | ((uint32_t)c[2] << 8) | c[3]);
}
/* -t TYPE as the grabber takes it: upper case, four characters, spaces after */
static long type_id(const char *s)
{
    char c[5] = {0};
    int i;
    for (i = 0; i < 4 && s[i]; i++) c[i] = (char)toupper((unsigned char)s[i]);
    return id_of(c);
}
static void id_str(long id, char *s)
{ s[0] = (char)(id >> 24); s[1] = (char)(id >> 16); s[2] = (char)(id >> 8); s[3] = (char)id; s[4] = 0; }

static const char *get_prop(const obj *o, long type)
{
    int i;
    for (i = 0; i < o->nprops; i++) if (o->props[i].type == type) return o->props[i].val;
    return NULL;
}

static void set_prop(obj *o, long type, const char *val)
{
    int i;
    for (i = 0; i < o->nprops; i++)
        if (o->props[i].type == type) { free(o->props[i].val); o->props[i].val = strdup(val); return; }
    o->props = (prop *)realloc(o->props, sizeof(prop) * (size_t)(o->nprops + 1));
    o->props[o->nprops].type = type;
    o->props[o->nprops].val = strdup(val);
    o->nprops++;
}

static void free_obj(obj *o)
{
    int i;
    for (i = 0; i < o->nprops; i++) free(o->props[i].val);
    free(o->props);
    free(o->data.p);
}

static void append(datafile *d, obj *o)
{
    d->o = (obj *)realloc(d->o, sizeof(obj) * (size_t)(d->n + 1));
    d->o[d->n++] = *o;
}

/* the objects of a datafile from its count on (a nested one is only that: no "ALL.") */
static int parse_objects(const unsigned char *p, size_t n, datafile *d)
{
    size_t at = 4;
    long count, k;
    obj cur;
    if (n < 4) return -1;
    count = getm32(p);
    if (count < 0 || count > 1000000) return -1;
    memset(&cur, 0, sizeof(cur));
    for (k = 0; k < count;) {
        long type, fs, ds;
        if (at + 4 > n) return -1;
        type = getm32(p + at); at += 4;
        if (type == DAT_PROPERTY) {
            long pt, ps;
            char *v;
            if (at + 8 > n) return -1;
            pt = getm32(p + at); ps = getm32(p + at + 4); at += 8;
            if (ps < 0 || at + (size_t)ps > n) return -1;
            v = (char *)malloc((size_t)ps + 1);
            memcpy(v, p + at, (size_t)ps); v[ps] = 0; at += (size_t)ps;
            cur.props = (prop *)realloc(cur.props, sizeof(prop) * (size_t)(cur.nprops + 1));
            cur.props[cur.nprops].type = pt; cur.props[cur.nprops].val = v; cur.nprops++;
            continue;
        }
        if (at + 8 > n) return -1;
        fs = getm32(p + at); ds = getm32(p + at + 4); at += 8;   /* bytes in the file, the object's size (negative: LZSS) */
        if (fs < 0 || at + (size_t)fs > n) return -1;
        cur.type = type;
        if (ds < 0) lzss_decode(p + at, (size_t)fs, (size_t)-ds, &cur.data);
        else put(&cur.data, p + at, (size_t)fs);
        at += (size_t)fs;
        append(d, &cur);
        memset(&cur, 0, sizeof(cur));
        k++;
    }
    return 0;
}

/* a .dat: "slh!" (all of it LZSS) or "slh.", then "ALL.", then the objects; -1 no file, -2 not a datafile */
static int load_dat(const char *name, datafile *d)
{
    buf raw = {0}, un = {0};
    const unsigned char *p;
    size_t n;
    int r;
    if (read_file(name, &raw) != 0) return -1;
    if (raw.n < 8) { free(raw.p); return -2; }
    if (getm32(raw.p) == F_PACK_MAGIC) {
        lzss_decode(raw.p + 4, raw.n - 4, (size_t)-1, &un);
        p = un.p; n = un.n;
    } else if (getm32(raw.p) == F_NOPACK_MAGIC) {
        p = raw.p + 4; n = raw.n - 4;
    } else { free(raw.p); return -2; }
    r = (n >= 4 && getm32(p) == DAT_MAGIC) ? parse_objects(p + 4, n - 4, d) : -2;
    free(raw.p); free(un.p);
    return r;
}

static int cmp_prop(const void *a, const void *b)
{
    long x = ((const prop *)a)->type, y = ((const prop *)b)->type;
    return x < y ? -1 : x > y;
}

/* the grabber's order: by name, case ignored, its "info" object last */
static int cmp_obj(const void *a, const void *b)
{
    const obj *x = (const obj *)a, *y = (const obj *)b;
    long info = id_of("info");
    const char *nx, *ny;
    if ((x->type == info) != (y->type == info)) return x->type == info ? 1 : -1;
    nx = get_prop(x, DAT_NAME); ny = get_prop(y, DAT_NAME);
    return strcasecmp(nx ? nx : "", ny ? ny : "");
}

static int strip = 0;               /* -s1: names only; -s2: no properties */
static int packing = 0;             /* -c0 none, -c1 each object, -c2 the whole file */

static void write_objects(buf *b, datafile *d, int pack_each)
{
    int i, j;
    putm32(b, d->n);
    for (i = 0; i < d->n; i++) {
        obj *o = &d->o[i];
        qsort(o->props, (size_t)o->nprops, sizeof(prop), cmp_prop);
        for (j = 0; j < o->nprops; j++) {
            size_t l = strlen(o->props[j].val);
            if (strip == 2 || (strip == 1 && o->props[j].type != DAT_NAME)) continue;
            putm32(b, DAT_PROPERTY); putm32(b, o->props[j].type); putm32(b, (long)l);
            put(b, o->props[j].val, l);
        }
        putm32(b, o->type);
        if (pack_each) {
            buf z = {0};
            lzss_encode(o->data.p, o->data.n, &z);
            putm32(b, (long)z.n); putm32(b, -(long)o->data.n);
            put(b, z.p, z.n);
            free(z.p);
        } else {
            putm32(b, (long)o->data.n); putm32(b, (long)o->data.n);
            put(b, o->data.p, o->data.n);
        }
    }
}

static int save_dat(const char *name, datafile *d)
{
    buf body = {0}, out = {0};
    FILE *f;
    putm32(&body, DAT_MAGIC);
    write_objects(&body, d, packing == 1);
    if (packing == 2) { putm32(&out, F_PACK_MAGIC); lzss_encode(body.p, body.n, &out); }
    else { putm32(&out, F_NOPACK_MAGIC); put(&out, body.p, body.n); }
    f = fopen(name, "wb");
    if (!f || fwrite(out.p, 1, out.n, f) != out.n || fclose(f) != 0) return -1;
    free(body.p); free(out.p);
    return 0;
}

/* ---- new objects, each type as the grabber makes it ----------------------------------------------- */

static void bitmap_object(buf *b, BITMAP *bmp)
{
    int x, y, d = bitmap_color_depth(bmp);
    putm16(b, d == 32 ? -32 : d);
    putm16(b, bmp->w); putm16(b, bmp->h);
    for (y = 0; y < bmp->h; y++) {
        if (d == 8) { put(b, bmp->line[y], (size_t)bmp->w); continue; }
        for (x = 0; x < bmp->w; x++) {
            int c = getpixel(bmp, x, y), r = getr_depth(d, c), g = getg_depth(d, c), bl = getb_depth(d, c);
            if (c == bitmap_mask_color(bmp)) { r = 255; g = 0; bl = 255; }
            if (d == 15 || d == 16) puti16(b, ((r >> 3) << 11) | ((g >> 2) << 5) | (bl >> 3));
            else { put8(b, r); put8(b, g); put8(b, bl); if (d == 32) put8(b, geta_depth(d, c)); }
        }
    }
}

static BITMAP *picture(const char *name, RGB *pal)
{
    BITMAP *b = load_bitmap(name, pal);
    if (!b) die("can't read the picture %s", name);
    return b;
}

static void grab_bitmap(buf *b, const char *name)
{
    PALETTE pal;
    BITMAP *bmp = picture(name, pal);
    bitmap_object(b, bmp);
    destroy_bitmap(bmp);
}

/* a picture's palette as Allegro's PALETTE: r, g, b (0 to 63) and the filler, each colour */
static void grab_palette(buf *b, const char *name)
{
    PALETTE pal;
    int i;
    destroy_bitmap(picture(name, pal));
    for (i = 0; i < PAL_SIZE; i++) { put8(b, pal[i].r); put8(b, pal[i].g); put8(b, pal[i].b); put8(b, pal[i].filler); }
}

static void grab_font(buf *b, const char *name)
{
    PALETTE pal;
    FONT *f = load_font(name, pal, NULL);
    PACKFILE *pf;
    char tmp[PATH_MAX];
    const char *dir = getenv("TMPDIR");
    buf got = {0};
    if (!f) die("can't read the font %s", name);
    /* the object through a packfile, as allegro4.library reads it back */
    snprintf(tmp, sizeof(tmp), "%s/a4dat-font-%ld", dir && *dir ? dir : "/tmp", (long)getpid());
    pf = pack_fopen(tmp, F_WRITE);
    if (!pf || a4_write_font_object(pf, f) != 0) die("can't write the font of %s", name);
    pack_fclose(pf);
    if (read_file(tmp, &got) != 0) die("can't read back the font of %s", name);
    remove(tmp);
    put(b, got.p, got.n);
    free(got.p);
    destroy_font(f);
}

static void grab_sample(buf *b, const char *name)
{
    SAMPLE *s = load_sample(name);
    unsigned long i, n;
    if (!s) die("can't read the sample %s", name);
    putm16(b, s->stereo ? -s->bits : s->bits);
    putm16(b, s->freq);
    putm32(b, (long)s->len);
    n = s->len * (s->stereo ? 2 : 1);
    if (s->bits == 8) put(b, s->data, (size_t)n);
    else for (i = 0; i < n; i++) puti16(b, ((uint16_t *)s->data)[i]);
    destroy_sample(s);
}

static void grab_midi(buf *b, const char *name)
{
    MIDI *m = load_midi(name);
    int c;
    if (!m) die("can't read the MIDI file %s", name);
    putm16(b, m->divisions);
    for (c = 0; c < MIDI_TRACKS; c++) {
        int l = m->track[c].data ? m->track[c].len : 0;
        putm32(b, l);
        if (l > 0) put(b, m->track[c].data, (size_t)l);
    }
    destroy_midi(m);
}

/* a .dat as a FILE object: its objects without the grabber's "info", counted, with no "ALL." */
static void grab_datafile(buf *b, const char *name)
{
    datafile sub = {0}, keep = {0};
    int i;
    if (load_dat(name, &sub) != 0) die("can't read the datafile %s", name);
    for (i = 0; i < sub.n; i++) {
        if (sub.o[i].type == id_of("info")) free_obj(&sub.o[i]);
        else append(&keep, &sub.o[i]);
    }
    write_objects(b, &keep, 0);
    for (i = 0; i < keep.n; i++) free_obj(&keep.o[i]);
    free(keep.o); free(sub.o);
}

static long type_of(const char *name)
{
    const char *e = get_extension(name);
    if (!ustricmp(e, "bmp") || !ustricmp(e, "pcx") || !ustricmp(e, "tga") || !ustricmp(e, "lbm")) return DAT_BITMAP;
    if (!ustricmp(e, "wav") || !ustricmp(e, "voc")) return DAT_SAMPLE;
    if (!ustricmp(e, "mid")) return DAT_MIDI;
    if (!ustricmp(e, "fnt")) return DAT_FONT;
    if (!ustricmp(e, "dat")) return DAT_FILE;
    return DAT_DATA;
}

static int keep_names = 0;          /* -k: the file's name as it is for NAME */

/* the grabber's DATE: month-day-year, hour:minute, the file's time (SOURCE_DATE_EPOCH, UTC, when set) */
static void date_of(const char *name, char *s, size_t n)
{
    struct stat st;
    time_t t = 0;
    struct tm tm;
    const char *sde = getenv("SOURCE_DATE_EPOCH");
    if (sde && *sde) { t = (time_t)strtoll(sde, NULL, 10); gmtime_r(&t, &tm); }
    else { if (stat(name, &st) == 0) t = st.st_mtime; localtime_r(&t, &tm); }
    snprintf(s, n, "%d-%d-%d, %d:%02d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

static void add_file(datafile *d, const char *name, long type)
{
    obj o;
    char nm[PATH_MAX], date[64], full[PATH_MAX];
    int i;
    memset(&o, 0, sizeof(o));
    o.type = type ? type : type_of(name);
    if (o.type == DAT_BITMAP) grab_bitmap(&o.data, name);
    else if (o.type == DAT_PALETTE) grab_palette(&o.data, name);
    else if (o.type == DAT_FONT) grab_font(&o.data, name);
    else if (o.type == DAT_SAMPLE) grab_sample(&o.data, name);
    else if (o.type == DAT_MIDI) grab_midi(&o.data, name);
    else if (o.type == DAT_FILE) grab_datafile(&o.data, name);
    else if (read_file(name, &o.data) != 0) die("can't read %s", name);
    /* NAME: the file's name, upper case, '.' as '_' */
    snprintf(nm, sizeof(nm), "%s", get_filename(name));
    if (!keep_names) for (i = 0; nm[i]; i++) nm[i] = nm[i] == '.' ? '_' : (char)toupper((unsigned char)nm[i]);
    if (!realpath(name, full)) snprintf(full, sizeof(full), "%s", name);
    date_of(name, date, sizeof(date));
    set_prop(&o, DAT_NAME, nm);
    set_prop(&o, id_of("ORIG"), full);
    set_prop(&o, id_of("DATE"), date);
    if (o.type == DAT_BITMAP) {         /* a whole picture: no grab position */
        set_prop(&o, id_of("XPOS"), "-1"); set_prop(&o, id_of("YPOS"), "-1");
        set_prop(&o, id_of("XSIZ"), "-1"); set_prop(&o, id_of("YSIZ"), "-1");
    }
    for (i = 0; i < d->n; i++) {
        const char *on = get_prop(&d->o[i], DAT_NAME);
        if (d->o[i].type != id_of("info") && on && !strcasecmp(on, nm)) { free_obj(&d->o[i]); d->o[i] = o; return; }
    }
    append(d, &o);
}

static void list(datafile *d, int depth)
{
    int i;
    for (i = 0; i < d->n; i++) {
        char t[5];
        const char *nm = get_prop(&d->o[i], DAT_NAME);
        id_str(d->o[i].type, t);
        printf("%*s- %s - %-24s - %lu bytes\n", depth * 2, "", t, nm ? nm : "", (unsigned long)d->o[i].data.n);
        if (d->o[i].type == DAT_FILE) {
            datafile sub = {0};
            int j;
            if (parse_objects(d->o[i].data.p, d->o[i].data.n, &sub) == 0) list(&sub, depth + 1);
            for (j = 0; j < sub.n; j++) free_obj(&sub.o[j]);
            free(sub.o);
        }
    }
}

static void usage(void)
{
    fprintf(stderr, "usage: dat [-a] [-k] [-t TYPE] [-bpp N] [-c0|-c1|-c2] [-s0|-s1|-s2] [-v] FILE.dat [FILES...]\n"
                    "       dat -l FILE.dat\n");
    exit(2);
}

int main(int argc, char **argv)
{
    datafile d = {0};
    const char *dat = NULL;
    const char **files = (const char **)calloc((size_t)argc, sizeof(char *));
    int nfiles = 0, i, do_list = 0, verbose = 0, has_info = 0, bpp = 0, r;
    long type = 0;
    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        if (!strcmp(a, "-a")) continue;
        else if (!strcmp(a, "-k")) keep_names = 1;
        else if (!strcmp(a, "-l")) do_list = 1;
        else if (!strcmp(a, "-v")) verbose = 1;
        else if (!strcmp(a, "-t") && i + 1 < argc) type = type_id(argv[++i]);
        else if (!strcmp(a, "-bpp") && i + 1 < argc) bpp = atoi(argv[++i]);
        else if (!strncmp(a, "-c", 2) && a[2] >= '0' && a[2] <= '2' && !a[3]) packing = a[2] - '0';
        else if (!strncmp(a, "-s", 2) && a[2] >= '0' && a[2] <= '2' && !a[3]) strip = a[2] - '0';
        else if (a[0] == '-' && a[1]) { fprintf(stderr, "dat: %s is not an option of this dat (README.md)\n", a); return 2; }
        else if (!dat) dat = a;
        else files[nfiles++] = a;
    }
    if (!dat) usage();
    if (install_allegro(SYSTEM_NONE, &errno, atexit) != 0) die("can't start Allegro%s", "");
    /* -bpp N: new bitmaps at that depth; without it, each picture at its own */
    if (bpp) { set_color_depth(bpp); set_color_conversion(COLORCONV_TOTAL); }
    else { set_color_depth(8); set_color_conversion(COLORCONV_NONE); }
    r = load_dat(dat, &d);
    if (r == -2) die("%s is not an Allegro datafile", dat);
    if (do_list) { if (r != 0) die("can't read %s", dat); list(&d, 0); return 0; }
    for (i = 0; i < nfiles; i++) {
        if (verbose) printf("Inserting %s\n", files[i]);
        add_file(&d, files[i], type);
    }
    for (i = 0; i < d.n; i++) if (d.o[i].type == id_of("info")) has_info = 1;
    if (!has_info) {                    /* the grabber's own object, as dat leaves it */
        static const char info[] = "For internal use by the grabber";
        obj o;
        memset(&o, 0, sizeof(o));
        o.type = id_of("info");
        put(&o.data, info, sizeof(info));
        set_prop(&o, DAT_NAME, "GrabberInfo");
        append(&d, &o);
    }
    qsort(d.o, (size_t)d.n, sizeof(obj), cmp_obj);
    if (save_dat(dat, &d) != 0) die("can't write %s", dat);
    if (verbose) printf("Writing %s\n", dat);
    for (i = 0; i < d.n; i++) free_obj(&d.o[i]);
    free(d.o); free(files);
    return 0;
}
