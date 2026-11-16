/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Bitmaps (8-bit, linear, in Fast RAM), clipping and the drawing
 * primitives. The screen is a bitmap like any other; drawing on it marks it
 * to be shown (a4_gfx.c).
 */
#include "a4_internal.h"

/* ---- bitmaps --------------------------------------------------------------- */

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
    int y;
    if (width < 0 || height < 0) return NULL;
    if (color_depth != 8) {
        /* allegro4.library is 8-bit: any depth gets an 8-bit bitmap, so
         * a game's own buffers still work; truecolour pixels are not kept. */
    }
    b = new_bitmap_struct(width, height);
    if (!b) return NULL;
    pix = (unsigned char *)a4_calloc((size_t)(width ? width : 1) * (size_t)(height ? height : 1));
    if (!pix) { a4_free(b); return NULL; }
    b->dat = pix;
    for (y = 0; y < height; y++) b->line[y] = pix + (size_t)y * (size_t)width;
    return b;
}

BITMAP *create_bitmap(int width, int height) { return create_bitmap_ex(8, width, height); }
BITMAP *create_video_bitmap(int width, int height) { return create_bitmap(width, height); }
BITMAP *create_system_bitmap(int width, int height) { return create_bitmap(width, height); }

BITMAP *create_sub_bitmap(BITMAP *parent, int x, int y, int width, int height)
{
    BITMAP *b;
    int i;
    if (!parent) return NULL;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > parent->w) width = parent->w - x;
    if (y + height > parent->h) height = parent->h - y;
    if (width < 0 || height < 0) return NULL;
    b = new_bitmap_struct(width, height);
    if (!b) return NULL;
    for (i = 0; i < height; i++) b->line[i] = parent->line[y + i] + x;
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

int bitmap_color_depth(BITMAP *bmp) { (void)bmp; return 8; }
int bitmap_mask_color(BITMAP *bmp) { (void)bmp; return MASK_COLOR_8; }
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
static inline void plot(BITMAP *b, int x, int y, int c)
{
    unsigned char *p = b->line[y] + x;
    switch (A4S->draw_mode) {
    case DRAW_MODE_SOLID:
        *p = (unsigned char)c;
        break;
    case DRAW_MODE_XOR:
        *p ^= (unsigned char)c;
        break;
    case DRAW_MODE_TRANS:
        if (color_map) *p = color_map->data[c & 255][*p];
        else *p = (unsigned char)c;
        break;
    default: {
        BITMAP *pat = A4S->pattern;
        int px, py, pc;
        if (!pat || pat->w <= 0 || pat->h <= 0) { *p = (unsigned char)c; break; }
        px = (x - A4S->pattern_x) % pat->w; if (px < 0) px += pat->w;
        py = (y - A4S->pattern_y) % pat->h; if (py < 0) py += pat->h;
        pc = pat->line[py][px];
        if (A4S->draw_mode == DRAW_MODE_COPY_PATTERN) *p = (unsigned char)pc;
        else if (A4S->draw_mode == DRAW_MODE_SOLID_PATTERN) *p = pc ? (unsigned char)c : 0;
        else if (pc) *p = (unsigned char)c;   /* masked pattern */
        break;
    }
    }
}

static void span(BITMAP *b, int x1, int x2, int y, int c)
{
    if (A4S->draw_mode == DRAW_MODE_SOLID) {
        memset(b->line[y] + x1, c, (size_t)(x2 - x1 + 1));
    } else {
        int x;
        for (x = x1; x <= x2; x++) plot(b, x, y, c);
    }
}

/* ---- pixels and lines ----------------------------------------------------------- */

void clear_to_color(BITMAP *b, int color)
{
    int l, t, r, bt, y;
    clip_box(b, &l, &t, &r, &bt);
    for (y = t; y < bt; y++) memset(b->line[y] + l, color, (size_t)(r - l));
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

int getpixel(BITMAP *b, int x, int y)
{
    if (x < 0 || y < 0 || x >= b->w || y >= b->h) return -1;
    return b->line[y][x];
}
int _getpixel(BITMAP *b, int x, int y) { return b->line[y][x]; }

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
    int l, t, r, bt, target, sp = 0, cap = 1024;
    int *stack;
    clip_box(b, &l, &t, &r, &bt);
    if (x < l || x >= r || y < t || y >= bt) return;
    target = b->line[y][x];
    if (target == (color & 255) && A4S->draw_mode == DRAW_MODE_SOLID) return;
    stack = (int *)a4_malloc(sizeof(int) * 2 * (size_t)cap);
    if (!stack) return;
    {
        /* a scratch map of filled pixels, so patterns and XOR end too */
        unsigned char *done = (unsigned char *)a4_calloc((size_t)(r - l) * (size_t)(bt - t));
        if (!done) { a4_free(stack); return; }
        stack[sp++] = x; stack[sp++] = y;
        while (sp) {
            int cy = stack[--sp], cx = stack[--sp], x1, x2, i;
            if (done[(cy - t) * (r - l) + (cx - l)] || b->line[cy][cx] != target) continue;
            x1 = cx; while (x1 > l && b->line[cy][x1 - 1] == target && !done[(cy - t) * (r - l) + (x1 - 1 - l)]) x1--;
            x2 = cx; while (x2 < r - 1 && b->line[cy][x2 + 1] == target && !done[(cy - t) * (r - l) + (x2 + 1 - l)]) x2++;
            for (i = x1; i <= x2; i++) done[(cy - t) * (r - l) + (i - l)] = 1;
            for (i = x1; i <= x2; i++) {
                int ny;
                for (ny = cy - 1; ny <= cy + 1; ny += 2) {
                    if (ny < t || ny >= bt) continue;
                    if (b->line[ny][i] == target && !done[(ny - t) * (r - l) + (i - l)]) {
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
