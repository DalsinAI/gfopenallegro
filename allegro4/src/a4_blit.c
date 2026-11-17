/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Blits, sprites (plain, flipped, masked, translucent, lit, rotated,
 * stretched) and RLE sprites, all 8-bit. Colour 0 is the mask colour.
 */
#include "a4_internal.h"

/* clip a copy of w x h from (sx,sy) to (dx,dy) against the source's size
 * and the destination's clip box; 0 when nothing is left */
static int clip_copy(BITMAP *src, BITMAP *dst, int *sx, int *sy, int *dx, int *dy, int *w, int *h)
{
    int l, t, r, b;
    if (dst->clip) { l = dst->cl; t = dst->ct; r = dst->cr; b = dst->cb; }
    else { l = 0; t = 0; r = dst->w; b = dst->h; }
    if (*sx < 0) { *w += *sx; *dx -= *sx; *sx = 0; }
    if (*sy < 0) { *h += *sy; *dy -= *sy; *sy = 0; }
    if (*sx + *w > src->w) *w = src->w - *sx;
    if (*sy + *h > src->h) *h = src->h - *sy;
    if (*dx < l) { int d = l - *dx; *w -= d; *sx += d; *dx = l; }
    if (*dy < t) { int d = t - *dy; *h -= d; *sy += d; *dy = t; }
    if (*dx + *w > r) *w = r - *dx;
    if (*dy + *h > b) *h = b - *dy;
    return *w > 0 && *h > 0;
}

/* a large copy onto the screen is a game showing its frame: show it now */
static void after_screen_blit(BITMAP *dst, int w, int h)
{
    if (!a4_is_screen(dst)) return;
    a4_mark_screen(dst);
    if ((long)w * h * 2 >= (long)A4S->screen_bmp->w * A4S->screen_bmp->h) a4_present();
}

void blit(BITMAP *src, BITMAP *dst, int sx, int sy, int dx, int dy, int w, int h)
{
    int y;
    if (!src || !dst) return;
    if (!clip_copy(src, dst, &sx, &sy, &dx, &dy, &w, &h)) return;
    if (is_same_bitmap(src, dst) && dy > sy) {
        for (y = h - 1; y >= 0; y--) memmove(dst->line[dy + y] + dx, src->line[sy + y] + sx, (size_t)w);
    } else {
        for (y = 0; y < h; y++) memmove(dst->line[dy + y] + dx, src->line[sy + y] + sx, (size_t)w);
    }
    after_screen_blit(dst, w, h);
}

void masked_blit(BITMAP *src, BITMAP *dst, int sx, int sy, int dx, int dy, int w, int h)
{
    int x, y;
    if (!src || !dst) return;
    if (!clip_copy(src, dst, &sx, &sy, &dx, &dy, &w, &h)) return;
    for (y = 0; y < h; y++) {
        const unsigned char *s = src->line[sy + y] + sx;
        unsigned char *d = dst->line[dy + y] + dx;
        for (x = 0; x < w; x++) if (s[x]) d[x] = s[x];
    }
    after_screen_blit(dst, w, h);
}

/* the general sprite drawer: hflip/vflip, and what to do per pixel */
enum { SPR_MASKED, SPR_TRANS, SPR_LIT, SPR_CHAR };

static void sprite_ex(BITMAP *bmp, BITMAP *spr, int x, int y, int hflip, int vflip, int how, int color, int bg)
{
    int l, t, r, b, sx0, sy0, w, h, i, j;
    if (!bmp || !spr) return;
    if (bmp->clip) { l = bmp->cl; t = bmp->ct; r = bmp->cr; b = bmp->cb; }
    else { l = 0; t = 0; r = bmp->w; b = bmp->h; }
    w = spr->w; h = spr->h;
    sx0 = 0; sy0 = 0;
    if (x < l) { sx0 = l - x; }
    if (y < t) { sy0 = t - y; }
    if (x + w > r) w = r - x;
    if (y + h > b) h = b - y;
    if (sx0 >= w || sy0 >= h) return;
    for (j = sy0; j < h; j++) {
        const unsigned char *s = spr->line[vflip ? spr->h - 1 - j : j];
        unsigned char *d = bmp->line[y + j] + x;
        for (i = sx0; i < w; i++) {
            int c = s[hflip ? spr->w - 1 - i : i];
            switch (how) {
            case SPR_MASKED: if (c) d[i] = (unsigned char)c; break;
            case SPR_TRANS:
                if (c) d[i] = color_map ? color_map->data[c][d[i]] : (unsigned char)c;
                break;
            case SPR_LIT:
                if (c) d[i] = color_map ? color_map->data[color & 255][c] : (unsigned char)c;
                break;
            default:      /* SPR_CHAR: a font glyph */
                if (c) d[i] = (unsigned char)color;
                else if (bg >= 0) d[i] = (unsigned char)bg;
                break;
            }
        }
    }
    a4_mark_screen(bmp);
}

void draw_sprite(BITMAP *bmp, BITMAP *s, int x, int y) { sprite_ex(bmp, s, x, y, 0, 0, SPR_MASKED, 0, -1); }
void draw_sprite_h_flip(BITMAP *bmp, BITMAP *s, int x, int y) { sprite_ex(bmp, s, x, y, 1, 0, SPR_MASKED, 0, -1); }
void draw_sprite_v_flip(BITMAP *bmp, BITMAP *s, int x, int y) { sprite_ex(bmp, s, x, y, 0, 1, SPR_MASKED, 0, -1); }
void draw_sprite_vh_flip(BITMAP *bmp, BITMAP *s, int x, int y) { sprite_ex(bmp, s, x, y, 1, 1, SPR_MASKED, 0, -1); }
void draw_trans_sprite(BITMAP *bmp, BITMAP *s, int x, int y) { sprite_ex(bmp, s, x, y, 0, 0, SPR_TRANS, 0, -1); }
void draw_lit_sprite(BITMAP *bmp, BITMAP *s, int x, int y, int c) { sprite_ex(bmp, s, x, y, 0, 0, SPR_LIT, c, -1); }
void draw_character_ex(BITMAP *bmp, BITMAP *s, int x, int y, int c, int bg) { sprite_ex(bmp, s, x, y, 0, 0, SPR_CHAR, c, bg); }

void draw_sprite_ex(BITMAP *bmp, BITMAP *s, int x, int y, int mode, int flip)
{
    int how = mode == DRAW_SPRITE_TRANS ? SPR_TRANS : mode == DRAW_SPRITE_LIT ? SPR_LIT : SPR_MASKED;
    sprite_ex(bmp, s, x, y, (flip & DRAW_SPRITE_H_FLIP) != 0, (flip & DRAW_SPRITE_V_FLIP) != 0, how, 0, -1);
}

/* ---- stretching ------------------------------------------------------------------- */

static void stretch(BITMAP *src, BITMAP *dst, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, int masked)
{
    int l, t, r, b, i, j;
    uint32_t xstep, ystep, fy;
    if (!src || !dst || sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0) return;
    if (dst->clip) { l = dst->cl; t = dst->ct; r = dst->cr; b = dst->cb; }
    else { l = 0; t = 0; r = dst->w; b = dst->h; }
    xstep = (uint32_t)(((uint64_t)sw << 16) / (uint32_t)dw);
    ystep = (uint32_t)(((uint64_t)sh << 16) / (uint32_t)dh);
    for (j = 0; j < dh; j++) {
        int yy = dy + j, srow;
        unsigned char *d;
        const unsigned char *s;
        uint32_t fx;
        if (yy < t || yy >= b) continue;
        fy = (uint32_t)j * ystep;
        srow = sy + (int)(fy >> 16);
        if (srow < 0 || srow >= src->h) continue;
        s = src->line[srow];
        d = dst->line[yy];
        fx = 0;
        for (i = 0; i < dw; i++, fx += xstep) {
            int xx = dx + i, scol = sx + (int)(fx >> 16);
            if (xx < l || xx >= r || scol < 0 || scol >= src->w) continue;
            if (!masked || s[scol]) d[xx] = s[scol];
        }
    }
    a4_mark_screen(dst);
    if (a4_is_screen(dst) && (long)dw * dh * 2 >= (long)A4S->screen_bmp->w * A4S->screen_bmp->h) a4_present();
}

void stretch_blit(BITMAP *s, BITMAP *d, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{ stretch(s, d, sx, sy, sw, sh, dx, dy, dw, dh, 0); }
void masked_stretch_blit(BITMAP *s, BITMAP *d, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{ stretch(s, d, sx, sy, sw, sh, dx, dy, dw, dh, 1); }
void stretch_sprite(BITMAP *bmp, BITMAP *spr, int x, int y, int w, int h)
{ if (spr) stretch(spr, bmp, 0, 0, spr->w, spr->h, x, y, w, h, 1); }

/* ---- rotation ------------------------------------------------------------------------ */

/* draws sprite rotated by angle (256 = full turn) and scaled about its
 * point (cx,cy), which lands at (x,y) on bmp; inverse mapping per pixel */
static void rotate_core(BITMAP *bmp, BITMAP *spr, int x, int y, int cx, int cy, fixed angle, fixed scale, int vflip)
{
    fixed c, s, inv;
    int l, t, r, b, i, j, rad;
    if (!bmp || !spr || scale == 0) return;
    c = fixcos(angle);
    s = fixsin(angle);
    inv = fixdiv(itofix(1), scale);
    if (bmp->clip) { l = bmp->cl; t = bmp->ct; r = bmp->cr; b = bmp->cb; }
    else { l = 0; t = 0; r = bmp->w; b = bmp->h; }
    /* the destination box: the sprite's farthest corner from the pivot */
    {
        int dxm = MAX(cx, spr->w - cx), dym = MAX(cy, spr->h - cy);
        rad = fixtoi(fixmul(fixsqrt(itofix(dxm * dxm + dym * dym) > 0 ? itofix(dxm * dxm + dym * dym) : 0), scale)) + 2;
        if (rad < 1) rad = 1;
        if (rad > 4096) rad = 4096;
    }
    for (j = y - rad; j <= y + rad; j++) {
        unsigned char *d;
        if (j < t || j >= b) continue;
        d = bmp->line[j];
        for (i = x - rad; i <= x + rad; i++) {
            fixed px, py;
            int u, v, col;
            if (i < l || i >= r) continue;
            /* the pixel's centre, rotated back by the angle and unscaled */
            px = itofix(i - x) + 0x8000;
            py = itofix(j - y) + 0x8000;
            u = fixfloor(fixmul(fixmul(px, c) + fixmul(py, s), inv) + itofix(cx));
            v = fixfloor(fixmul(fixmul(py, c) - fixmul(px, s), inv) + itofix(cy));
            if (u < 0 || v < 0 || u >= spr->w || v >= spr->h) continue;
            col = spr->line[vflip ? spr->h - 1 - v : v][u];
            if (col) d[i] = (unsigned char)col;
        }
    }
    a4_mark_screen(bmp);
}

void rotate_sprite(BITMAP *bmp, BITMAP *s, int x, int y, fixed a)
{ if (s) rotate_core(bmp, s, x + s->w / 2, y + s->h / 2, s->w / 2, s->h / 2, a, itofix(1), 0); }
void rotate_sprite_v_flip(BITMAP *bmp, BITMAP *s, int x, int y, fixed a)
{ if (s) rotate_core(bmp, s, x + s->w / 2, y + s->h / 2, s->w / 2, s->h / 2, a, itofix(1), 1); }
void rotate_scaled_sprite(BITMAP *bmp, BITMAP *s, int x, int y, fixed a, fixed sc)
{ if (s) rotate_core(bmp, s, x + fixtoi(fixmul(itofix(s->w / 2), sc)), y + fixtoi(fixmul(itofix(s->h / 2), sc)), s->w / 2, s->h / 2, a, sc, 0); }
void rotate_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *s, int x, int y, fixed a, fixed sc)
{ if (s) rotate_core(bmp, s, x + fixtoi(fixmul(itofix(s->w / 2), sc)), y + fixtoi(fixmul(itofix(s->h / 2), sc)), s->w / 2, s->h / 2, a, sc, 1); }
void pivot_sprite(BITMAP *bmp, BITMAP *s, int x, int y, int cx, int cy, fixed a)
{ rotate_core(bmp, s, x, y, cx, cy, a, itofix(1), 0); }
void pivot_sprite_v_flip(BITMAP *bmp, BITMAP *s, int x, int y, int cx, int cy, fixed a)
{ rotate_core(bmp, s, x, y, cx, cy, a, itofix(1), 1); }
void pivot_scaled_sprite(BITMAP *bmp, BITMAP *s, int x, int y, int cx, int cy, fixed a, fixed sc)
{ rotate_core(bmp, s, x, y, cx, cy, a, sc, 0); }
void pivot_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *s, int x, int y, int cx, int cy, fixed a, fixed sc)
{ rotate_core(bmp, s, x, y, cx, cy, a, sc, 1); }

/* ---- RLE sprites (Allegro 4's 8-bit runs: n>0 n pixels follow, n<0 skip -n,
 * 0 ends the line) ---------------------------------------------------------------------- */

RLE_SPRITE *get_rle_sprite(BITMAP *bmp)
{
    RLE_SPRITE *s;
    signed char *buf, *p;
    int x, y, cap;
    if (!bmp) return NULL;
    cap = bmp->w * bmp->h * 2 + bmp->h + 16;
    buf = (signed char *)a4_malloc((size_t)cap);
    if (!buf) return NULL;
    p = buf;
    for (y = 0; y < bmp->h; y++) {
        const unsigned char *row = bmp->line[y];
        x = 0;
        while (x < bmp->w) {
            int n = 0;
            if (row[x] == 0) {
                while (x + n < bmp->w && row[x + n] == 0 && n < 127) n++;
                *p++ = (signed char)-n;
            } else {
                while (x + n < bmp->w && row[x + n] != 0 && n < 127) n++;
                *p++ = (signed char)n;
                memcpy(p, row + x, (size_t)n);
                p += n;
            }
            x += n;
        }
        *p++ = 0;
    }
    s = (RLE_SPRITE *)a4_malloc(sizeof(RLE_SPRITE) + (size_t)(p - buf));
    if (s) {
        s->w = bmp->w; s->h = bmp->h; s->color_depth = 8; s->size = (int)(p - buf);
        memcpy(s->dat, buf, (size_t)(p - buf));
    }
    a4_free(buf);
    return s;
}

void destroy_rle_sprite(RLE_SPRITE *s) { a4_free(s); }

static void rle_draw(BITMAP *bmp, const RLE_SPRITE *s, int x, int y, int how, int color)
{
    const signed char *p;
    int l, t, r, b, j;
    if (!bmp || !s) return;
    if (bmp->clip) { l = bmp->cl; t = bmp->ct; r = bmp->cr; b = bmp->cb; }
    else { l = 0; t = 0; r = bmp->w; b = bmp->h; }
    p = s->dat;
    for (j = 0; j < s->h; j++) {
        int xx = x, yy = y + j;
        int visible = yy >= t && yy < b;
        for (;;) {
            int n = *p++;
            if (n == 0) break;
            if (n < 0) { xx += -n; continue; }
            while (n--) {
                int c = (unsigned char)*p++;
                if (visible && xx >= l && xx < r) {
                    unsigned char *d = bmp->line[yy] + xx;
                    if (how == SPR_TRANS) *d = color_map ? color_map->data[c][*d] : (unsigned char)c;
                    else if (how == SPR_LIT) *d = color_map ? color_map->data[color & 255][c] : (unsigned char)c;
                    else *d = (unsigned char)c;
                }
                xx++;
            }
        }
    }
    a4_mark_screen(bmp);
}

void draw_rle_sprite(BITMAP *bmp, const RLE_SPRITE *s, int x, int y) { rle_draw(bmp, s, x, y, SPR_MASKED, 0); }
void draw_trans_rle_sprite(BITMAP *bmp, const RLE_SPRITE *s, int x, int y) { rle_draw(bmp, s, x, y, SPR_TRANS, 0); }
void draw_lit_rle_sprite(BITMAP *bmp, const RLE_SPRITE *s, int x, int y, int c) { rle_draw(bmp, s, x, y, SPR_LIT, c); }
