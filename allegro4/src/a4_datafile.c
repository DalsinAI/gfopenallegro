/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Allegro 4 datafiles ("ALL." in an "slh!" packed or "slh." plain file):
 * bitmaps (8-bit; 15/16/24/32-bit ones matched to the palette), RLE and
 * compiled sprites, palettes, fonts, samples, MIDI, raw data and nested
 * datafiles, with their properties (NAME and the rest).
 */
#include "a4_internal.h"

FONT *a4_read_font_object(PACKFILE *f);
void a4_font_destroy(FONT *f);
SAMPLE *a4_read_sample_object(PACKFILE *f);
MIDI *a4_read_midi_object(PACKFILE *f);

static void *read_block(PACKFILE *f, long size)
{
    void *p = a4_malloc((size_t)(size > 0 ? size : 1));
    if (!p) return NULL;
    if (pack_fread(p, size, f) < size) { /* short: keep what there is */ }
    return p;
}

/* a bitmap of 'bits' (negative: with alpha) from a datafile or font */
BITMAP *a4_read_bitmap(PACKFILE *f, int bits)
{
    int w, h, x, y, rgba = 0, depth;
    BITMAP *b;
    if (bits < 0) { bits = -bits; rgba = 1; }
    w = pack_mgetw(f);
    h = pack_mgetw(f);
    if (w < 0 || h < 0) return NULL;
    if (bits == 8) {
        b = create_bitmap_ex(8, w, h);
        if (!b) return NULL;
        for (y = 0; y < h; y++) pack_fread(b->line[y], w, f);
        return a4_fixup_loaded(b, NULL);
    }
    /* truecolour data: read at its own depth (4-bit grey as 24), then to the game's */
    depth = bits == 15 || bits == 16 ? 16 : bits == 32 || rgba ? 32 : 24;
    b = create_bitmap_ex(depth, w, h);
    if (!b) return NULL;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            int r, g, bl, a = 255, c;
            if (bits == 15 || bits == 16) {
                c = pack_igetw(f);          /* stored as 5-6-5 */
                r = ((c >> 11) & 31) * 255 / 31;
                g = ((c >> 5) & 63) * 255 / 63;
                bl = (c & 31) * 255 / 31;
            } else if (bits == 4) {
                c = pack_getc(f);
                r = g = bl = (c & 15) * 17;
            } else {
                r = pack_getc(f);
                g = pack_getc(f);
                bl = pack_getc(f);
                if (rgba) a = pack_getc(f);
            }
            /* pink (255,0,255) is the mask in truecolour data */
            if (r == 255 && g == 0 && bl == 255) a4_wr(b->line[y], x, depth, a4_maskc(depth));
            else {
                uint32_t col = rgba ? (uint32_t)makeacol32(r, g, bl, a) : a4_pack(depth, r, g, bl);
                if (col == a4_maskc(depth)) col ^= 1;
                a4_wr(b->line[y], x, depth, col);
            }
        }
    }
    return a4_fixup_loaded(b, NULL);
}

static RLE_SPRITE *read_rle(PACKFILE *f)
{
    int bits = pack_mgetw(f), w = pack_mgetw(f), h = pack_mgetw(f);
    long size = pack_mgetl(f);
    RLE_SPRITE *s;
    if (bits != 8) {
        /* other depths: skip and make an empty sprite of the size */
        BITMAP *b;
        pack_fseek(f, (int)size);
        b = create_bitmap(w, h);
        if (!b) return NULL;
        s = get_rle_sprite(b);
        destroy_bitmap(b);
        return s;
    }
    s = (RLE_SPRITE *)a4_malloc(sizeof(RLE_SPRITE) + (size_t)size);
    if (!s) return NULL;
    s->w = w; s->h = h; s->color_depth = 8; s->size = (int)size;
    pack_fread(s->dat, size, f);
    return s;
}

static RGB *read_palette(PACKFILE *f, long size)
{
    RGB *p = (RGB *)a4_calloc(sizeof(PALETTE));
    int c, n = (int)(size / 3), x = 0;
    if (!p) return NULL;
    if (n > PAL_SIZE) n = PAL_SIZE;
    for (c = 0; c < n; c++) {
        p[c].r = (unsigned char)(pack_getc(f) >> 2);
        p[c].g = (unsigned char)(pack_getc(f) >> 2);
        p[c].b = (unsigned char)(pack_getc(f) >> 2);
    }
    for (; c < PAL_SIZE; c++) { p[c] = p[x]; if (++x >= n) x = 0; }
    return p;
}

static void *load_object(PACKFILE *f, long type, long size, void (*callback)(DATAFILE *));
static DATAFILE *load_file_object(PACKFILE *f, void (*callback)(DATAFILE *));

static void destroy_object(DATAFILE *d)
{
    int i;
    if (!d->dat) return;
    for (i = 0; i < A4S->ntypes; i++)
        if (A4S->types[i].id == d->type && A4S->types[i].destroy) { A4S->types[i].destroy(d->dat); d->dat = NULL; return; }
    switch (d->type) {
    case DAT_FILE: unload_datafile((DATAFILE *)d->dat); return;
    case DAT_BITMAP: case DAT_C_SPRITE: case DAT_XC_SPRITE: destroy_bitmap((BITMAP *)d->dat); break;
    case DAT_RLE_SPRITE: destroy_rle_sprite((RLE_SPRITE *)d->dat); break;
    case DAT_FONT: a4_font_destroy((FONT *)d->dat); break;
    case DAT_SAMPLE: destroy_sample((SAMPLE *)d->dat); break;
    case DAT_MIDI: destroy_midi((MIDI *)d->dat); break;
    default: a4_free(d->dat); break;
    }
    d->dat = NULL;
}

static void *load_object(PACKFILE *f, long type, long size, void (*callback)(DATAFILE *))
{
    int i;
    for (i = 0; i < A4S->ntypes; i++)
        if (A4S->types[i].id == type && A4S->types[i].load) return A4S->types[i].load(f, size);
    switch (type) {
    case DAT_FILE:
        if (pack_mgetl(f) != DAT_MAGIC) return NULL;
        return load_file_object(f, callback);
    case DAT_BITMAP:
    case DAT_C_SPRITE:
    case DAT_XC_SPRITE: {
        int bits = (short)pack_mgetw(f);
        return a4_read_bitmap(f, bits);
    }
    case DAT_RLE_SPRITE: return read_rle(f);
    case DAT_PALETTE: return read_palette(f, size);
    case DAT_FONT: return a4_read_font_object(f);
    case DAT_SAMPLE: return a4_read_sample_object(f);
    case DAT_MIDI: return a4_read_midi_object(f);
    default: return read_block(f, size);
    }
}

/* the objects after "ALL.": a count, then each object's properties and chunk */
static DATAFILE *load_file_object(PACKFILE *f, void (*callback)(DATAFILE *))
{
    long count = pack_mgetl(f), c = 0;
    DATAFILE *dat;
    DATAFILE_PROPERTY *props = NULL;
    int nprops = 0;
    if (count < 0 || count > 100000) return NULL;
    dat = (DATAFILE *)a4_calloc(sizeof(DATAFILE) * (size_t)(count + 1));
    if (!dat) return NULL;
    while (c < count) {
        long type = pack_mgetl(f);
        if (type == EOF && pack_feof(f)) break;
        if (type == DAT_PROPERTY) {
            long ptype = pack_mgetl(f), psize = pack_mgetl(f);
            DATAFILE_PROPERTY *np;
            if (psize < 0 || psize > 65536) break;
            np = (DATAFILE_PROPERTY *)a4_realloc(props, sizeof(DATAFILE_PROPERTY) * (size_t)(nprops + 1),
                                                 sizeof(DATAFILE_PROPERTY) * (size_t)(nprops + 2));
            if (!np) break;
            props = np;
            props[nprops].type = (int)ptype;
            props[nprops].dat = (char *)a4_malloc((size_t)psize + 1);
            if (!props[nprops].dat) break;
            pack_fread(props[nprops].dat, psize, f);
            props[nprops].dat[psize] = 0;
            nprops++;
            props[nprops].type = DAT_END;
            props[nprops].dat = NULL;
            continue;
        }
        {
            PACKFILE *ch = pack_fopen_chunk(f, FALSE);
            long size;
            if (!ch) break;
            /* the unpacked size is what an object's loader sees */
            size = ch->fsize;
            dat[c].dat = load_object(ch, type, size, callback);
            dat[c].type = (int)type;
            dat[c].size = size;
            pack_fclose_chunk(ch);
            if (!dat[c].dat) {
                dat[c].type = DAT_END;
                unload_datafile(dat);
                if (props) { int i; for (i = 0; i < nprops; i++) a4_free(props[i].dat); a4_free(props); }
                return NULL;
            }
            dat[c].prop = props;
            props = NULL;
            nprops = 0;
            if (callback) callback(&dat[c]);
            c++;
        }
    }
    dat[c].type = DAT_END;
    dat[c].dat = NULL;
    if (props) { int i; for (i = 0; i < nprops; i++) a4_free(props[i].dat); a4_free(props); }
    if (c < count) { unload_datafile(dat); return NULL; }
    return dat;
}

DATAFILE *load_datafile_callback(const char *filename, void (*callback)(DATAFILE *))
{
    PACKFILE *f = pack_fopen(filename, F_READ_PACKED);
    DATAFILE *d = NULL;
    if (!f) return NULL;
    if (pack_mgetl(f) == DAT_MAGIC) d = load_file_object(f, callback);
    pack_fclose(f);
    return d;
}

DATAFILE *load_datafile(const char *filename) { return load_datafile_callback(filename, NULL); }

static void free_props(DATAFILE_PROPERTY *p)
{
    int i;
    if (!p) return;
    for (i = 0; p[i].type != DAT_END; i++) a4_free(p[i].dat);
    a4_free(p);
}

void unload_datafile(DATAFILE *dat)
{
    int i;
    if (!dat) return;
    for (i = 0; dat[i].type != DAT_END; i++) {
        destroy_object(&dat[i]);
        free_props(dat[i].prop);
    }
    a4_free(dat);
}

/* "OBJECT" or "FILE/OBJECT" inside filename */
DATAFILE *load_datafile_object(const char *filename, const char *objectname)
{
    char name[600];
    PACKFILE *f;
    DATAFILE *d;
    long type;
    if (!filename || !objectname) return NULL;
    ustrzcpy(name, (int)sizeof(name), filename);
    ustrzcat(name, (int)sizeof(name), "#");
    ustrzcat(name, (int)sizeof(name), objectname);
    f = pack_fopen(name, F_READ);
    if (!f) return NULL;
    d = (DATAFILE *)a4_calloc(sizeof(DATAFILE));
    if (!d) { pack_fclose(f); return NULL; }
    type = A4S->last_obj_type;
    d->dat = load_object(f, type, f->fsize, NULL);
    d->size = f->fsize;
    d->type = (int)type;
    d->prop = NULL;
    pack_fclose(f);
    if (!d->dat) { a4_free(d); return NULL; }
    return d;
}

void unload_datafile_object(DATAFILE *dat)
{
    if (!dat) return;
    destroy_object(dat);
    free_props(dat->prop);
    a4_free(dat);
}

const char *get_datafile_property(const DATAFILE *dat, int type)
{
    DATAFILE_PROPERTY *p;
    if (!dat || !dat->prop) return "";
    for (p = dat->prop; p->type != DAT_END; p++) if (p->type == type) return p->dat ? p->dat : "";
    return "";
}

DATAFILE *find_datafile_object(const DATAFILE *dat, const char *objectname)
{
    char name[512];
    int n = 0, i;
    const char *rest = NULL;
    if (!dat || !objectname) return NULL;
    while (objectname[n] && objectname[n] != '/' && objectname[n] != '#' && n < 511) { name[n] = objectname[n]; n++; }
    name[n] = 0;
    if (objectname[n]) rest = objectname + n + 1;
    for (i = 0; dat[i].type != DAT_END; i++) {
        if (ustricmp(get_datafile_property(&dat[i], DAT_NAME), name) == 0) {
            if (rest) {
                if (dat[i].type == DAT_FILE) return find_datafile_object((DATAFILE *)dat[i].dat, rest);
                return NULL;
            }
            return (DATAFILE *)&dat[i];
        }
    }
    return NULL;
}

void register_datafile_object(int id, void *(*load)(PACKFILE *f, long size), void (*destroy)(void *data))
{
    int i;
    for (i = 0; i < A4S->ntypes; i++)
        if (A4S->types[i].id == id) { A4S->types[i].load = load; A4S->types[i].destroy = destroy; return; }
    if (A4S->ntypes < (int)(sizeof(A4S->types) / sizeof(A4S->types[0]))) {
        A4S->types[A4S->ntypes].id = id;
        A4S->types[A4S->ntypes].load = load;
        A4S->types[A4S->ntypes].destroy = destroy;
        A4S->ntypes++;
    }
}

void fixup_datafile(DATAFILE *data) { (void)data; }

DATAFILE_INDEX *create_datafile_index(const char *filename)
{
    DATAFILE_INDEX *ix = (DATAFILE_INDEX *)a4_calloc(sizeof(DATAFILE_INDEX));
    DATAFILE *d;
    int n = 0;
    if (!ix) return NULL;
    /* loads the datafile once to count; items load by name from then on */
    d = load_datafile(filename);
    if (!d) { a4_free(ix); return NULL; }
    while (d[n].type != DAT_END) n++;
    ix->filename = a4_strdup0(filename);
    ix->offset = (long *)a4_calloc(sizeof(long) * (size_t)(n + 1));
    {
        int i;
        for (i = 0; i < n && ix->offset; i++) ix->offset[i] = (long)a4_strdup0(get_datafile_property(&d[i], DAT_NAME));
    }
    unload_datafile(d);
    return ix;
}

DATAFILE *load_datafile_object_indexed(const DATAFILE_INDEX *index, int item)
{
    if (!index || !index->offset || !index->offset[item]) return NULL;
    return load_datafile_object(index->filename, (const char *)index->offset[item]);
}

void destroy_datafile_index(DATAFILE_INDEX *index)
{
    int i;
    if (!index) return;
    if (index->offset) { for (i = 0; index->offset[i]; i++) a4_free((void *)index->offset[i]); a4_free(index->offset); }
    a4_free(index->filename);
    a4_free(index);
}
