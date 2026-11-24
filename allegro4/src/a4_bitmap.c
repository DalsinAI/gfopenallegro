/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Bitmaps (8, 15, 16, 24 and 32-bit, linear, in Fast RAM), clipping and
 * the drawing primitives. The screen is a bitmap like any other; drawing on it marks it
 * to be shown (a4_gfx.c).
 */
#include "a4_internal.h"

/* ---- bitmaps --------------------------------------------------------------- */

/* never written: one per depth, shared by every opener */
static GFX_VTABLE vtables[5] = {
    { 8, MASK_COLOR_8 }, { 15, MASK_COLOR_15 }, { 16, MASK_COLOR_16 }, { 24, MASK_COLOR_24 }, { 32, MASK_COLOR_32 },
};

GFX_VTABLE *a4_vtable(int depth)
{
    switch (depth) {
    case 8: return &vtables[0];
    case 15: return &vtables[1];
    case 16: return &vtables[2];
    case 24: return &vtables[3];
    case 32: return &vtables[4];
    default: return NULL;
    }
}
int a4_valid_depth(int depth) { return a4_vtable(depth) != NULL; }

static BITMAP *new_bitmap_struct(int w, int h)
{
    BITMAP *b = (BITMAP *)a4_calloc(sizeof(BITMAP) + sizeof(unsigned char *) * (size_t)(h > 0 ? h : 1));
    if (!b) return NULL;
    b->w = w;
    b->h = h;
    b->clip = TRUE;
    b->cl = 0; b->ct = 0; b->cr = w; b->cb = h;
    return b;
}

BITMAP *create_bitmap_ex(int color_depth, int width, int height)
{
    BITMAP *b;
    unsigned char *pix;
    GFX_VTABLE *vt = a4_vtable(color_depth);
    size_t pitch;
    int y;
    if (width < 0 || height < 0 || !vt) return NULL;
    b = new_bitmap_struct(width, height);
    if (!b) return NULL;
    /* the rows one after another, as in Allegro 4's memory bitmaps: games read bmp->dat as width x
     * height pixels (Liquid War's maps); 16- and 32-bit pixels stay aligned, a row being whole pixels */
    pitch = (size_t)(width ? width : 1) * (size_t)a4_bpp(color_depth);
    pix = (unsigned char *)a4_calloc(pitch * (size_t)(height ? height : 1));
    if (!pix) { a4_free(b); return NULL; }
    b->vtable = vt;
    b->dat = pix;
    for (y = 0; y < height; y++) b->line[y] = pix + (size_t)y * pitch;
    if (color_depth != 8) {
        /* a new truecolour bitmap is black, as Allegro's are; the mask is
         * only where the game draws it */
    }
    return b;
}

BITMAP *create_bitmap(int width, int height) { return create_bitmap_ex(_color_depth ? _color_depth : 8, width, height); }
BITMAP *create_video_bitmap(int width, int height) { return create_bitmap(width, height); }
BITMAP *create_system_bitmap(int width, int height) { return create_bitmap(width, height); }

BITMAP *create_sub_bitmap(BITMAP *parent, int x, int y, int width, int height)
{
    BITMAP *b;
    int i, bpp;
    if (!parent) return NULL;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > parent->w) width = parent->w - x;
    if (y + height > parent->h) height = parent->h - y;
    if (width < 0 || height < 0) return NULL;
    b = new_bitmap_struct(width, height);
    if (!b) return NULL;
    bpp = a4_bpp(a4_bdepth(parent));
    for (i = 0; i < height; i++) b->line[i] = parent->line[y + i] + x * bpp;
    b->vtable = parent->vtable;
    b->id = BMP_ID_SUB | (parent->id & (BMP_ID_VIDEO | BMP_ID_SYSTEM));
    b->extra = parent;              /* for the screen test */
    b->x_ofs = x + parent->x_ofs;
    b->y_ofs = y + parent->y_ofs;
    return b;
}

void destroy_bitmap(BITMAP *bitmap)
{
    if (!bitmap) return;
    if (bitmap == A4S->screen_bmp) return;  /* set_gfx_mode owns it */
    if (!(bitmap->id & BMP_ID_SUB) && bitmap->dat) a4_free(bitmap->dat);
    a4_free(bitmap);
}

BITMAP *a4_bitmap_root(BITMAP *bmp)
{
    while (bmp && (bmp->id & BMP_ID_SUB) && bmp->extra) bmp = (BITMAP *)bmp->extra;
    return bmp;
}

int a4_is_screen(BITMAP *bmp) { return bmp && A4S->screen_bmp && a4_bitmap_root(bmp) == A4S->screen_bmp; }

/* a copy at another depth: 8-bit through the palette, truecolour to 8-bit
 * by rgb_map or the nearest colour; the mask stays the mask */
BITMAP *a4_bitmap_to_depth(BITMAP *src, int depth, const RGB *pal)
{
    BITMAP *d;
    int sd, x, y;
    uint32_t smask, dmask, exp8[256];
    if (!src) return NULL;
    sd = a4_bdepth(src);
    if (sd == depth || !a4_valid_depth(depth)) return src;
    d = create_bitmap_ex(depth, src->w, src->h);
    if (!d) return NULL;
    smask = a4_maskc(sd);
    dmask = a4_maskc(depth);
    if (sd == 8) a4_expand_palette(depth, pal, exp8);
    for (y = 0; y < src->h; y++)
        for (x = 0; x < src->w; x++) {
            uint32_t c = a4_rd(src->line[y], x, sd);
            if (c == smask) c = dmask;
            else if (sd == 8) c = exp8[c];
            else {
                c = a4_convert(c, sd, depth);
                if (c == dmask && depth != 8) c ^= 1;       /* a real colour that met the mask */
            }
            a4_wr(d->line[y], x, depth, c);
        }
    return d;
}

static int depth_index(int d) { return d == 8 ? 0 : d == 15 ? 1 : d == 16 ? 2 : d == 24 ? 3 : 4; }

/* the COLORCONV_ bit for from -> to: four bits per source depth, the others in order */
static int conv_bit(int from, int to)
{
    int f = depth_index(from), t = depth_index(to);
    return 1 << (f * 4 + (t < f ? t : t - 1));
}

BITMAP *a4_fixup_loaded(BITMAP *b, const RGB *pal)
{
    BITMAP *n;
    int from, to = _color_depth;
    if (!b) return NULL;
    from = a4_bdepth(b);
    if (from == to || !a4_valid_depth(to) || !(A4S->color_conv & conv_bit(from, to))) return b;
    n = a4_bitmap_to_depth(b, to, pal);
    if (!n) return b;
    destroy_bitmap(b);
    return n;
}

int bitmap_color_depth(BITMAP *bmp) { return bmp ? a4_bdepth(bmp) : 0; }
int bitmap_mask_color(BITMAP *bmp) { return bmp ? (int)a4_maskc(a4_bdepth(bmp)) : 0; }
int is_same_bitmap(BITMAP *a, BITMAP *b) { return a && b && a4_bitmap_root(a) == a4_bitmap_root(b); }
int is_linear_bitmap(BITMAP *bmp) { (void)bmp; return TRUE; }
int is_planar_bitmap(BITMAP *bmp) { (void)bmp; return FALSE; }
int is_memory_bitmap(BITMAP *bmp) { return !a4_is_screen(bmp); }
int is_screen_bitmap(BITMAP *bmp) { return a4_is_screen(bmp); }
int is_video_bitmap(BITMAP *bmp) { return a4_is_screen(bmp); }
int is_system_bitmap(BITMAP *bmp) { (void)bmp; return FALSE; }
int is_sub_bitmap(BITMAP *bmp) { return bmp && (bmp->id & BMP_ID_SUB) != 0; }
void acquire_bitmap(BITMAP *bmp) { (void)bmp; }
void release_bitmap(BITMAP *bmp) { if (a4_is_screen(bmp)) a4_mark_screen(bmp); }
void lock_bitmap(BITMAP *bmp) { (void)bmp; }
unsigned long bmp_write_line(BITMAP *bmp, int line) { a4_mark_screen(bmp); return (unsigned long)bmp->line[line]; }
unsigned long bmp_read_line(BITMAP *bmp, int line) { return (unsigned long)bmp->line[line]; }
void bmp_unwrite_line(BITMAP *bmp) { (void)bmp; }
int show_video_bitmap(BITMAP *bitmap) { if (a4_is_screen(bitmap)) a4_present(); return 0; }
int request_video_bitmap(BITMAP *bitmap) { return show_video_bitmap(bitmap); }
int scroll_screen(int x, int y) { return (x || y) ? -1 : 0; }
int request_scroll(int x, int y) { return scroll_screen(x, y); }
int poll_scroll(void) { return 0; }
int enable_triple_buffer(void) { return -1; }

/* ---- clipping ------------------------------------------------------------------ */

void set_clip_rect(BITMAP *b, int x1, int y1, int x2, int y2)
{
    x2++; y2++;
    b->cl = MID(0, x1, b->w - 1);
    b->ct = MID(0, y1, b->h - 1);
    b->cr = MID(0, x2, b->w);
    b->cb = MID(0, y2, b->h);
    if (b->cr < b->cl) b->cr = b->cl;
    if (b->cb < b->ct) b->cb = b->ct;
    if (b->w == 0) { b->cl = b->cr = 0; }
    if (b->h == 0) { b->ct = b->cb = 0; }
    b->clip = TRUE;
}

void add_clip_rect(BITMAP *b, int x1, int y1, int x2, int y2)
{
    int cx1, cy1, cx2, cy2;
    get_clip_rect(b, &cx1, &cy1, &cx2, &cy2);
    set_clip_rect(b, MAX(x1, cx1), MAX(y1, cy1), MIN(x2, cx2), MIN(y2, cy2));
}

void get_clip_rect(BITMAP *b, int *x1, int *y1, int *x2, int *y2)
{
    if (x1) *x1 = b->cl;
    if (y1) *y1 = b->ct;
    if (x2) *x2 = b->cr - 1;
    if (y2) *y2 = b->cb - 1;
}

void set_clip_state(BITMAP *b, int state) { b->clip = state ? TRUE : FALSE; }
int get_clip_state(BITMAP *b) { return b->clip; }

int is_inside_bitmap(BITMAP *b, int x, int y, int clip)
{
    if (clip && b->clip) return x >= b->cl && x < b->cr && y >= b->ct && y < b->cb;
    return x >= 0 && x < b->w && y >= 0 && y < b->h;
}

/* the area drawing may touch */
static inline void clip_box(BITMAP *b, int *l, int *t, int *r, int *bt)
{
    if (b->clip) { *l = b->cl; *t = b->ct; *r = b->cr; *bt = b->cb; }
    else { *l = 0; *t = 0; *r = b->w; *bt = b->h; }
}

/* ---- drawing modes ------------------------------------------------------------- */

void drawing_mode(int mode, BITMAP *pattern, int x_anchor, int y_anchor)
{
    A4S->draw_mode = mode;
    A4S->pattern = pattern;
    A4S->pattern_x = x_anchor;
    A4S->pattern_y = y_anchor;
}
void xor_mode(int on) { drawing_mode(on ? DRAW_MODE_XOR : DRAW_MODE_SOLID, NULL, 0, 0); }
void solid_mode(void) { drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0); }

/* one pixel under the drawing mode, already clipped */
static void plot(BITMAP *b, int x, int y, int c)
{
    int d = a4_bdepth(b);
    unsigned char *row = b->line[y];
    switch (A4S->draw_mode) {
    case DRAW_MODE_SOLID:
        a4_wr(row, x, d, (uint32_t)c);
        break;
    case DRAW_MODE_XOR:
        a4_wr(row, x, d, a4_rd(row, x, d) ^ (uint32_t)c);
        break;
    case DRAW_MODE_TRANS:
        if (d == 8) row[x] = color_map ? color_map->data[c & 255][row[x]] : (unsigned char)c;
        else a4_wr(row, x, d, a4_blend(d, (uint32_t)c, a4_rd(row, x, d), A4S->blend_a));
        break;
    default: {
        BITMAP *pat = A4S->pattern;
        int px, py, pd;
        uint32_t pc;
        if (!pat || pat->w <= 0 || pat->h <= 0) { a4_wr(row, x, d, (uint32_t)c); break; }
        px = (x - A4S->pattern_x) % pat->w; if (px < 0) px += pat->w;
        py = (y - A4S->pattern_y) % pat->h; if (py < 0) py += pat->h;
        pd = a4_bdepth(pat);
        pc = a4_rd(pat->line[py], px, pd);
        if (A4S->draw_mode == DRAW_MODE_COPY_PATTERN) a4_wr(row, x, d, pd == d ? pc : a4_convert(pc, pd, d));
        else if (A4S->draw_mode == DRAW_MODE_SOLID_PATTERN) a4_wr(row, x, d, pc != a4_maskc(pd) ? (uint32_t)c : a4_maskc(d));
        else if (pc != a4_maskc(pd)) a4_wr(row, x, d, (uint32_t)c);   /* masked pattern */
        break;
    }
    }
}

/* a solid run of one colour */
static void fill_run(unsigned char *row, int x1, int n, int d, uint32_t c)
{
    int i;
    switch (d) {
    case 8: memset(row + x1, (int)c, (size_t)n); break;
    case 15: case 16: { uint16_t *p = (uint16_t *)row + x1; for (i = 0; i < n; i++) p[i] = (uint16_t)c; break; }
    case 32: { uint32_t *p = (uint32_t *)row + x1; for (i = 0; i < n; i++) p[i] = c; break; }
    default: for (i = 0; i < n; i++) a4_wr(row, x1 + i, d, c); break;
    }
}

static void span(BITMAP *b, int x1, int x2, int y, int c)
{
    if (A4S->draw_mode == DRAW_MODE_SOLID) {
        fill_run(b->line[y], x1, x2 - x1 + 1, a4_bdepth(b), (uint32_t)c);
    } else {
        int x;
        for (x = x1; x <= x2; x++) plot(b, x, y, c);
    }
}

/* ---- pixels and lines ----------------------------------------------------------- */

void clear_to_color(BITMAP *b, int color)
{
    int l, t, r, bt, y, d = a4_bdepth(b);
    clip_box(b, &l, &t, &r, &bt);
    for (y = t; y < bt; y++) fill_run(b->line[y], l, r - l, d, (uint32_t)color);
    a4_mark_screen(b);
}
void clear_bitmap(BITMAP *b) { clear_to_color(b, 0); }

void putpixel(BITMAP *b, int x, int y, int color)
{
    int l, t, r, bt;
    clip_box(b, &l, &t, &r, &bt);
    if (x < l || x >= r || y < t || y >= bt) return;
    plot(b, x, y, color);
    a4_mark_screen(b);
}
void _putpixel(BITMAP *b, int x, int y, int color) { b->line[y][x] = (unsigned char)color; a4_mark_screen(b); }
void _putpixel15(BITMAP *b, int x, int y, int color) { ((uint16_t *)b->line[y])[x] = (uint16_t)color; a4_mark_screen(b); }
void _putpixel16(BITMAP *b, int x, int y, int color) { ((uint16_t *)b->line[y])[x] = (uint16_t)color; a4_mark_screen(b); }
void _putpixel24(BITMAP *b, int x, int y, int color) { a4_wr(b->line[y], x, 24, (uint32_t)color); a4_mark_screen(b); }
void _putpixel32(BITMAP *b, int x, int y, int color) { ((uint32_t *)b->line[y])[x] = (uint32_t)color; a4_mark_screen(b); }

int getpixel(BITMAP *b, int x, int y)
{
    if (x < 0 || y < 0 || x >= b->w || y >= b->h) return -1;
    return (int)a4_rd(b->line[y], x, a4_bdepth(b));
}
int _getpixel(BITMAP *b, int x, int y) { return b->line[y][x]; }
int _getpixel15(BITMAP *b, int x, int y) { return ((uint16_t *)b->line[y])[x]; }
int _getpixel16(BITMAP *b, int x, int y) { return ((uint16_t *)b->line[y])[x]; }
int _getpixel24(BITMAP *b, int x, int y) { return (int)a4_rd(b->line[y], x, 24); }
int _getpixel32(BITMAP *b, int x, int y) { return (int)((uint32_t *)b->line[y])[x]; }

void hline(BITMAP *b, int x1, int y, int x2, int color)
{
    int l, t, r, bt;
    if (x1 > x2) { int s = x1; x1 = x2; x2 = s; }
    clip_box(b, &l, &t, &r, &bt);
    if (y < t || y >= bt) return;
    if (x1 < l) x1 = l;
    if (x2 >= r) x2 = r - 1;
    if (x1 > x2) return;
    span(b, x1, x2, y, color);
    a4_mark_screen(b);
}

void vline(BITMAP *b, int x, int y1, int y2, int color)
{
    int l, t, r, bt, y;
    if (y1 > y2) { int s = y1; y1 = y2; y2 = s; }
    clip_box(b, &l, &t, &r, &bt);
    if (x < l || x >= r) return;
    if (y1 < t) y1 = t;
    if (y2 >= bt) y2 = bt - 1;
    for (y = y1; y <= y2; y++) plot(b, x, y, color);
    a4_mark_screen(b);
}

void do_line(BITMAP *bmp, int x1, int y1, int x2, int y2, int d, void (*proc)(BITMAP *, int, int, int))
{
    int dx = ABS(x2 - x1), dy = -ABS(y2 - y1);
    int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    for (;;) {
        proc(bmp, x1, y1, d);
        if (x1 == x2 && y1 == y2) break;
        {
            int e2 = 2 * err;
            if (e2 >= dy) { err += dy; x1 += sx; }
            if (e2 <= dx) { err += dx; y1 += sy; }
        }
    }
}

static void line_pixel(BITMAP *b, int x, int y, int c)
{
    int l, t, r, bt;
    clip_box(b, &l, &t, &r, &bt);
    if (x >= l && x < r && y >= t && y < bt) plot(b, x, y, c);
}

void line(BITMAP *b, int x1, int y1, int x2, int y2, int color)
{
    if (y1 == y2) { hline(b, x1, y1, x2, color); return; }
    if (x1 == x2) { vline(b, x1, y1, y2, color); return; }
    do_line(b, x1, y1, x2, y2, color, line_pixel);
    a4_mark_screen(b);
}
void fastline(BITMAP *b, int x1, int y1, int x2, int y2, int color) { line(b, x1, y1, x2, y2, color); }

void rect(BITMAP *b, int x1, int y1, int x2, int y2, int color)
{
    if (x2 < x1) { int s = x1; x1 = x2; x2 = s; }
    if (y2 < y1) { int s = y1; y1 = y2; y2 = s; }
    hline(b, x1, y1, x2, color);
    if (y2 > y1) hline(b, x1, y2, x2, color);
    if (y2 - y1 > 1) {
        vline(b, x1, y1 + 1, y2 - 1, color);
        if (x2 > x1) vline(b, x2, y1 + 1, y2 - 1, color);
    }
}

void rectfill(BITMAP *b, int x1, int y1, int x2, int y2, int color)
{
    int l, t, r, bt, y;
    if (x2 < x1) { int s = x1; x1 = x2; x2 = s; }
    if (y2 < y1) { int s = y1; y1 = y2; y2 = s; }
    clip_box(b, &l, &t, &r, &bt);
    if (x1 < l) x1 = l;
    if (y1 < t) y1 = t;
    if (x2 >= r) x2 = r - 1;
    if (y2 >= bt) y2 = bt - 1;
    if (x1 > x2 || y1 > y2) return;
    for (y = y1; y <= y2; y++) span(b, x1, x2, y, color);
    a4_mark_screen(b);
}

/* ---- circles and ellipses ----------------------------------------------------- */

void do_circle(BITMAP *bmp, int x, int y, int radius, int d, void (*proc)(BITMAP *, int, int, int))
{
    int cx = 0, cy = radius, df = 1 - radius, d_e = 3, d_se = -2 * radius + 5;
    do {
        proc(bmp, x + cx, y + cy, d);
        if (cx) proc(bmp, x - cx, y + cy, d);
        if (cy) proc(bmp, x + cx, y - cy, d);
        if (cx && cy) proc(bmp, x - cx, y - cy, d);
        if (cx != cy) {
            proc(bmp, x + cy, y + cx, d);
            if (cx) proc(bmp, x + cy, y - cx, d);
            if (cy) proc(bmp, x - cy, y + cx, d);
            if (cx && cy) proc(bmp, x - cy, y - cx, d);
        }
        if (df < 0) { df += d_e; d_e += 2; d_se += 2; }
        else { df += d_se; d_e += 2; d_se += 4; cy--; }
        cx++;
    } while (cx <= cy);
}

void circle(BITMAP *b, int x, int y, int radius, int color)
{
    do_circle(b, x, y, radius, color, line_pixel);
    a4_mark_screen(b);
}

void circlefill(BITMAP *b, int x, int y, int radius, int color)
{
    int cx = 0, cy = radius, df = 1 - radius, d_e = 3, d_se = -2 * radius + 5;
    if (radius < 0) return;
    do {
        hline(b, x - cy, y - cx, x + cy, color);
        if (cx) hline(b, x - cy, y + cx, x + cy, color);
        if (df < 0) { df += d_e; d_e += 2; d_se += 2; }
        else {
            if (cx != cy) {
                hline(b, x - cx, y - cy, x + cx, color);
                hline(b, x - cx, y + cy, x + cx, color);
            }
            df += d_se; d_e += 2; d_se += 4; cy--;
        }
        cx++;
    } while (cx <= cy);
}

/* integer midpoint ellipse; calls back each quadrant's points (or spans) */
static void ellipse_points(BITMAP *b, int xc, int yc, int rx, int ry, int color, int fill)
{
    long rx2 = (long)rx * rx, ry2 = (long)ry * ry;
    long x = 0, y = ry;
    long px = 0, py = 2 * rx2 * y;
    long p;
    if (rx <= 0 || ry <= 0) {
        if (fill || 1) hline(b, xc - rx, yc, xc + rx, color), vline(b, xc, yc - ry, yc + ry, color);
        return;
    }
    p = ry2 - rx2 * ry + rx2 / 4;
    while (px < py) {
        if (fill) { hline(b, xc - (int)x, yc + (int)y, xc + (int)x, color); hline(b, xc - (int)x, yc - (int)y, xc + (int)x, color); }
        else {
            line_pixel(b, xc + (int)x, yc + (int)y, color); line_pixel(b, xc - (int)x, yc + (int)y, color);
            line_pixel(b, xc + (int)x, yc - (int)y, color); line_pixel(b, xc - (int)x, yc - (int)y, color);
        }
        x++;
        px += 2 * ry2;
        if (p < 0) p += ry2 + px;
        else { y--; py -= 2 * rx2; p += ry2 + px - py; }
    }
    p = ry2 * (2 * x + 1) * (2 * x + 1) / 4 + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        if (fill) { hline(b, xc - (int)x, yc + (int)y, xc + (int)x, color); hline(b, xc - (int)x, yc - (int)y, xc + (int)x, color); }
        else {
            line_pixel(b, xc + (int)x, yc + (int)y, color); line_pixel(b, xc - (int)x, yc + (int)y, color);
            line_pixel(b, xc + (int)x, yc - (int)y, color); line_pixel(b, xc - (int)x, yc - (int)y, color);
        }
        y--;
        py -= 2 * rx2;
        if (p > 0) p += rx2 - py;
        else { x++; px += 2 * ry2; p += rx2 - py + px; }
    }
    a4_mark_screen(b);
}

void ellipse(BITMAP *b, int x, int y, int rx, int ry, int color) { ellipse_points(b, x, y, rx, ry, color, 0); }
void ellipsefill(BITMAP *b, int x, int y, int rx, int ry, int color) { ellipse_points(b, x, y, rx, ry, color, 1); }

void do_ellipse(BITMAP *bmp, int xc, int yc, int rx, int ry, int d, void (*proc)(BITMAP *, int, int, int))
{
    long rx2 = (long)rx * rx, ry2 = (long)ry * ry, x = 0, y = ry, px = 0, py = 2 * rx2 * y, p;
    if (rx <= 0 || ry <= 0) { proc(bmp, xc, yc, d); return; }
    p = ry2 - rx2 * ry + rx2 / 4;
    while (px < py) {
        proc(bmp, xc + (int)x, yc + (int)y, d); proc(bmp, xc - (int)x, yc + (int)y, d);
        proc(bmp, xc + (int)x, yc - (int)y, d); proc(bmp, xc - (int)x, yc - (int)y, d);
        x++; px += 2 * ry2;
        if (p < 0) p += ry2 + px; else { y--; py -= 2 * rx2; p += ry2 + px - py; }
    }
    p = ry2 * (2 * x + 1) * (2 * x + 1) / 4 + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        proc(bmp, xc + (int)x, yc + (int)y, d); proc(bmp, xc - (int)x, yc + (int)y, d);
        proc(bmp, xc + (int)x, yc - (int)y, d); proc(bmp, xc - (int)x, yc - (int)y, d);
        y--; py -= 2 * rx2;
        if (p > 0) p += rx2 - py; else { x++; px += 2 * ry2; p += rx2 - py + px; }
    }
}

/* ---- polygons ---------------------------------------------------------------------- */

void polygon(BITMAP *b, int vertices, const int *points, int color)
{
    int miny = INT_MAX, maxy = INT_MIN, i, y;
    int xs[64];
    if (vertices < 3) {
        if (vertices == 2) line(b, points[0], points[1], points[2], points[3], color);
        return;
    }
    for (i = 0; i < vertices; i++) {
        if (points[i * 2 + 1] < miny) miny = points[i * 2 + 1];
        if (points[i * 2 + 1] > maxy) maxy = points[i * 2 + 1];
    }
    if (b->clip) { if (miny < b->ct) miny = b->ct; if (maxy >= b->cb) maxy = b->cb - 1; }
    for (y = miny; y <= maxy; y++) {
        int n = 0, j;
        for (i = 0; i < vertices; i++) {
            int x1 = points[i * 2], y1 = points[i * 2 + 1];
            int k = (i + 1) % vertices;
            int x2 = points[k * 2], y2 = points[k * 2 + 1];
            if (y1 == y2) continue;
            if (y1 > y2) { int s = x1; x1 = x2; x2 = s; s = y1; y1 = y2; y2 = s; }
            if (y < y1 || y > y2 || (y == y2 && y2 != maxy)) continue;
            if (n < 64) xs[n++] = x1 + (int)((long)(y - y1) * (x2 - x1) / (y2 - y1));
        }
        for (i = 1; i < n; i++) {         /* insertion sort */
            int v = xs[i];
            for (j = i - 1; j >= 0 && xs[j] > v; j--) xs[j + 1] = xs[j];
            xs[j + 1] = v;
        }
        for (i = 0; i + 1 < n; i += 2) hline(b, xs[i], y, xs[i + 1], color);
    }
    /* the edges, so thin polygons draw like Allegro's */
    for (i = 0; i < vertices; i++) {
        int k = (i + 1) % vertices;
        line(b, points[i * 2], points[i * 2 + 1], points[k * 2], points[k * 2 + 1], color);
    }
}

void triangle(BITMAP *b, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
    int pts[6];
    pts[0] = x1; pts[1] = y1; pts[2] = x2; pts[3] = y2; pts[4] = x3; pts[5] = y3;
    polygon(b, 3, pts, color);
}

/* ---- flood fill (span stack) --------------------------------------------------- */

void floodfill(BITMAP *b, int x, int y, int color)
{
    int l, t, r, bt, sp = 0, cap = 1024, d = a4_bdepth(b);
    uint32_t target;
    int *stack;
    clip_box(b, &l, &t, &r, &bt);
    if (x < l || x >= r || y < t || y >= bt) return;
    target = a4_rd(b->line[y], x, d);
    if (target == (d == 8 ? (uint32_t)(color & 255) : (uint32_t)color) && A4S->draw_mode == DRAW_MODE_SOLID) return;
    stack = (int *)a4_malloc(sizeof(int) * 2 * (size_t)cap);
    if (!stack) return;
    {
        /* a scratch map of filled pixels, so patterns and XOR end too */
        unsigned char *done = (unsigned char *)a4_calloc((size_t)(r - l) * (size_t)(bt - t));
        if (!done) { a4_free(stack); return; }
        stack[sp++] = x; stack[sp++] = y;
        while (sp) {
            int cy = stack[--sp], cx = stack[--sp], x1, x2, i;
            if (done[(cy - t) * (r - l) + (cx - l)] || a4_rd(b->line[cy], cx, d) != target) continue;
            x1 = cx; while (x1 > l && a4_rd(b->line[cy], x1 - 1, d) == target && !done[(cy - t) * (r - l) + (x1 - 1 - l)]) x1--;
            x2 = cx; while (x2 < r - 1 && a4_rd(b->line[cy], x2 + 1, d) == target && !done[(cy - t) * (r - l) + (x2 + 1 - l)]) x2++;
            for (i = x1; i <= x2; i++) done[(cy - t) * (r - l) + (i - l)] = 1;
            for (i = x1; i <= x2; i++) {
                int ny;
                for (ny = cy - 1; ny <= cy + 1; ny += 2) {
                    if (ny < t || ny >= bt) continue;
                    if (a4_rd(b->line[ny], i, d) == target && !done[(ny - t) * (r - l) + (i - l)]) {
                        if (sp + 2 > cap * 2) {
                            int *ns = (int *)a4_realloc(stack, sizeof(int) * 2 * (size_t)cap, sizeof(int) * 4 * (size_t)cap);
                            if (!ns) goto out;
                            stack = ns; cap *= 2;
                        }
                        stack[sp++] = i; stack[sp++] = ny;
                    }
                }
            }
        }
    out:
        {
            int yy, xx;
            for (yy = t; yy < bt; yy++)
                for (xx = l; xx < r; xx++)
                    if (done[(yy - t) * (r - l) + (xx - l)]) plot(b, xx, yy, color);
        }
        a4_free(done);
    }
    a4_free(stack);
    a4_mark_screen(b);
}

/* ---- splines and arcs ------------------------------------------------------------- */

void spline(BITMAP *b, const int points[8], int color)
{
    int i, px = points[0], py = points[1];
    for (i = 1; i <= 32; i++) {
        long t = (long)i * 2048 / 32, mt = 2048 - t;        /* 11-bit fixed */
        long a = mt * mt / 2048 * mt / 2048, bb = 3 * t * mt / 2048 * mt / 2048;
        long c = 3 * t * t / 2048 * mt / 2048, d = t * t / 2048 * t / 2048;
        int x = (int)((a * points[0] + bb * points[2] + c * points[4] + d * points[6]) / 2048);
        int y = (int)((a * points[1] + bb * points[3] + c * points[5] + d * points[7]) / 2048);
        line(b, px, py, x, y, color);
        px = x; py = y;
    }
}

void do_arc(BITMAP *bmp, int x, int y, fixed ang1, fixed ang2, int r, int d, void (*proc)(BITMAP *, int, int, int))
{
    fixed a;
    int steps = r * 4 + 8, i;
    while (ang2 < ang1) ang2 += itofix(256);
    for (i = 0; i <= steps; i++) {
        a = ang1 + (fixed)(((int64_t)(ang2 - ang1) * i) / steps);
        proc(bmp, x + fixtoi(fixcos(a) * r), y - fixtoi(fixsin(a) * r), d);
    }
}

void arc(BITMAP *b, int x, int y, fixed ang1, fixed ang2, int r, int color)
{
    do_arc(b, x, y, ang1, ang2, r, color, line_pixel);
    a4_mark_screen(b);
}
