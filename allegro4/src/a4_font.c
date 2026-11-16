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
    d = load_datafile(filename);
    if (!d) return NULL;
    for (i = 0; d[i].type != DAT_END; i++) {
        if (d[i].type == DAT_PALETTE && pal) memcpy(pal, d[i].dat, sizeof(PALETTE));
        if (d[i].type == DAT_FONT && !f) { f = (FONT *)d[i].dat; d[i].dat = NULL; d[i].type = DAT_DATA; }
    }
    unload_datafile(d);
    return f;
}

/* ---- drawing text ------------------------------------------------------------------ */

/* one character at x; returns its width. color -1: a colour font draws in
 * its own colours (a mono font then uses colour 255... Allegro uses the
 * glyph colours; mono with -1 draws nothing extra) */
static int draw_char(BITMAP *bmp, const FONT *f, int c, int x, int y, int color, int bg)
{
    a4_range *r = range_for(f, c);
    int l, t, rr, b, i, j, w, h;
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
                if (on) { if (color >= 0) bmp->line[yy][xx] = (unsigned char)color; }
                else if (bg >= 0) bmp->line[yy][xx] = (unsigned char)bg;
            }
        }
        return w;
    } else {
        BITMAP *s = r->bitmaps[c - r->begin];
        if (!s) return 0;
        for (j = 0; j < s->h; j++) {
            int yy = y + j;
            if (yy < t || yy >= b) continue;
            for (i = 0; i < s->w; i++) {
                int xx = x + i, p = s->line[j][i];
                if (xx < l || xx >= rr) continue;
                if (p) bmp->line[yy][xx] = (unsigned char)(color >= 0 ? color : p);
                else if (bg >= 0) bmp->line[yy][xx] = (unsigned char)bg;
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
