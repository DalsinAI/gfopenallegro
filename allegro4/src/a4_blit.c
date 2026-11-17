/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Blits, sprites (plain, flipped, masked, translucent, lit, rotated,
 * stretched) and RLE sprites, at every depth. The mask colour is 0 in
 * 8-bit and pink in truecolour. A blit or sprite from another depth is
 * converted as it is drawn (an 8-bit one through the palette).
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

/* converts a source pixel to the destination's depth */
struct conv {
    int sd, dd;
    uint32_t smask, dmask;
    uint32_t exp8[256];             /* sd 8 -> dd */
};

static void conv_init(struct conv *cv, int sd, int dd)
{
    cv->sd = sd; cv->dd = dd;
    cv->smask = a4_maskc(sd); cv->dmask = a4_maskc(dd);
    if (sd == 8 && dd != 8) a4_expand_palette(dd, NULL, cv->exp8);
}

static inline uint32_t conv_px(const struct conv *cv, uint32_t c)
{
    if (cv->sd == cv->dd) return c;
    if (cv->sd == 8) return cv->exp8[c & 255];
    return a4_convert(c, cv->sd, cv->dd);
}

void blit(BITMAP *src, BITMAP *dst, int sx, int sy, int dx, int dy, int w, int h)
{
    int y, x, sd, dd;
    if (!src || !dst) return;
    if (!clip_copy(src, dst, &sx, &sy, &dx, &dy, &w, &h)) return;
    sd = a4_bdepth(src); dd = a4_bdepth(dst);
    if (sd == dd) {
        int bpp = a4_bpp(sd);
        size_t n = (size_t)w * (size_t)bpp;
        if (is_same_bitmap(src, dst) && dy > sy) {
            for (y = h - 1; y >= 0; y--) memmove(dst->line[dy + y] + dx * bpp, src->line[sy + y] + sx * bpp, n);
        } else {
            for (y = 0; y < h; y++) memmove(dst->line[dy + y] + dx * bpp, src->line[sy + y] + sx * bpp, n);
        }
    } else {
        struct conv cv;
        conv_init(&cv, sd, dd);
        for (y = 0; y < h; y++)
            for (x = 0; x < w; x++)
                a4_wr(dst->line[dy + y], dx + x, dd, conv_px(&cv, a4_rd(src->line[sy + y], sx + x, sd)));
    }
    after_screen_blit(dst, w, h);
}

void masked_blit(BITMAP *src, BITMAP *dst, int sx, int sy, int dx, int dy, int w, int h)
{
    int x, y, sd, dd;
    struct conv cv;
    if (!src || !dst) return;
    if (!clip_copy(src, dst, &sx, &sy, &dx, &dy, &w, &h)) return;
    sd = a4_bdepth(src); dd = a4_bdepth(dst);
    if (sd == 8 && dd == 8) {
        for (y = 0; y < h; y++) {
            const unsigned char *s = src->line[sy + y] + sx;
            unsigned char *d = dst->line[dy + y] + dx;
            for (x = 0; x < w; x++) if (s[x]) d[x] = s[x];
        }
    } else {
        conv_init(&cv, sd, dd);
        for (y = 0; y < h; y++)
            for (x = 0; x < w; x++) {
                uint32_t c = a4_rd(src->line[sy + y], sx + x, sd);
                if (c != cv.smask) a4_wr(dst->line[dy + y], dx + x, dd, conv_px(&cv, c));
            }
    }
    after_screen_blit(dst, w, h);
}

/* the general sprite drawer: hflip/vflip, and what to do per pixel */
enum { SPR_MASKED, SPR_TRANS, SPR_LIT, SPR_CHAR };

/* one sprite pixel c (not the mask) onto *at depth dd */
static inline void spr_px(unsigned char *row, int x, const struct conv *cv, uint32_t c, int how, int color, int bg, uint32_t litc)
{
    int dd = cv->dd;
    (void)bg;
    switch (how) {
    case SPR_MASKED:
        a4_wr(row, x, dd, conv_px(cv, c));
        break;
    case SPR_TRANS:
        if (dd == 8) row[x] = cv->sd == 8 && color_map ? color_map->data[c & 255][row[x]] : (unsigned char)conv_px(cv, c);
        else a4_wr(row, x, dd, a4_blend(dd, A4S->blend_kind == A4_BLEND_ALPHA && cv->sd == 32 ? c : conv_px(cv, c),
                                       a4_rd(row, x, dd), A4S->blend_a));
        break;
    case SPR_LIT:
        if (dd == 8) row[x] = cv->sd == 8 && color_map ? color_map->data[color & 255][c & 255] : (unsigned char)conv_px(cv, c);
        else a4_wr(row, x, dd, a4_blend(dd, litc, conv_px(cv, c), color & 255));
        break;
    default:      /* SPR_CHAR: a font glyph */
        a4_wr(row, x, dd, (uint32_t)color);
        break;
    }
}

static void sprite_ex(BITMAP *bmp, BITMAP *spr, int x, int y, int hflip, int vflip, int how, int color, int bg)
{
    int l, t, r, b, sx0, sy0, w, h, i, j;
    struct conv cv;
    uint32_t litc = 0;
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
    conv_init(&cv, a4_bdepth(spr), a4_bdepth(bmp));
    if (how == SPR_LIT && cv.dd != 8) litc = a4_pack(cv.dd, A4S->blend_r, A4S->blend_g, A4S->blend_b);
    if (cv.sd == 8 && cv.dd == 8) {
        /* the 8-bit path as it always was */
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
    } else {
        for (j = sy0; j < h; j++) {
            const unsigned char *s = spr->line[vflip ? spr->h - 1 - j : j];
            unsigned char *row = bmp->line[y + j];
            for (i = sx0; i < w; i++) {
                uint32_t c = a4_rd(s, hflip ? spr->w - 1 - i : i, cv.sd);
                if (c != cv.smask) spr_px(row, x + i, &cv, c, how, color, bg, litc);
                else if (how == SPR_CHAR && bg >= 0) a4_wr(row, x + i, cv.dd, (uint32_t)bg);
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
    struct conv cv;
    if (!src || !dst || sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0) return;
    if (dst->clip) { l = dst->cl; t = dst->ct; r = dst->cr; b = dst->cb; }
    else { l = 0; t = 0; r = dst->w; b = dst->h; }
    conv_init(&cv, a4_bdepth(src), a4_bdepth(dst));
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
        if (cv.sd == 8 && cv.dd == 8) {
            for (i = 0; i < dw; i++, fx += xstep) {
                int xx = dx + i, scol = sx + (int)(fx >> 16);
                if (xx < l || xx >= r || scol < 0 || scol >= src->w) continue;
                if (!masked || s[scol]) d[xx] = s[scol];
            }
        } else {
            for (i = 0; i < dw; i++, fx += xstep) {
                int xx = dx + i, scol = sx + (int)(fx >> 16);
                uint32_t c;
                if (xx < l || xx >= r || scol < 0 || scol >= src->w) continue;
                c = a4_rd(s, scol, cv.sd);
                if (!masked || c != cv.smask) a4_wr(d, xx, cv.dd, conv_px(&cv, c));
            }
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
    struct conv cv;
    if (!bmp || !spr || scale == 0) return;
    conv_init(&cv, a4_bdepth(spr), a4_bdepth(bmp));
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
            int u, v;
            uint32_t col;
            if (i < l || i >= r) continue;
            /* the pixel's centre, rotated back by the angle and unscaled */
            px = itofix(i - x) + 0x8000;
            py = itofix(j - y) + 0x8000;
            u = fixfloor(fixmul(fixmul(px, c) + fixmul(py, s), inv) + itofix(cx));
            v = fixfloor(fixmul(fixmul(py, c) - fixmul(px, s), inv) + itofix(cy));
            if (u < 0 || v < 0 || u >= spr->w || v >= spr->h) continue;
            col = a4_rd(spr->line[vflip ? spr->h - 1 - v : v], u, cv.sd);
            if (col != cv.smask) a4_wr(d, i, cv.dd, conv_px(&cv, col));
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

/* ---- RLE sprites (Allegro 4's runs: n>0 n pixels follow, n<0 skip -n,
 * 0 ends the line; a pixel is 1 byte in 8-bit, else 4, native order) ----------------- */

RLE_SPRITE *get_rle_sprite(BITMAP *bmp)
{
    RLE_SPRITE *s;
    signed char *buf, *p;
    int x, y, cap, d, ps;
    uint32_t mask;
    if (!bmp) return NULL;
    d = a4_bdepth(bmp);
    ps = d == 8 ? 1 : 4;
    mask = a4_maskc(d);
    cap = bmp->w * bmp->h * (ps + 1) + bmp->h + 16;
    buf = (signed char *)a4_malloc((size_t)cap);
    if (!buf) return NULL;
    p = buf;
    for (y = 0; y < bmp->h; y++) {
        const unsigned char *row = bmp->line[y];
        x = 0;
        while (x < bmp->w) {
            int n = 0;
            if (a4_rd(row, x, d) == mask) {
                while (x + n < bmp->w && a4_rd(row, x + n, d) == mask && n < 127) n++;
                *p++ = (signed char)-n;
            } else {
                int k;
                while (x + n < bmp->w && a4_rd(row, x + n, d) != mask && n < 127) n++;
                *p++ = (signed char)n;
                if (ps == 1) { memcpy(p, row + x, (size_t)n); p += n; }
                else for (k = 0; k < n; k++) { uint32_t c = a4_rd(row, x + k, d); memcpy(p, &c, 4); p += 4; }
            }
            x += n;
        }
        *p++ = 0;
    }
    s = (RLE_SPRITE *)a4_malloc(sizeof(RLE_SPRITE) + (size_t)(p - buf));
    if (s) {
        s->w = bmp->w; s->h = bmp->h; s->color_depth = d; s->size = (int)(p - buf);
        memcpy(s->dat, buf, (size_t)(p - buf));
    }
    a4_free(buf);
    return s;
}

void destroy_rle_sprite(RLE_SPRITE *s) { a4_free(s); }

static void rle_draw(BITMAP *bmp, const RLE_SPRITE *s, int x, int y, int how, int color)
{
    const signed char *p;
    int l, t, r, b, j, ps;
    struct conv cv;
    uint32_t litc = 0;
    if (!bmp || !s) return;
    if (bmp->clip) { l = bmp->cl; t = bmp->ct; r = bmp->cr; b = bmp->cb; }
    else { l = 0; t = 0; r = bmp->w; b = bmp->h; }
    conv_init(&cv, a4_valid_depth(s->color_depth) ? s->color_depth : 8, a4_bdepth(bmp));
    ps = cv.sd == 8 ? 1 : 4;
    if (how == SPR_LIT && cv.dd != 8) litc = a4_pack(cv.dd, A4S->blend_r, A4S->blend_g, A4S->blend_b);
    p = s->dat;
    for (j = 0; j < s->h; j++) {
        int xx = x, yy = y + j;
        int visible = yy >= t && yy < b;
        for (;;) {
            int n = *p++;
            if (n == 0) break;
            if (n < 0) { xx += -n; continue; }
            while (n--) {
                uint32_t c;
                if (ps == 1) c = (unsigned char)*p;
                else memcpy(&c, p, 4);
                p += ps;
                if (visible && xx >= l && xx < r) {
                    if (cv.sd == 8 && cv.dd == 8) {
                        unsigned char *d = bmp->line[yy] + xx;
                        if (how == SPR_TRANS) *d = color_map ? color_map->data[c][*d] : (unsigned char)c;
                        else if (how == SPR_LIT) *d = color_map ? color_map->data[color & 255][c] : (unsigned char)c;
                        else *d = (unsigned char)c;
                    } else spr_px(bmp->line[yy], xx, &cv, c, how, color, -1, litc);
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
