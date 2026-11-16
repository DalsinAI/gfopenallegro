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
int makecol(int r, int g, int b) { return makecol8(r, g, b); }
int makecol_depth(int d, int r, int g, int b) { (void)d; return makecol8(r, g, b); }
int makeacol(int r, int g, int b, int a) { (void)a; return makecol8(r, g, b); }
int makeacol_depth(int d, int r, int g, int b, int a) { (void)d; (void)a; return makecol8(r, g, b); }

static int gun(int c, int k)
{
    RGB tmp[256];
    const RGB *p = match_palette(tmp);
    int v = k == 0 ? p[c & 255].r : k == 1 ? p[c & 255].g : p[c & 255].b;
    return a4_pal63to255(v);
}
int getr8(int c) { return gun(c, 0); }
int getg8(int c) { return gun(c, 1); }
int getb8(int c) { return gun(c, 2); }
int getr(int c) { return getr8(c); }
int getg(int c) { return getg8(c); }
int getb(int c) { return getb8(c); }
int geta(int c) { (void)c; return 255; }
int getr_depth(int d, int c) { (void)d; return getr8(c); }
int getg_depth(int d, int c) { (void)d; return getg8(c); }
int getb_depth(int d, int c) { (void)d; return getb8(c); }

void set_color_depth(int depth) { _color_depth = depth; }
int get_color_depth(void) { return _color_depth; }
void set_color_conversion(int mode) { A4S->color_conv = mode; }
int get_color_conversion(void) { return A4S->color_conv; }

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
