/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Fonts: the built-in 8x8 font (`font`), fonts from datafiles (mono and
 * colour ranges, Allegro 4's layout), and text drawing. Text is 8-bit
 * Latin-1: one byte, one character.
 *
 * The built-in glyphs are the public-domain 8x8 VGA-style set (font8x8 by
 * Daniel Hepper, from Marcel Sondaar's and IBM's public-domain VGA fonts),
 * stored here leftmost pixel in the top bit.
 */
#include "a4_internal.h"

BITMAP *a4_read_bitmap(PACKFILE *f, int bits);

/* the character drawn for one a font does not have (allegro_404_char) */
static int allegro_404_char_value(void) { return '^'; }

static const unsigned char builtin_8x8[96][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* ' ' */
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},   /* '!' */
    {0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* '"' */
    {0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00},   /* '#' */
    {0x30, 0x7C, 0xC0, 0x78, 0x0C, 0xF8, 0x30, 0x00},   /* '$' */
    {0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00},   /* '%' */
    {0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00},   /* '&' */
    {0x60, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00},   /* "'" */
    {0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00},   /* '(' */
    {0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00},   /* ')' */
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},   /* '*' */
    {0x00, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x00, 0x00},   /* '+' */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60},   /* ',' */
    {0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00},   /* '-' */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00},   /* '.' */
    {0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00},   /* '/' */
    {0x7C, 0xC6, 0xCE, 0xDE, 0xF6, 0xE6, 0x7C, 0x00},   /* '0' */
    {0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00},   /* '1' */
    {0x78, 0xCC, 0x0C, 0x38, 0x60, 0xCC, 0xFC, 0x00},   /* '2' */
    {0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78, 0x00},   /* '3' */
    {0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00},   /* '4' */
    {0xFC, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00},   /* '5' */
    {0x38, 0x60, 0xC0, 0xF8, 0xCC, 0xCC, 0x78, 0x00},   /* '6' */
    {0xFC, 0xCC, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00},   /* '7' */
    {0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78, 0x00},   /* '8' */
    {0x78, 0xCC, 0xCC, 0x7C, 0x0C, 0x18, 0x70, 0x00},   /* '9' */
    {0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00},   /* ':' */
    {0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60},   /* ';' */
    {0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x00},   /* '<' */
    {0x00, 0x00, 0xFC, 0x00, 0x00, 0xFC, 0x00, 0x00},   /* '=' */
    {0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00},   /* '>' */
    {0x78, 0xCC, 0x0C, 0x18, 0x30, 0x00, 0x30, 0x00},   /* '?' */
    {0x7C, 0xC6, 0xDE, 0xDE, 0xDE, 0xC0, 0x78, 0x00},   /* '@' */
    {0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00},   /* 'A' */
    {0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00},   /* 'B' */
    {0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00},   /* 'C' */
    {0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00},   /* 'D' */
    {0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00},   /* 'E' */
    {0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00},   /* 'F' */
    {0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3E, 0x00},   /* 'G' */
    {0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00},   /* 'H' */
    {0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},   /* 'I' */
    {0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00},   /* 'J' */
    {0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00},   /* 'K' */
    {0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00},   /* 'L' */
    {0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00},   /* 'M' */
    {0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00},   /* 'N' */
    {0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00},   /* 'O' */
    {0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00},   /* 'P' */
    {0x78, 0xCC, 0xCC, 0xCC, 0xDC, 0x78, 0x1C, 0x00},   /* 'Q' */
    {0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00},   /* 'R' */
    {0x78, 0xCC, 0xE0, 0x70, 0x1C, 0xCC, 0x78, 0x00},   /* 'S' */
    {0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},   /* 'T' */
    {0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x00},   /* 'U' */
    {0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00},   /* 'V' */
    {0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0xEE, 0xC6, 0x00},   /* 'W' */
    {0xC6, 0xC6, 0x6C, 0x38, 0x38, 0x6C, 0xC6, 0x00},   /* 'X' */
    {0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x78, 0x00},   /* 'Y' */
    {0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00},   /* 'Z' */
    {0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00},   /* '[' */
    {0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00},   /* '\\' */
    {0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00},   /* ']' */
    {0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00},   /* '^' */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   /* '_' */
    {0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},   /* '`' */
    {0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00},   /* 'a' */
    {0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0xDC, 0x00},   /* 'b' */
    {0x00, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00},   /* 'c' */
    {0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00},   /* 'd' */
    {0x00, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00},   /* 'e' */
    {0x38, 0x6C, 0x60, 0xF0, 0x60, 0x60, 0xF0, 0x00},   /* 'f' */
    {0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8},   /* 'g' */
    {0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00},   /* 'h' */
    {0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00},   /* 'i' */
    {0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78},   /* 'j' */
    {0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00},   /* 'k' */
    {0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},   /* 'l' */
    {0x00, 0x00, 0xCC, 0xFE, 0xFE, 0xD6, 0xC6, 0x00},   /* 'm' */
    {0x00, 0x00, 0xF8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00},   /* 'n' */
    {0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x00},   /* 'o' */
    {0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0},   /* 'p' */
    {0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E},   /* 'q' */
    {0x00, 0x00, 0xDC, 0x76, 0x66, 0x60, 0xF0, 0x00},   /* 'r' */
    {0x00, 0x00, 0x7C, 0xC0, 0x78, 0x0C, 0xF8, 0x00},   /* 's' */
    {0x10, 0x30, 0x7C, 0x30, 0x30, 0x34, 0x18, 0x00},   /* 't' */
    {0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00},   /* 'u' */
    {0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00},   /* 'v' */
    {0x00, 0x00, 0xC6, 0xD6, 0xFE, 0xFE, 0x6C, 0x00},   /* 'w' */
    {0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00},   /* 'x' */
    {0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8},   /* 'y' */
    {0x00, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00},   /* 'z' */
    {0x1C, 0x30, 0x30, 0xE0, 0x30, 0x30, 0x1C, 0x00},   /* '{' */
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},   /* '|' */
    {0xE0, 0x30, 0x30, 0x1C, 0x30, 0x30, 0xE0, 0x00},   /* '}' */
    {0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* '~' */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* DEL */
};

/* a font is a list of ranges; each range is mono glyphs or colour bitmaps */
typedef struct a4_range {
    int begin, end;                 /* end is one past the last */
    int mono;
    FONT_GLYPH **glyphs;            /* mono */
    BITMAP **bitmaps;               /* colour */
    struct a4_range *next;
} a4_range;

static int text_bg_mode(void) { return A4S->text_bg; }

static a4_range *range_for(const FONT *f, int c)
{
    a4_range *r;
    for (r = (a4_range *)f->data; r; r = r->next) if (c >= r->begin && c < r->end) return r;
    return NULL;
}

/* width of one character, or of the 404 character when it is missing */
static int char_width(const FONT *f, int c)
{
    a4_range *r = range_for(f, c);
    if (!r) { r = range_for(f, allegro_404_char_value()); c = allegro_404_char_value(); if (!r) return 0; }
    if (r->mono) return r->glyphs[c - r->begin] ? r->glyphs[c - r->begin]->w : 0;
    return r->bitmaps[c - r->begin] ? r->bitmaps[c - r->begin]->w : 0;
}

static FONT *new_mono_font(const unsigned char (*bits)[8], int first, int count)
{
    FONT *f = (FONT *)a4_calloc(sizeof(FONT));
    a4_range *r = (a4_range *)a4_calloc(sizeof(a4_range));
    int i;
    if (!f || !r) { a4_free(f); a4_free(r); return NULL; }
    r->glyphs = (FONT_GLYPH **)a4_calloc(sizeof(FONT_GLYPH *) * (size_t)count);
    if (!r->glyphs) { a4_free(f); a4_free(r); return NULL; }
    r->begin = first; r->end = first + count; r->mono = 1;
    for (i = 0; i < count; i++) {
        FONT_GLYPH *g = (FONT_GLYPH *)a4_malloc(sizeof(FONT_GLYPH) + 8);
        if (!g) continue;
        g->w = 8; g->h = 8;
        memcpy(g->dat, bits[i], 8);
        r->glyphs[i] = g;
    }
    f->data = r;
    f->height = 8;
    return f;
}

FONT *a4_builtin_font(void)
{
    if (!A4S->builtin_font) A4S->builtin_font = new_mono_font(builtin_8x8, 32, 96);
    return A4S->builtin_font;
}

void a4_font_destroy(FONT *f)
{
    a4_range *r, *n;
    int i;
    if (!f) return;
    for (r = (a4_range *)f->data; r; r = n) {
        n = r->next;
        for (i = 0; i < r->end - r->begin; i++) {
            if (r->mono && r->glyphs) a4_free(r->glyphs[i]);
            else if (r->bitmaps) destroy_bitmap(r->bitmaps[i]);
        }
        a4_free(r->glyphs);
        a4_free(r->bitmaps);
        a4_free(r);
    }
    a4_free(f);
}

void a4_font_free_builtin(void)
{
    if (A4S->builtin_font) { a4_font_destroy(A4S->builtin_font); A4S->builtin_font = NULL; }
}

void destroy_font(FONT *f) { if (f && f != A4S->builtin_font) a4_font_destroy(f); }

/* a datafile font: a 16-bit height (> 0: an old 8x8/8x16 fixed font, < 0: an
 * old proportional one, 0: the 4.x form with ranges) */
FONT *a4_read_font_object(PACKFILE *pk)
{
    short height = (short)pack_mgetw(pk);
    FONT *f = (FONT *)a4_calloc(sizeof(FONT));
    a4_range **tail;
    int nranges, maxh = 0;
    if (!f) return NULL;
    tail = (a4_range **)&f->data;
    if (height > 0) {
        /* the old fixed font: 95 characters from ' ', 8 wide, height 8 or 16 */
        a4_range *r = (a4_range *)a4_calloc(sizeof(a4_range));
        int i;
        if (!r) { a4_free(f); return NULL; }
        r->begin = 32; r->end = 32 + 95; r->mono = 1;
        r->glyphs = (FONT_GLYPH **)a4_calloc(sizeof(FONT_GLYPH *) * 95);
        for (i = 0; r->glyphs && i < 95; i++) {
            FONT_GLYPH *g = (FONT_GLYPH *)a4_malloc(sizeof(FONT_GLYPH) + (size_t)height);
            if (!g) break;
            g->w = 8; g->h = height;
            pack_fread(g->dat, height, pk);
            r->glyphs[i] = g;
        }
        *tail = r;
        f->height = height;
        return f;
    }
    if (height < 0) {
        /* the old proportional font: 95 8-bit bitmaps */
        a4_range *r = (a4_range *)a4_calloc(sizeof(a4_range));
        int i;
        if (!r) { a4_free(f); return NULL; }
        r->begin = 32; r->end = 32 + 95; r->mono = 0;
        r->bitmaps = (BITMAP **)a4_calloc(sizeof(BITMAP *) * 95);
        for (i = 0; r->bitmaps && i < 95; i++) {
            if (pack_feof(pk)) { r->bitmaps[i] = create_bitmap(8, maxh ? maxh : 8); continue; }
            r->bitmaps[i] = a4_read_bitmap(pk, 8);
            if (r->bitmaps[i] && r->bitmaps[i]->h > maxh) maxh = r->bitmaps[i]->h;
        }
        *tail = r;
        f->height = maxh;
        return f;
    }
    nranges = pack_mgetw(pk);
    while (nranges-- > 0) {
        int depth = pack_getc(pk);
        a4_range *r = (a4_range *)a4_calloc(sizeof(a4_range));
        int i, n;
        if (!r) break;
        r->begin = (int)pack_mgetl(pk);
        r->end = (int)pack_mgetl(pk) + 1;
        n = r->end - r->begin;
        if (n <= 0 || n > 0x110000) { a4_free(r); break; }
        if (depth == 1 || depth == 255) {
            r->mono = 1;
            r->glyphs = (FONT_GLYPH **)a4_calloc(sizeof(FONT_GLYPH *) * (size_t)n);
            for (i = 0; r->glyphs && i < n; i++) {
                int w = pack_mgetw(pk), h = pack_mgetw(pk), sz = ((w + 7) / 8) * h;
                FONT_GLYPH *g = (FONT_GLYPH *)a4_malloc(sizeof(FONT_GLYPH) + (size_t)(sz > 0 ? sz : 1));
                if (!g) break;
                g->w = (short)w; g->h = (short)h;
                pack_fread(g->dat, sz, pk);
                r->glyphs[i] = g;
                if (h > maxh) maxh = h;
            }
        } else {
            r->mono = 0;
            r->bitmaps = (BITMAP **)a4_calloc(sizeof(BITMAP *) * (size_t)n);
            for (i = 0; r->bitmaps && i < n; i++) {
                r->bitmaps[i] = a4_read_bitmap(pk, depth == 0 ? 8 : depth);
                if (r->bitmaps[i] && r->bitmaps[i]->h > maxh) maxh = r->bitmaps[i]->h;
            }
        }
        *tail = r;
        tail = &r->next;
    }
    f->height = maxh;
    return f;
}

FONT *load_font(const char *filename, RGB *pal, void *param)
{
    DATAFILE *d;
    FONT *f = NULL;
    int i;
    (void)param;
    {   /* a picture of a glyph grid, as Allegro 4.2's load_font */
        const char *e = get_extension(filename);
        if (e && (!ustricmp(e, "pcx") || !ustricmp(e, "bmp") || !ustricmp(e, "tga") || !ustricmp(e, "lbm")))
            return load_bitmap_font(filename, pal, param);
    }
    d = load_datafile(filename);
    if (!d) return NULL;
    for (i = 0; d[i].type != DAT_END; i++) {
        if (d[i].type == DAT_PALETTE && pal) memcpy(pal, d[i].dat, sizeof(PALETTE));
        if (d[i].type == DAT_FONT && !f) { f = (FONT *)d[i].dat; d[i].dat = NULL; d[i].type = DAT_DATA; }
    }
    unload_datafile(d);
    return f;
}

FONT *load_dat_font(const char *filename, RGB *pal, void *param)
{
    char **names = (char **)param;
    DATAFILE *d, *fo = NULL, *po = NULL;
    FONT *f = NULL;
    int i;
    d = load_datafile(filename);
    if (!d) return NULL;
    if (names && names[0]) fo = find_datafile_object(d, names[0]);
    else for (i = 0; d[i].type != DAT_END && !fo; i++) if (d[i].type == DAT_FONT) fo = &d[i];
    if (names && names[1]) po = find_datafile_object(d, names[1]);
    else for (i = 0; d[i].type != DAT_END && !po; i++) if (d[i].type == DAT_PALETTE) po = &d[i];
    if (fo && fo->type == DAT_FONT) { f = (FONT *)fo->dat; fo->dat = NULL; fo->type = DAT_DATA; }
    if (f && pal && po && po->type == DAT_PALETTE) memcpy(pal, po->dat, sizeof(PALETTE));
    unload_datafile(d);
    return f;
}

/* Allegro's font bitmap layout: the top-left pixel's colour draws a box
 * round each glyph; a glyph's top-left corner is where that colour has
 * three neighbours and the fourth (down-right) is not it */
static int grab_find(BITMAP *b, uint32_t border, int *x, int *y, int *w, int *h)
{
    int d = a4_bdepth(b);
#define PX(yy, xx) a4_rd(b->line[yy], xx, d)
    for (;;) {
        if (*x >= b->w - 1) { *x = 0; (*y)++; if (*y >= b->h - 1) return 0; }
        if (PX(*y, *x) == border && PX(*y, *x + 1) == border &&
            PX(*y + 1, *x) == border && PX(*y + 1, *x + 1) != border) break;
        (*x)++;
    }
    *w = 1;
    while (*x + *w + 1 < b->w && PX(*y + 1, *x + *w + 1) != border) (*w)++;
    *h = 1;
    while (*y + *h + 1 < b->h && PX(*y + *h + 1, *x + 1) != border) (*h)++;
    return 1;
#undef PX
}

FONT *grab_font_from_bitmap(BITMAP *bmp)
{
    FONT *f;
    a4_range *r;
    int x, y, w, h, n = 0, mono = 1, maxh = 0, i, j, d;
    uint32_t border, bg, other = 0xFFFFFFFFu;
    if (!bmp || bmp->w < 2 || bmp->h < 2) return NULL;
    d = a4_bdepth(bmp);
    bg = d == 8 ? 0 : a4_maskc(d);              /* a glyph's clear pixels */
    border = a4_rd(bmp->line[0], 0, d);
    /* count the glyphs; mono when they hold 0 and at most one other colour */
    for (x = 0, y = 0; grab_find(bmp, border, &x, &y, &w, &h); x += w) {
        n++;
        for (j = 0; j < h && mono; j++)
            for (i = 0; i < w; i++) {
                uint32_t p = a4_rd(bmp->line[y + 1 + j], x + 1 + i, d);
                if (p == bg) continue;
                if (other != 0xFFFFFFFFu && p != other) { mono = 0; break; }
                other = p;
            }
    }
    if (n == 0) return NULL;
    f = (FONT *)a4_calloc(sizeof(FONT));
    r = (a4_range *)a4_calloc(sizeof(a4_range));
    if (!f || !r) { a4_free(f); a4_free(r); return NULL; }
    r->begin = 32; r->end = 32 + n; r->mono = mono;
    if (mono) r->glyphs = (FONT_GLYPH **)a4_calloc(sizeof(FONT_GLYPH *) * (size_t)n);
    else r->bitmaps = (BITMAP **)a4_calloc(sizeof(BITMAP *) * (size_t)n);
    if (!r->glyphs && !r->bitmaps) { a4_free(f); a4_free(r); return NULL; }
    f->data = r;
    for (n = 0, x = 0, y = 0; grab_find(bmp, border, &x, &y, &w, &h); x += w, n++) {
        if (h > maxh) maxh = h;
        if (mono) {
            int stride = (w + 7) / 8;
            FONT_GLYPH *g = (FONT_GLYPH *)a4_calloc(sizeof(FONT_GLYPH) + (size_t)(stride * h));
            if (!g) continue;
            g->w = (short)w; g->h = (short)h;
            for (j = 0; j < h; j++)
                for (i = 0; i < w; i++)
                    if (a4_rd(bmp->line[y + 1 + j], x + 1 + i, d) != bg) g->dat[j * stride + (i >> 3)] |= (unsigned char)(0x80 >> (i & 7));
            r->glyphs[n] = g;
        } else {
            BITMAP *g = create_bitmap_ex(d, w, h);
            if (!g) continue;
            for (j = 0; j < h; j++) memcpy(g->line[j], bmp->line[y + 1 + j] + (x + 1) * a4_bpp(d), (size_t)(w * a4_bpp(d)));
            r->bitmaps[n] = g;
        }
    }
    f->height = maxh;
    return f;
}

/* ---- drawing text ------------------------------------------------------------------ */

/* one character at x; returns its width. color -1: a colour font draws in
 * its own colours (a mono font then uses colour 255... Allegro uses the
 * glyph colours; mono with -1 draws nothing extra) */
static int draw_char(BITMAP *bmp, const FONT *f, int c, int x, int y, int color, int bg)
{
    a4_range *r = range_for(f, c);
    int l, t, rr, b, i, j, w, h, d = a4_bdepth(bmp);
    if (!r) { c = allegro_404_char_value(); r = range_for(f, c); if (!r) return 0; }
    if (bmp->clip) { l = bmp->cl; t = bmp->ct; rr = bmp->cr; b = bmp->cb; }
    else { l = 0; t = 0; rr = bmp->w; b = bmp->h; }
    if (r->mono) {
        FONT_GLYPH *g = r->glyphs[c - r->begin];
        int stride;
        if (!g) return 0;
        w = g->w; h = g->h; stride = (w + 7) / 8;
        for (j = 0; j < h; j++) {
            int yy = y + j;
            if (yy < t || yy >= b) continue;
            for (i = 0; i < w; i++) {
                int xx = x + i, on = (g->dat[j * stride + (i >> 3)] >> (7 - (i & 7))) & 1;
                if (xx < l || xx >= rr) continue;
                if (on) { if (color >= 0) a4_wr(bmp->line[yy], xx, d, (uint32_t)color); }
                else if (bg >= 0) a4_wr(bmp->line[yy], xx, d, (uint32_t)bg);
            }
        }
        return w;
    } else {
        BITMAP *s = r->bitmaps[c - r->begin];
        int sd;
        uint32_t smask;
        if (!s) return 0;
        sd = a4_bdepth(s);
        smask = a4_maskc(sd);
        for (j = 0; j < s->h; j++) {
            int yy = y + j;
            if (yy < t || yy >= b) continue;
            for (i = 0; i < s->w; i++) {
                int xx = x + i;
                uint32_t p;
                if (xx < l || xx >= rr) continue;
                p = a4_rd(s->line[j], i, sd);
                if (p != smask) a4_wr(bmp->line[yy], xx, d, color >= 0 ? (uint32_t)color : a4_convert(p, sd, d));
                else if (bg >= 0) a4_wr(bmp->line[yy], xx, d, (uint32_t)bg);
            }
        }
        return s->w;
    }
}

int text_length(const FONT *f, const char *s)
{
    int w = 0;
    if (!f || !s) return 0;
    while (*s) w += char_width(f, (unsigned char)*s++);
    return w;
}

int text_height(const FONT *f) { return f ? f->height : 0; }

void textout_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg)
{
    if (!bmp || !f || !s) return;
    while (*s) x += draw_char(bmp, f, (unsigned char)*s++, x, y, color, bg);
    a4_mark_screen(bmp);
}

void textout_centre_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg)
{ textout_ex(bmp, f, s, x - text_length(f, s) / 2, y, color, bg); }

void textout_right_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg)
{ textout_ex(bmp, f, s, x - text_length(f, s), y, color, bg); }

void textout_justify_ex(BITMAP *bmp, const FONT *f, const char *s, int x1, int x2, int y, int diff, int color, int bg)
{
    char buf[A4_TEXT_MAX];
    const char *words[128];
    int nwords = 0, total = 0, i, space, x;
    char *p;
    if (!s) return;
    ustrzcpy(buf, (int)sizeof(buf), s);
    for (p = buf; *p && nwords < 128;) {
        while (*p == ' ') *p++ = 0;
        if (!*p) break;
        words[nwords++] = p;
        while (*p && *p != ' ') p++;
    }
    for (i = 0; i < nwords; i++) total += text_length(f, words[i]);
    space = x2 - x1 - total;
    if (nwords < 2 || space > diff || space < 0) { textout_ex(bmp, f, s, x1, y, color, bg); return; }
    x = x1;
    for (i = 0; i < nwords; i++) {
        textout_ex(bmp, f, words[i], x, y, color, bg);
        x += text_length(f, words[i]);
        if (i < nwords - 1) x += space / (nwords - 1) + (i < space % (nwords - 1) ? 1 : 0);
    }
}

int text_mode(int mode) { int old = A4S->text_bg; A4S->text_bg = mode; return old; }
void textout(BITMAP *b, const FONT *f, const char *s, int x, int y, int c) { textout_ex(b, f, s, x, y, c, text_bg_mode()); }
void textout_centre(BITMAP *b, const FONT *f, const char *s, int x, int y, int c) { textout_centre_ex(b, f, s, x, y, c, text_bg_mode()); }
void textout_right(BITMAP *b, const FONT *f, const char *s, int x, int y, int c) { textout_right_ex(b, f, s, x, y, c, text_bg_mode()); }
void textout_justify(BITMAP *b, const FONT *f, const char *s, int x1, int x2, int y, int diff, int c)
{ textout_justify_ex(b, f, s, x1, x2, y, diff, c, text_bg_mode()); }

int font_has_alpha(FONT *f) { (void)f; return FALSE; }
int is_color_font(FONT *f) { return f && f->data && !((a4_range *)f->data)->mono; }
int is_mono_font(FONT *f) { return f && f->data && ((a4_range *)f->data)->mono; }
int get_font_ranges(FONT *f) { int n = 0; a4_range *r; if (!f) return -1; for (r = (a4_range *)f->data; r; r = r->next) n++; return n; }
int get_font_range_begin(FONT *f, int range)
{
    a4_range *r; int n = 0;
    if (!f) return -1;
    for (r = (a4_range *)f->data; r; r = r->next, n++) if (n == range || range == -1) return r->begin;
    return -1;
}
int get_font_range_end(FONT *f, int range)
{
    a4_range *r, *last = NULL; int n = 0;
    if (!f) return -1;
    for (r = (a4_range *)f->data; r; r = r->next, n++) { last = r; if (n == range) return r->end - 1; }
    return (range == -1 && last) ? last->end - 1 : -1;
}

/* ---- fonts from a picture ------------------------------------------------------------- */

FONT *load_bitmap_font(const char *filename, RGB *pal, void *param)
{
    BITMAP *b;
    FONT *f;
    (void)param;
    b = load_bitmap(filename, pal);
    if (!b) return NULL;
    f = grab_font_from_bitmap(b);
    destroy_bitmap(b);
    return f;
}

void make_trans_font(FONT *f) { (void)f; }

#ifdef A4_WRITERS
/* ---- the font object a4_read_font_object reads, for the host's dat (tools/a4dat) ------------- */

static void write_glyph_bitmap(PACKFILE *pk, BITMAP *b)
{
    int x, y, d = a4_bdepth(b);
    pack_mputw(b->w, pk);
    pack_mputw(b->h, pk);
    for (y = 0; y < b->h; y++) {
        if (d == 8) { pack_fwrite(b->line[y], b->w, pk); continue; }
        for (x = 0; x < b->w; x++) {
            uint32_t c = a4_rd(b->line[y], x, d);
            int r, g, bl;
            if (c == a4_maskc(d)) { r = 255; g = 0; bl = 255; }
            else a4_unpack(d, c, &r, &g, &bl);
            if (d == 15 || d == 16) pack_iputw(((r >> 3) << 11) | ((g >> 2) << 5) | (bl >> 3), pk);
            else { pack_putc(r, pk); pack_putc(g, pk); pack_putc(bl, pk); }
        }
    }
}

/* 0 (the new format), the number of ranges, then each range: its depth (1 a mono range, 0 an 8-bit
 * colour one, else the colour depth), its first and last character, and each glyph (mono: width,
 * height and the bits, a row a whole byte; colour: width, height and the pixels), as Allegro 4's
 * grabber writes a font */
int a4_write_font_object(PACKFILE *pk, FONT *f)
{
    a4_range *r;
    int n = 0, i;
    if (!f || !pk) return -1;
    for (r = (a4_range *)f->data; r; r = r->next) n++;
    pack_mputw(0, pk);
    pack_mputw(n, pk);
    for (r = (a4_range *)f->data; r; r = r->next) {
        int count = r->end - r->begin, depth = 8;
        if (!r->mono) for (i = 0; i < count; i++) if (r->bitmaps[i]) { depth = a4_bdepth(r->bitmaps[i]); break; }
        pack_putc(r->mono ? 1 : depth == 8 ? 0 : depth, pk);
        pack_mputl(r->begin, pk);
        pack_mputl(r->end - 1, pk);
        for (i = 0; i < count; i++) {
            if (r->mono) {
                FONT_GLYPH *g = r->glyphs[i];
                pack_mputw(g ? g->w : 0, pk);
                pack_mputw(g ? g->h : 0, pk);
                if (g) pack_fwrite(g->dat, ((g->w + 7) / 8) * g->h, pk);
            } else if (r->bitmaps[i]) write_glyph_bitmap(pk, r->bitmaps[i]);
            else { pack_mputw(0, pk); pack_mputw(0, pk); }
        }
    }
    return pack_ferror(pk) ? -1 : 0;
}
#endif
