/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Picture files: PCX (8-bit RLE and 24-bit) and BMP (1/4/8-bit,
 * uncompressed or RLE8, and 24/32-bit), loaded at their own depth and then
 * converted to the game's colour depth as set_color_conversion allows;
 * saved as 8-bit (PCX, BMP) or 24-bit (BMP of a truecolour bitmap). load_bitmap picks by the
 * name's extension; register_bitmap_file_type adds others.
 */
#include "a4_internal.h"

/* ---- PCX ---------------------------------------------------------------------- */

BITMAP *load_pcx_pf(PACKFILE *f, RGB *pal)
{
    int bpp, planes, bpl, w, h, x, y, p, c, i;
    BITMAP *b;
    unsigned char *row;
    pack_getc(f);                               /* manufacturer */
    pack_getc(f);                               /* version */
    if (pack_getc(f) != 1) return NULL;          /* RLE */
    bpp = pack_getc(f);
    w = pack_igetw(f); h = pack_igetw(f);
    w = pack_igetw(f) - w + 1;
    h = pack_igetw(f) - h + 1;
    if (w <= 0 || h <= 0 || bpp != 8) return NULL;
    pack_fseek(f, 4 + 48 + 1);                  /* DPI, the 16-colour palette, reserved */
    planes = pack_getc(f);
    bpl = pack_igetw(f);
    pack_fseek(f, 60);
    if (planes != 1 && planes != 3) return NULL;
    b = create_bitmap_ex(planes == 1 ? 8 : 24, w, h);
    row = (unsigned char *)a4_malloc((size_t)bpl * (size_t)planes);
    if (!b || !row) { destroy_bitmap(b); a4_free(row); return NULL; }
    for (y = 0; y < h; y++) {
        x = 0;
        while (x < bpl * planes) {
            c = pack_getc(f);
            if (c == EOF) break;
            if ((c & 0xC0) == 0xC0) {
                int n = c & 0x3F;
                c = pack_getc(f);
                while (n-- && x < bpl * planes) row[x++] = (unsigned char)c;
            } else row[x++] = (unsigned char)c;
        }
        if (planes == 1) memcpy(b->line[y], row, (size_t)w);
        else {
            for (p = 0; p < w; p++)
                a4_wr(b->line[y], p, 24, (uint32_t)row[p] << 16 | (uint32_t)row[bpl + p] << 8 | row[2 * bpl + p]);
        }
    }
    a4_free(row);
    if (planes == 1) {
        /* the palette: 769 bytes from the end, after a 12 */
        RGB own[256];
        while ((c = pack_getc(f)) != EOF && c != 12) ;
        if (c != 12) return a4_fixup_loaded(b, NULL);
        for (i = 0; i < 256; i++) {
            own[i].r = (unsigned char)(pack_getc(f) >> 2);
            own[i].g = (unsigned char)(pack_getc(f) >> 2);
            own[i].b = (unsigned char)(pack_getc(f) >> 2);
            own[i].filler = 0;
        }
        if (pal) memcpy(pal, own, sizeof(own));
        return a4_fixup_loaded(b, own);
    }
    if (pal) get_palette(pal);
    return a4_fixup_loaded(b, NULL);
}

BITMAP *load_pcx(const char *filename, RGB *pal)
{
    PACKFILE *f = pack_fopen(filename, F_READ);
    BITMAP *b;
    if (!f) return NULL;
    b = load_pcx_pf(f, pal);
    pack_fclose(f);
    return b;
}

int save_pcx_pf(PACKFILE *f, BITMAP *b, const RGB *pal)
{
    int x, y, i;
    RGB cur[256];
    if (a4_bdepth(b) != 8) {
        /* PCX is saved 8-bit: a truecolour bitmap is matched to the palette */
        BITMAP *e = a4_bitmap_to_depth(b, 8, NULL);
        int r;
        if (!e) return -1;
        r = save_pcx_pf(f, e, pal);
        destroy_bitmap(e);
        return r;
    }
    if (!pal) { get_palette(cur); pal = cur; }
    pack_putc(10, f); pack_putc(5, f); pack_putc(1, f); pack_putc(8, f);
    pack_iputw(0, f); pack_iputw(0, f); pack_iputw(b->w - 1, f); pack_iputw(b->h - 1, f);
    pack_iputw(320, f); pack_iputw(200, f);
    for (i = 0; i < 48; i++) pack_putc(0, f);
    pack_putc(0, f);
    pack_putc(1, f);
    pack_iputw((b->w + 1) & ~1, f);
    pack_iputw(1, f);
    for (i = 0; i < 58; i++) pack_putc(0, f);
    for (y = 0; y < b->h; y++) {
        int bpl = (b->w + 1) & ~1;
        x = 0;
        while (x < bpl) {
            int c = x < b->w ? b->line[y][x] : 0, n = 1;
            while (x + n < bpl && n < 63 && (x + n < b->w ? b->line[y][x + n] : 0) == c) n++;
            if (n > 1 || (c & 0xC0) == 0xC0) pack_putc(0xC0 | n, f);
            pack_putc(c, f);
            x += n;
        }
    }
    pack_putc(12, f);
    for (i = 0; i < 256; i++) {
        pack_putc(a4_pal63to255(pal[i].r), f);
        pack_putc(a4_pal63to255(pal[i].g), f);
        pack_putc(a4_pal63to255(pal[i].b), f);
    }
    return pack_ferror(f) ? -1 : 0;
}

int save_pcx(const char *filename, BITMAP *b, const RGB *pal)
{
    PACKFILE *f = pack_fopen(filename, F_WRITE);
    int r;
    if (!f) return -1;
    r = save_pcx_pf(f, b, pal);
    if (pack_fclose(f) != 0) r = -1;
    return r;
}

/* ---- BMP ------------------------------------------------------------------------ */

BITMAP *load_bmp_pf(PACKFILE *f, RGB *pal)
{
    long offbits, hsize, w, h, comp, ncol;
    int bits, y, x, i, flip = 1;
    BITMAP *b;
    RGB cur[256];
    if (pack_igetw(f) != 0x4D42) return NULL;   /* "BM" */
    pack_igetl(f); pack_igetw(f); pack_igetw(f);
    offbits = pack_igetl(f);
    hsize = pack_igetl(f);
    if (hsize == 12) {
        w = pack_igetw(f); h = pack_igetw(f); pack_igetw(f); bits = pack_igetw(f); comp = 0; ncol = 0;
    } else {
        w = pack_igetl(f); h = pack_igetl(f); pack_igetw(f); bits = pack_igetw(f);
        comp = pack_igetl(f); pack_igetl(f); pack_igetl(f); pack_igetl(f);
        ncol = pack_igetl(f); pack_igetl(f);
        pack_fseek(f, (int)(hsize - 40));
    }
    if (h < 0) { h = -h; flip = 0; }
    if (w <= 0 || h <= 0 || w > 16384 || h > 16384) return NULL;
    if (bits <= 8) {
        int n = ncol ? (int)ncol : (1 << bits), q = hsize == 12 ? 3 : 4;
        for (i = 0; i < n && i < 256; i++) {
            cur[i].b = (unsigned char)(pack_getc(f) >> 2);
            cur[i].g = (unsigned char)(pack_getc(f) >> 2);
            cur[i].r = (unsigned char)(pack_getc(f) >> 2);
            cur[i].filler = 0;
            if (q == 4) pack_getc(f);
        }
        for (; i < 256; i++) cur[i].r = cur[i].g = cur[i].b = cur[i].filler = 0;
        {
            long used = 14 + hsize + (long)n * q;
            if (offbits > used) pack_fseek(f, (int)(offbits - used));
        }
        if (pal) memcpy(pal, cur, sizeof(cur));
    } else {
        get_palette(cur);
        if (pal) memcpy(pal, cur, sizeof(cur));
        if (offbits > 14 + hsize) pack_fseek(f, (int)(offbits - 14 - hsize));
    }
    b = create_bitmap_ex(bits <= 8 ? 8 : 24, (int)w, (int)h);
    if (!b) return NULL;
    if (comp == 1 && bits == 8) {
        /* RLE8 */
        int xx = 0, yy = 0;
        for (;;) {
            int n = pack_getc(f), c = pack_getc(f);
            if (n == EOF || c == EOF) break;
            if (n) { while (n--) { if (xx < w && yy < h) b->line[flip ? h - 1 - yy : yy][xx] = (unsigned char)c; xx++; } }
            else if (c == 0) { xx = 0; yy++; }
            else if (c == 1) break;
            else if (c == 2) { xx += pack_getc(f); yy += pack_getc(f); }
            else {
                int k;
                for (k = 0; k < c; k++) { int v = pack_getc(f); if (xx < w && yy < h) b->line[flip ? h - 1 - yy : yy][xx] = (unsigned char)v; xx++; }
                if (c & 1) pack_getc(f);
            }
        }
        return a4_fixup_loaded(b, cur);
    }
    for (y = 0; y < h; y++) {
        unsigned char *row = b->line[flip ? h - 1 - y : y];
        long rowbytes = ((w * bits + 31) / 32) * 4, used = 0;
        if (bits == 8) { pack_fread(row, w, f); used = w; }
        else if (bits == 4 || bits == 1) {
            int ppb = 8 / bits;
            for (x = 0; x < w; x += ppb) {
                int c = pack_getc(f), k;
                used++;
                for (k = 0; k < ppb && x + k < w; k++)
                    row[x + k] = (unsigned char)((c >> (8 - bits * (k + 1))) & ((1 << bits) - 1));
            }
        } else {
            int bpp = bits / 8;
            for (x = 0; x < w; x++) {
                int bl = pack_getc(f), g = pack_getc(f), r = pack_getc(f);
                if (bpp == 4) pack_getc(f);
                used += bpp;
                a4_wr(row, x, 24, (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)bl);
            }
        }
        if (rowbytes > used) pack_fseek(f, (int)(rowbytes - used));
    }
    return a4_fixup_loaded(b, bits <= 8 ? cur : NULL);
}

BITMAP *load_bmp(const char *filename, RGB *pal)
{
    PACKFILE *f = pack_fopen(filename, F_READ);
    BITMAP *b;
    if (!f) return NULL;
    b = load_bmp_pf(f, pal);
    pack_fclose(f);
    return b;
}

static int save_bmp24(PACKFILE *f, BITMAP *b)
{
    int x, y, d = a4_bdepth(b);
    long rowbytes = ((long)b->w * 3 + 3) & ~3L;
    pack_iputw(0x4D42, f);
    pack_iputl(54 + rowbytes * b->h, f);
    pack_iputw(0, f); pack_iputw(0, f);
    pack_iputl(54, f);
    pack_iputl(40, f); pack_iputl(b->w, f); pack_iputl(b->h, f);
    pack_iputw(1, f); pack_iputw(24, f);
    pack_iputl(0, f); pack_iputl(rowbytes * b->h, f);
    pack_iputl(0xB12, f); pack_iputl(0xB12, f); pack_iputl(0, f); pack_iputl(0, f);
    for (y = b->h - 1; y >= 0; y--) {
        for (x = 0; x < b->w; x++) {
            int r, g, bl;
            a4_unpack(d, a4_rd(b->line[y], x, d), &r, &g, &bl);
            pack_putc(bl, f); pack_putc(g, f); pack_putc(r, f);
        }
        for (x = b->w * 3; x < rowbytes; x++) pack_putc(0, f);
    }
    return pack_ferror(f) ? -1 : 0;
}

int save_bmp_pf(PACKFILE *f, BITMAP *b, const RGB *pal)
{
    int x, y, i;
    long rowbytes = ((long)b->w + 3) & ~3L;
    RGB cur[256];
    if (a4_bdepth(b) != 8) return save_bmp24(f, b);
    if (!pal) { get_palette(cur); pal = cur; }
    pack_iputw(0x4D42, f);
    pack_iputl(54 + 1024 + rowbytes * b->h, f);
    pack_iputw(0, f); pack_iputw(0, f);
    pack_iputl(54 + 1024, f);
    pack_iputl(40, f); pack_iputl(b->w, f); pack_iputl(b->h, f);
    pack_iputw(1, f); pack_iputw(8, f);
    pack_iputl(0, f); pack_iputl(rowbytes * b->h, f);
    pack_iputl(0xB12, f); pack_iputl(0xB12, f); pack_iputl(256, f); pack_iputl(256, f);
    for (i = 0; i < 256; i++) {
        pack_putc(a4_pal63to255(pal[i].b), f);
        pack_putc(a4_pal63to255(pal[i].g), f);
        pack_putc(a4_pal63to255(pal[i].r), f);
        pack_putc(0, f);
    }
    for (y = b->h - 1; y >= 0; y--) {
        pack_fwrite(b->line[y], b->w, f);
        for (x = b->w; x < rowbytes; x++) pack_putc(0, f);
    }
    return pack_ferror(f) ? -1 : 0;
}

int save_bmp(const char *filename, BITMAP *b, const RGB *pal)
{
    PACKFILE *f = pack_fopen(filename, F_WRITE);
    int r;
    if (!f) return -1;
    r = save_bmp_pf(f, b, pal);
    if (pack_fclose(f) != 0) r = -1;
    return r;
}

BITMAP *load_tga(const char *filename, RGB *pal) { (void)filename; (void)pal; return NULL; }

/* ---- by extension ------------------------------------------------------------------- */

struct ftype { char ext[8]; BITMAP *(*load)(const char *, RGB *); int (*save)(const char *, BITMAP *, const RGB *); };
static struct ftype extra_types[8];
static int n_extra;

void register_bitmap_file_type(const char *ext, BITMAP *(*load)(const char *filename, RGB *pal),
                               int (*save)(const char *filename, BITMAP *bmp, const RGB *pal))
{
    if (n_extra >= 8 || !ext) return;
    ustrzcpy(extra_types[n_extra].ext, 8, ext);
    extra_types[n_extra].load = load;
    extra_types[n_extra].save = save;
    n_extra++;
}

BITMAP *load_bitmap(const char *filename, RGB *pal)
{
    const char *e = get_extension(filename);
    int i;
    for (i = 0; i < n_extra; i++) if (ustricmp(e, extra_types[i].ext) == 0 && extra_types[i].load) return extra_types[i].load(filename, pal);
    if (ustricmp(e, "pcx") == 0) return load_pcx(filename, pal);
    if (ustricmp(e, "bmp") == 0) return load_bmp(filename, pal);
    if (ustricmp(e, "tga") == 0) return load_tga(filename, pal);
    return NULL;
}

int save_bitmap(const char *filename, BITMAP *b, const RGB *pal)
{
    const char *e = get_extension(filename);
    int i;
    for (i = 0; i < n_extra; i++) if (ustricmp(e, extra_types[i].ext) == 0 && extra_types[i].save) return extra_types[i].save(filename, b, pal);
    if (ustricmp(e, "bmp") == 0) return save_bmp(filename, b, pal);
    return save_pcx(filename, b, pal);
}
