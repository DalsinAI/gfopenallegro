/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * The 256-colour palette (6 bits a gun, as Allegro 4 keeps it), fades,
 * colour matching and the colour tables (RGB_MAP, COLOR_MAP).
 */
#include "a4_internal.h"

void set_color(int idx, const RGB *p)
{
    if (idx < 0 || idx > 255 || !p) return;
    A4S->palette[idx][0] = p->r & 63;
    A4S->palette[idx][1] = p->g & 63;
    A4S->palette[idx][2] = p->b & 63;
    A4S->palette_dirty = 1;
    if (_color_depth != 8 && A4S->pub && palette_color)
        palette_color[idx] = makecol_depth(_color_depth, a4_pal63to255(p->r & 63), a4_pal63to255(p->g & 63), a4_pal63to255(p->b & 63));
}

void set_palette_range(const PALETTE p, int from, int to, int retracesync)
{
    int i;
    (void)retracesync;
    if (!p) return;
    if (from < 0) from = 0;
    if (to > 255) to = 255;
    for (i = from; i <= to; i++) set_color(i, &p[i]);
    /* a palette change is seen straight away, as on a VGA card: fades
     * that set the palette and wait call this in a loop */
    a4_present_if_dirty();
}

void set_palette(const PALETTE p) { set_palette_range(p, 0, 255, TRUE); }

void get_color(int idx, RGB *p)
{
    if (idx < 0 || idx > 255 || !p) return;
    p->r = A4S->palette[idx][0];
    p->g = A4S->palette[idx][1];
    p->b = A4S->palette[idx][2];
    p->filler = 0;
}

void get_palette_range(PALETTE p, int from, int to)
{
    int i;
    for (i = from; i <= to && i < 256; i++) if (i >= 0) get_color(i, &p[i]);
}

void get_palette(PALETTE p) { get_palette_range(p, 0, 255); }

void select_palette(const PALETTE p)
{
    memcpy(A4S->selected_copy, p, sizeof(PALETTE));
    A4S->has_selected = 1;
}
void unselect_palette(void) { A4S->has_selected = 0; }

/* the palette colour matching works on: select_palette's, else the shown one */
static const RGB *match_palette(RGB *tmp)
{
    if (A4S->has_selected) return A4S->selected_copy;
    get_palette(tmp);
    return tmp;
}

void fade_interpolate(const PALETTE src, const PALETTE dst, PALETTE out, int pos, int from, int to)
{
    int i;
    for (i = from; i <= to && i < 256; i++) {
        out[i].r = (unsigned char)(((int)src[i].r * (63 - pos) + (int)dst[i].r * pos) / 63);
        out[i].g = (unsigned char)(((int)src[i].g * (63 - pos) + (int)dst[i].g * pos) / 63);
        out[i].b = (unsigned char)(((int)src[i].b * (63 - pos) + (int)dst[i].b * pos) / 63);
    }
}

void fade_from_range(const PALETTE src, const PALETTE dst, int speed, int from, int to)
{
    PALETTE tmp;
    int c;
    uint64_t start;
    memcpy(tmp, src, sizeof(PALETTE));
    if (speed <= 0) speed = 1;
    if (speed > 64) speed = 64;
    /* Allegro's speed is steps per retrace at 70 Hz: 64 steps / speed */
    start = a4_os_micros();
    for (c = 0; c < 64; c += speed) {
        uint64_t due = start + (uint64_t)(c / speed + 1) * 1000000u / 70u;
        fade_interpolate(src, dst, tmp, c, from, to);
        set_palette_range(tmp, from, to, TRUE);
        a4_poll_point();
        while (a4_os_micros() < due) a4_os_delay_ms(1);
    }
    set_palette_range(dst, from, to, TRUE);
}

void fade_in_range(const PALETTE p, int speed, int from, int to)
{
    PALETTE black;
    memset(black, 0, sizeof(black));
    fade_from_range(black, p, speed, from, to);
}

void fade_out_range(int speed, int from, int to)
{
    PALETTE cur, black;
    get_palette(cur);
    memset(black, 0, sizeof(black));
    fade_from_range(cur, black, speed, from, to);
}

void fade_from(const PALETTE s, const PALETTE d, int speed) { fade_from_range(s, d, speed, 0, 255); }
void fade_in(const PALETTE p, int speed) { fade_in_range(p, speed, 0, 255); }
void fade_out(int speed) { fade_out_range(speed, 0, 255); }

void generate_332_palette(PALETTE pal)
{
    int c;
    for (c = 0; c < 256; c++) {
        pal[c].r = (unsigned char)(((c >> 5) & 7) * 63 / 7);
        pal[c].g = (unsigned char)(((c >> 2) & 7) * 63 / 7);
        pal[c].b = (unsigned char)((c & 3) * 63 / 3);
        pal[c].filler = 0;
    }
    pal[0].r = 63; pal[0].g = 0; pal[0].b = 63;         /* Allegro's mask colour pink */
    pal[254].r = pal[254].g = pal[254].b = 0;
}

int generate_optimized_palette(BITMAP *image, PALETTE pal, const signed char rsvd[256])
{
    (void)image; (void)rsvd;
    generate_332_palette(pal);
    return 256;
}

/* nearest colour in 6-bit space, skipping 0 (the mask) unless asked for black-ish 0 */
int bestfit_color(const PALETTE pal, int r, int g, int b)
{
    int i, best = 1, bestd = INT_MAX;
    for (i = 1; i < 256; i++) {
        int dr = (int)pal[i].r - r, dg = (int)pal[i].g - g, db = (int)pal[i].b - b;
        int d = dr * dr * 3 + dg * dg * 4 + db * db * 2;
        if (d < bestd) { bestd = d; best = i; if (!d) break; }
    }
    return best;
}

int makecol8(int r, int g, int b)
{
    RGB tmp[256];
    if (rgb_map) return rgb_map->data[(r & 255) >> 3][(g & 255) >> 3][(b & 255) >> 3];
    return bestfit_color(match_palette(tmp), (r & 255) >> 2, (g & 255) >> 2, (b & 255) >> 2);
}
int makecol15(int r, int g, int b) { return ((r & 255) >> 3) << 10 | ((g & 255) >> 3) << 5 | (b & 255) >> 3; }
int makecol16(int r, int g, int b) { return ((r & 255) >> 3) << 11 | ((g & 255) >> 2) << 5 | (b & 255) >> 3; }
int makecol24(int r, int g, int b) { return (r & 255) << 16 | (g & 255) << 8 | (b & 255); }
int makecol32(int r, int g, int b) { return (r & 255) << 16 | (g & 255) << 8 | (b & 255); }
int makeacol32(int r, int g, int b, int a) { return (int)((uint32_t)(a & 255) << 24 | (uint32_t)makecol32(r, g, b)); }
int makecol_depth(int d, int r, int g, int b)
{
    switch (d) {
    case 15: return makecol15(r, g, b);
    case 16: return makecol16(r, g, b);
    case 24: return makecol24(r, g, b);
    case 32: return makecol32(r, g, b);
    default: return makecol8(r, g, b);
    }
}
int makeacol_depth(int d, int r, int g, int b, int a) { return d == 32 ? makeacol32(r, g, b, a) : makecol_depth(d, r, g, b); }
int makecol(int r, int g, int b) { return makecol_depth(_color_depth, r, g, b); }
int makeacol(int r, int g, int b, int a) { return makeacol_depth(_color_depth, r, g, b, a); }

static int gun(int c, int k)
{
    RGB tmp[256];
    const RGB *p = match_palette(tmp);
    int v = k == 0 ? p[c & 255].r : k == 1 ? p[c & 255].g : p[c & 255].b;
    return a4_pal63to255(v);
}
static int s5(int v) { v &= 31; return (v << 3) | (v >> 2); }
static int s6(int v) { v &= 63; return (v << 2) | (v >> 4); }
int getr8(int c) { return gun(c, 0); }
int getg8(int c) { return gun(c, 1); }
int getb8(int c) { return gun(c, 2); }
int getr15(int c) { return s5(c >> 10); }
int getg15(int c) { return s5(c >> 5); }
int getb15(int c) { return s5(c); }
int getr16(int c) { return s5(c >> 11); }
int getg16(int c) { return s6(c >> 5); }
int getb16(int c) { return s5(c); }
int getr24(int c) { return (c >> 16) & 255; }
int getg24(int c) { return (c >> 8) & 255; }
int getb24(int c) { return c & 255; }
int getr32(int c) { return (c >> 16) & 255; }
int getg32(int c) { return (c >> 8) & 255; }
int getb32(int c) { return c & 255; }
int geta32(int c) { return (int)(((uint32_t)c >> 24) & 255); }
int getr_depth(int d, int c) { int r, g, b; a4_unpack(d, (uint32_t)c, &r, &g, &b); return r; }
int getg_depth(int d, int c) { int r, g, b; a4_unpack(d, (uint32_t)c, &r, &g, &b); return g; }
int getb_depth(int d, int c) { int r, g, b; a4_unpack(d, (uint32_t)c, &r, &g, &b); return b; }
int geta_depth(int d, int c) { return d == 32 ? geta32(c) : 255; }
int getr(int c) { return getr_depth(_color_depth, c); }
int getg(int c) { return getg_depth(_color_depth, c); }
int getb(int c) { return getb_depth(_color_depth, c); }
int geta(int c) { return geta_depth(_color_depth, c); }

uint32_t a4_pack(int depth, int r, int g, int b) { return (uint32_t)makecol_depth(depth, r, g, b); }

void a4_unpack(int depth, uint32_t c, int *r, int *g, int *b)
{
    switch (depth) {
    case 15: *r = getr15((int)c); *g = getg15((int)c); *b = getb15((int)c); break;
    case 16: *r = getr16((int)c); *g = getg16((int)c); *b = getb16((int)c); break;
    case 24: case 32: *r = (int)(c >> 16) & 255; *g = (int)(c >> 8) & 255; *b = (int)c & 255; break;
    default: *r = getr8((int)c); *g = getg8((int)c); *b = getb8((int)c); break;
    }
}

uint32_t a4_convert(uint32_t c, int from, int to)
{
    int r, g, b;
    if (from == to) return c;
    if ((from == 24 && to == 32) || (from == 32 && to == 24)) return c & 0xFFFFFF;
    a4_unpack(from, c, &r, &g, &b);
    return a4_pack(to, r, g, b);
}

void a4_expand_palette(int depth, const RGB *pal, uint32_t out[256])
{
    RGB tmp[256];
    int i;
    if (!pal) pal = match_palette(tmp);
    for (i = 0; i < 256; i++)
        out[i] = depth == 8 ? (uint32_t)i : a4_pack(depth, a4_pal63to255(pal[i].r & 63), a4_pal63to255(pal[i].g & 63), a4_pal63to255(pal[i].b & 63));
}

/* palette_color: the index in 8-bit, the palette's colours at a truecolour depth */
void a4_update_palette_color(void)
{
    uint32_t e[256];
    int i;
    if (!A4S->pub || !palette_color) return;
    a4_expand_palette(_color_depth, NULL, e);
    for (i = 0; i < 256; i++) palette_color[i] = (int)e[i];
}

void set_color_depth(int depth)
{
    if (!a4_valid_depth(depth)) return;
    _color_depth = depth;
    a4_update_palette_color();
}
int get_color_depth(void) { return _color_depth; }
void set_color_conversion(int mode) { A4S->color_conv = mode; }
int get_color_conversion(void) { return A4S->color_conv; }

/* ---- blenders (truecolour translucency) -------------------------------------------- */

static void set_blender(int kind, int r, int g, int b, int a)
{
    A4S->blend_kind = kind;
    A4S->blend_r = r & 255; A4S->blend_g = g & 255; A4S->blend_b = b & 255; A4S->blend_a = a & 255;
}
void set_trans_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_TRANS, r, g, b, a); }
void set_alpha_blender(void) { set_blender(A4_BLEND_ALPHA, 0, 0, 0, 255); }
void set_write_alpha_blender(void) { set_blender(A4_BLEND_WRITE_ALPHA, 0, 0, 0, 255); }
void set_add_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_ADD, r, g, b, a); }
void set_burn_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_BURN, r, g, b, a); }
void set_difference_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_DIFFERENCE, r, g, b, a); }
void set_dodge_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_DODGE, r, g, b, a); }
void set_invert_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_INVERT, r, g, b, a); }
void set_multiply_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_MULTIPLY, r, g, b, a); }
void set_screen_blender(int r, int g, int b, int a) { set_blender(A4_BLEND_SCREEN, r, g, b, a); }

/* one gun: the blend's own result for x over y */
static int blend_gun(int kind, int x, int y)
{
    switch (kind) {
    case A4_BLEND_ADD: return x + y > 255 ? 255 : x + y;
    case A4_BLEND_BURN: return x + y - 255 < 0 ? 0 : x + y - 255;
    case A4_BLEND_DIFFERENCE: return x > y ? x - y : y - x;
    case A4_BLEND_DODGE: return x == 255 ? 255 : (y * 255 / (255 - x) > 255 ? 255 : y * 255 / (255 - x));
    case A4_BLEND_INVERT: return 255 - x;
    case A4_BLEND_MULTIPLY: return x * y / 255;
    case A4_BLEND_SCREEN: return 255 - (255 - x) * (255 - y) / 255;
    default: return x;                                  /* trans */
    }
}

/* Allegro's blenders: the blend's result, then n of it over y (n 0-255;
 * the alpha blender takes n from x's own alpha, a 32-bit colour) */
uint32_t a4_blend(int depth, uint32_t x, uint32_t y, int n)
{
    int xr, xg, xb, yr, yg, yb, kind = A4S->blend_kind;
    if (kind == A4_BLEND_WRITE_ALPHA) return depth == 32 ? (y & 0xFFFFFF) | ((uint32_t)(n & 255) << 24) : y;
    if (kind == A4_BLEND_ALPHA) { n = (int)(x >> 24) & 255; x &= 0xFFFFFF; a4_unpack(32, x, &xr, &xg, &xb); }
    else a4_unpack(depth, x, &xr, &xg, &xb);
    a4_unpack(depth, y, &yr, &yg, &yb);
    if (n >= 255) n = 256;
    xr = blend_gun(kind, xr, yr); xg = blend_gun(kind, xg, yg); xb = blend_gun(kind, xb, yb);
    return a4_pack(depth, yr + (xr - yr) * n / 256, yg + (xg - yg) * n / 256, yb + (xb - yb) * n / 256);
}

void create_rgb_table(RGB_MAP *table, const PALETTE pal, void (*callback)(int pos))
{
    int r, g, b;
    for (r = 0; r < 32; r++) {
        for (g = 0; g < 32; g++)
            for (b = 0; b < 32; b++)
                table->data[r][g][b] = (unsigned char)bestfit_color(pal, r * 2 + 1, g * 2 + 1, b * 2 + 1);
        if (callback) callback(r * 8);
    }
}

void create_color_table(COLOR_MAP *table, const PALETTE pal,
                        void (*blend)(const PALETTE pal, int x, int y, RGB *rgb), void (*callback)(int pos))
{
    int x, y;
    for (x = 0; x < 256; x++) {
        for (y = 0; y < 256; y++) {
            RGB c;
            blend(pal, x, y, &c);
            table->data[x][y] = rgb_map ? rgb_map->data[c.r >> 1][c.g >> 1][c.b >> 1]
                                        : (unsigned char)bestfit_color(pal, c.r, c.g, c.b);
        }
        if (callback) callback(x);
    }
}

void create_trans_table(COLOR_MAP *table, const PALETTE pal, int r, int g, int b, void (*callback)(int pos))
{
    int x, y;
    for (x = 0; x < 256; x++) {
        for (y = 0; y < 256; y++) {
            int rr = ((int)pal[x].r * r + (int)pal[y].r * (256 - r)) >> 8;
            int gg = ((int)pal[x].g * g + (int)pal[y].g * (256 - g)) >> 8;
            int bb = ((int)pal[x].b * b + (int)pal[y].b * (256 - b)) >> 8;
            table->data[x][y] = rgb_map ? rgb_map->data[rr >> 1][gg >> 1][bb >> 1]
                                        : (unsigned char)bestfit_color(pal, rr, gg, bb);
        }
        if (callback) callback(x);
    }
}

void create_light_table(COLOR_MAP *table, const PALETTE pal, int r, int g, int b, void (*callback)(int pos))
{
    int x, y;
    for (x = 0; x < 256; x++) {       /* x: the light level, y: the colour */
        for (y = 0; y < 256; y++) {
            int rr = ((int)pal[y].r * x + r * (255 - x)) / 255;
            int gg = ((int)pal[y].g * x + g * (255 - x)) / 255;
            int bb = ((int)pal[y].b * x + b * (255 - x)) / 255;
            if (rr > 63) rr = 63;
            if (gg > 63) gg = 63;
            if (bb > 63) bb = 63;
            table->data[x][y] = rgb_map ? rgb_map->data[rr >> 1][gg >> 1][bb >> 1]
                                        : (unsigned char)bestfit_color(pal, rr, gg, bb);
        }
        if (callback) callback(x);
    }
}

void create_blender_table(COLOR_MAP *table, const PALETTE pal, void (*callback)(int pos))
{
    create_trans_table(table, pal, 128, 128, 128, callback);
}
