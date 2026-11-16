/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * PACKFILEs: buffered files, Allegro 4's LZSS packed files ("slh!"), the
 * unpacked marker ("slh."), chunks inside them (datafile objects, each
 * packed on its own or not) and "file.dat#OBJECT" names. Written from
 * Allegro 4's documented file format; packed writing writes the unpacked
 * form, which every Allegro 4 reads.
 */
#include "a4_internal.h"

#define LZ_THRESHOLD 2

/* ---- the source -------------------------------------------------------------- */

static int src_getc(PACKFILE *f)
{
    int c;
    if (f->limit == 0) return EOF;
    switch (f->kind) {
    case SRC_FILE:
        if (f->buf_pos >= f->buf_len) {
            long n = a4_os_read(f->fh, f->buf, F_BUF_SIZE);
            if (n <= 0) { if (n < 0) f->err = 1; return EOF; }
            f->buf_len = (int)n;
            f->buf_pos = 0;
        }
        c = f->buf[f->buf_pos++];
        break;
    case SRC_PARENT:
        c = pack_getc(f->parent);
        if (c == EOF) return EOF;
        break;
    default:
        c = f->vt->pf_getc(f->userdata);
        if (c == EOF) return EOF;
        break;
    }
    if (f->limit > 0) f->limit--;
    return c;
}

/* one byte of an LZSS stream: flag bytes say, bit by bit from the lowest,
 * whether a literal (1) or a 12-bit position and 4-bit length (0) follows */
static int lz_getc(PACKFILE *f)
{
    int c;
    if (f->copy_left > 0) {
        c = f->ring[f->copy_pos];
        f->copy_pos = (f->copy_pos + 1) & (LZ_N - 1);
        f->copy_left--;
        f->ring[f->r] = (unsigned char)c;
        f->r = (f->r + 1) & (LZ_N - 1);
        return c;
    }
    f->flags >>= 1;
    if (!(f->flags & 256)) {
        int fl = src_getc(f);
        if (fl == EOF) return EOF;
        f->flags = (unsigned)fl | 0xFF00u;
    }
    if (f->flags & 1) {
        c = src_getc(f);
        if (c == EOF) return EOF;
        f->ring[f->r] = (unsigned char)c;
        f->r = (f->r + 1) & (LZ_N - 1);
        return c;
    } else {
        int i = src_getc(f), j;
        if (i == EOF) return EOF;
        j = src_getc(f);
        if (j == EOF) return EOF;
        i |= (j & 0xF0) << 4;
        f->copy_pos = i;
        f->copy_left = (j & 0x0F) + LZ_THRESHOLD + 1;
        return lz_getc(f);
    }
}

static int start_lz(PACKFILE *f)
{
    f->ring = (unsigned char *)a4_calloc(LZ_N + LZ_F);
    if (!f->ring) return -1;
    f->pack = 1;
    f->r = LZ_N - LZ_F;
    f->flags = 0;
    f->copy_left = 0;
    return 0;
}

/* ---- opening ------------------------------------------------------------------- */

static PACKFILE *new_pf(void)
{
    PACKFILE *f = (PACKFILE *)a4_calloc(sizeof(PACKFILE));
    if (f) { f->unget = -1; f->limit = -1; }
    return f;
}

static void free_pf(PACKFILE *f)
{
    if (!f) return;
    a4_free(f->ring);
    a4_free(f->wbuf);
    a4_free(f);
}

static PACKFILE *open_datafile_object(const char *filename);

PACKFILE *pack_fopen(const char *filename, const char *mode)
{
    PACKFILE *f;
    int write = 0, packed = 0, nopack = 0;
    const char *m;
    if (!filename || !mode) return NULL;
    for (m = mode; *m; m++) {
        if (*m == 'w' || *m == 'W') write = 1;
        else if (*m == 'p' || *m == 'P') packed = 1;
        else if (*m == '!') nopack = 1;
    }
    if (!write && strchr(filename, '#')) return open_datafile_object(filename);
    f = new_pf();
    if (!f) return NULL;
    f->kind = SRC_FILE;
    f->write = write;
    f->fh = a4_os_open(filename, write);
    if (!f->fh) { free_pf(f); *allegro_errno = ENOENT; return NULL; }
    if (write) {
        if (packed && !nopack) pack_mputl(F_NOPACK_MAGIC, f);   /* the unpacked form */
        return f;
    }
    if (packed) {
        long magic = pack_mgetl(f);
        if (magic == F_PACK_MAGIC) {
            if (start_lz(f) != 0) { pack_fclose(f); return NULL; }
        } else if (magic != F_NOPACK_MAGIC) {
            pack_fclose(f);
            *allegro_errno = EDOM;
            return NULL;
        }
    }
    return f;
}

PACKFILE *pack_fopen_vtable(const PACKFILE_VTABLE *vtable, void *userdata)
{
    PACKFILE *f = new_pf();
    if (!f) return NULL;
    f->kind = SRC_VTABLE;
    f->vt = vtable;
    f->userdata = userdata;
    return f;
}

static int flush_write(PACKFILE *f)
{
    if (f->kind == SRC_FILE && f->write && f->buf_len) {
        if (a4_os_write(f->fh, f->buf, f->buf_len) != f->buf_len) f->err = 1;
        f->buf_len = 0;
    }
    return f->err ? EOF : 0;
}

int pack_fclose(PACKFILE *f)
{
    int r = 0;
    if (!f) return 0;
    if (f->kind == SRC_FILE) {
        if (f->write) r = flush_write(f);
        if (a4_os_close(f->fh) != 0) r = EOF;
    } else if (f->kind == SRC_VTABLE) {
        r = f->vt->pf_fclose ? f->vt->pf_fclose(f->userdata) : 0;
    } else if (f->kind == SRC_PARENT) {
        /* a "file.dat#OBJECT" opened directly: close the datafile too */
        PACKFILE *p = f->parent;
        while (p && p->kind == SRC_PARENT) { PACKFILE *pp = p->parent; free_pf(p); p = pp; }
        if (p) pack_fclose(p);
    }
    free_pf(f);
    return r;
}

/* a sub-chunk: 32-bit unpacked size, 32-bit stored size (negative: LZSS) */
PACKFILE *pack_fopen_chunk(PACKFILE *f, int pack)
{
    PACKFILE *c;
    if (!f) return NULL;
    c = new_pf();
    if (!c) return NULL;
    c->kind = SRC_PARENT;
    c->parent = f;
    if (f->write) {
        (void)pack;                     /* written unpacked */
        c->write = 1;
        return c;
    }
    {
        long fsize = pack_mgetl(f), dsize = pack_mgetl(f);
        c->fsize = fsize;
        if (pack_feof(f) && fsize == EOF) { free_pf(c); return NULL; }
        if (dsize < 0) {
            c->limit = -dsize;
            if (start_lz(c) != 0) { free_pf(c); return NULL; }
        } else {
            c->limit = dsize;
        }
    }
    return c;
}

PACKFILE *pack_fclose_chunk(PACKFILE *c)
{
    PACKFILE *p;
    if (!c) return NULL;
    p = c->parent;
    if (c->write) {
        pack_mputl(c->wlen, p);
        pack_mputl(c->wlen, p);
        pack_fwrite(c->wbuf, c->wlen, p);
    } else {
        /* skip what was not read, so the parent is at the next object */
        if (c->pack) { while (c->limit > 0 && src_getc(c) != EOF) ; }
        else { while (c->limit > 0 && src_getc(c) != EOF) ; }
    }
    free_pf(c);
    return p;
}

/* ---- reading and writing ------------------------------------------------------- */

int pack_getc(PACKFILE *f)
{
    int c;
    if (!f || f->write) return EOF;
    if (f->unget >= 0) { c = f->unget; f->unget = -1; return c; }
    c = f->pack ? lz_getc(f) : src_getc(f);
    if (c == EOF) f->eof = 1;
    return c;
}

int pack_ungetc(int c, PACKFILE *f) { if (!f) return EOF; f->unget = c & 255; f->eof = 0; return c; }

int pack_putc(int c, PACKFILE *f)
{
    if (!f || !f->write) return EOF;
    if (f->kind == SRC_PARENT) {
        if (f->wlen >= f->wcap) {
            long nc = f->wcap ? f->wcap * 2 : 4096;
            unsigned char *nb = (unsigned char *)a4_realloc(f->wbuf, (size_t)f->wcap, (size_t)nc);
            if (!nb) { f->err = 1; return EOF; }
            f->wbuf = nb; f->wcap = nc;
        }
        f->wbuf[f->wlen++] = (unsigned char)c;
        return c & 255;
    }
    if (f->kind == SRC_VTABLE) return f->vt->pf_putc ? f->vt->pf_putc(c, f->userdata) : EOF;
    if (f->buf_len >= F_BUF_SIZE && flush_write(f) == EOF) return EOF;
    f->buf[f->buf_len++] = (unsigned char)c;
    return c & 255;
}

int pack_feof(PACKFILE *f)
{
    int c;
    if (!f) return TRUE;
    if (f->eof) return TRUE;
    if (f->write) return FALSE;
    if (f->unget >= 0) return FALSE;
    c = pack_getc(f);
    if (c == EOF) return TRUE;
    f->unget = c;
    return FALSE;
}

int pack_ferror(PACKFILE *f) { return f ? f->err : 1; }

long pack_fread(void *p, long n, PACKFILE *f)
{
    unsigned char *d = (unsigned char *)p;
    long i;
    if (!f) return 0;
    /* the fast path: a plain file with nothing pushed back */
    if (f->kind == SRC_FILE && !f->pack && f->unget < 0 && f->limit < 0) {
        long done = 0;
        while (done < n) {
            if (f->buf_pos < f->buf_len) {
                long k = f->buf_len - f->buf_pos;
                if (k > n - done) k = n - done;
                memcpy(d + done, f->buf + f->buf_pos, (size_t)k);
                f->buf_pos += (int)k;
                done += k;
            } else if (n - done >= F_BUF_SIZE) {
                long k = a4_os_read(f->fh, d + done, n - done);
                if (k <= 0) { f->eof = 1; break; }
                done += k;
            } else {
                long k = a4_os_read(f->fh, f->buf, F_BUF_SIZE);
                if (k <= 0) { f->eof = 1; break; }
                f->buf_pos = 0;
                f->buf_len = (int)k;
            }
        }
        return done;
    }
    for (i = 0; i < n; i++) {
        int c = pack_getc(f);
        if (c == EOF) break;
        d[i] = (unsigned char)c;
    }
    return i;
}

long pack_fwrite(const void *p, long n, PACKFILE *f)
{
    const unsigned char *s = (const unsigned char *)p;
    long i;
    for (i = 0; i < n; i++) if (pack_putc(s[i], f) == EOF) break;
    return i;
}

int pack_fseek(PACKFILE *f, int offset)
{
    if (!f || f->write || offset < 0) return -1;
    while (offset-- > 0) if (pack_getc(f) == EOF) return -1;
    return 0;
}

int pack_igetw(PACKFILE *f) { int a = pack_getc(f), b = pack_getc(f); if (a == EOF || b == EOF) return EOF; return a | (b << 8); }
long pack_igetl(PACKFILE *f)
{
    int a = pack_getc(f), b = pack_getc(f), c = pack_getc(f), d = pack_getc(f);
    if (d == EOF) return EOF;
    return (long)(int32_t)((uint32_t)a | ((uint32_t)b << 8) | ((uint32_t)c << 16) | ((uint32_t)d << 24));
}
int pack_mgetw(PACKFILE *f) { int a = pack_getc(f), b = pack_getc(f); if (a == EOF || b == EOF) return EOF; return (a << 8) | b; }
long pack_mgetl(PACKFILE *f)
{
    int a = pack_getc(f), b = pack_getc(f), c = pack_getc(f), d = pack_getc(f);
    if (d == EOF) return EOF;
    return (long)(int32_t)(((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) | (uint32_t)d);
}
int pack_iputw(int w, PACKFILE *f) { pack_putc(w & 255, f); return pack_putc((w >> 8) & 255, f) == EOF ? EOF : w; }
long pack_iputl(long l, PACKFILE *f)
{
    pack_putc((int)(l & 255), f); pack_putc((int)((l >> 8) & 255), f);
    pack_putc((int)((l >> 16) & 255), f);
    return pack_putc((int)((l >> 24) & 255), f) == EOF ? EOF : l;
}
int pack_mputw(int w, PACKFILE *f) { pack_putc((w >> 8) & 255, f); return pack_putc(w & 255, f) == EOF ? EOF : w; }
long pack_mputl(long l, PACKFILE *f)
{
    pack_putc((int)((l >> 24) & 255), f); pack_putc((int)((l >> 16) & 255), f);
    pack_putc((int)((l >> 8) & 255), f);
    return pack_putc((int)(l & 255), f) == EOF ? EOF : l;
}

char *pack_fgets(char *p, int max, PACKFILE *f)
{
    int i = 0, c;
    if (max <= 0) return NULL;
    while (i < max - 1) {
        c = pack_getc(f);
        if (c == EOF) { if (!i) return NULL; break; }
        if (c == '\r') {
            int n = pack_getc(f);
            if (n != '\n' && n != EOF) pack_ungetc(n, f);
            break;
        }
        if (c == '\n') break;
        p[i++] = (char)c;
    }
    p[i] = 0;
    return p;
}

int pack_fputs(const char *p, PACKFILE *f)
{
    while (*p) if (pack_putc((unsigned char)*p++, f) == EOF) return EOF;
    return 0;
}

void packfile_password(const char *password)
{
    if (!password) { A4S->password[0] = 0; return; }
    ustrzcpy(A4S->password, (int)sizeof(A4S->password), password);
}

/* ---- "file.dat#OBJECT[/NESTED]" -------------------------------------------------- */

static PACKFILE *find_object(PACKFILE *f, const char *name)
{
    char want[256], got[256];
    int n = 0, nested = 0;
    while (*name && *name != '/' && *name != '#' && n < 255) want[n++] = *name++;
    want[n] = 0;
    if (*name) { nested = 1; name++; }
    pack_mgetl(f);                      /* the object count */
    for (;;) {
        int use = 0;
        long type = pack_mgetl(f);
        if (type == EOF) return NULL;
        while (type == DAT_PROPERTY) {
            long ptype = pack_mgetl(f), psize = pack_mgetl(f);
            if (ptype == DAT_NAME && psize < 255) {
                pack_fread(got, psize, f);
                got[psize] = 0;
                if (ustricmp(got, want) == 0) use = 1;
            } else pack_fseek(f, (int)psize);
            type = pack_mgetl(f);
            if (type == EOF) return NULL;
        }
        if (use) {
            PACKFILE *c;
            A4S->last_obj_type = type;
            c = pack_fopen_chunk(f, FALSE);
            if (!c) return NULL;
            if (nested) {
                if (type != DAT_FILE || pack_mgetl(c) != DAT_MAGIC) return NULL;
                return find_object(c, name);
            }
            return c;
        }
        {
            long fsize = pack_mgetl(f), dsize = pack_mgetl(f);
            (void)fsize;
            if (dsize < 0) dsize = -dsize;
            if (pack_fseek(f, (int)dsize) != 0) return NULL;
        }
    }
}

static PACKFILE *open_datafile_object(const char *filename)
{
    char path[512];
    const char *hash = strchr(filename, '#');
    PACKFILE *f, *c;
    int n = (int)(hash - filename);
    if (n >= (int)sizeof(path)) return NULL;
    memcpy(path, filename, (size_t)n);
    path[n] = 0;
    f = pack_fopen(path, F_READ_PACKED);
    if (!f) return NULL;
    if (pack_mgetl(f) != DAT_MAGIC) { pack_fclose(f); return NULL; }
    c = find_object(f, hash + 1);
    if (!c) { pack_fclose(f); return NULL; }
    return c;                           /* pack_fclose on it closes the file too */
}
