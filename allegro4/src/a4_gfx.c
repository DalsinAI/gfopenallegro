/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * The screen. set_gfx_mode opens an ACGame 8-bit screen (AGA or RTG, the
 * system's choice unless the game names one) and makes `screen` a bitmap
 * in Fast RAM at the game's colour depth. A truecolour screen is shown on
 * the 8-bit one through a fixed 6x7x6 colour cube (252 colours). Drawing on it marks it; it is shown through ACGame's frame
 * (one copy, then ACGame's c2p or chunky write) at vsync(), rest(), the
 * input polls, a palette change, and straight after a blit that covers at
 * least half of it, which is how a double-buffered game shows a frame.
 */
#include "a4_internal.h"
#include "acgame/platform.h"

static int open_acgame(int card, int w, int h)
{
    acgame_video_config cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.width = (unsigned)w;
    cfg.height = (unsigned)h;
    cfg.refresh_hz = A4S->requested_refresh > 0 ? (unsigned)A4S->requested_refresh : 50u;
    cfg.mode = ACGAME_VIDEO_INDEXED8;
    cfg.display = card == GFX_ACGAME_AGA ? ACGAME_DISPLAY_AGA :
                  card == GFX_ACGAME_RTG ? ACGAME_DISPLAY_RTG : ACGAME_DISPLAY_AUTO;
    return acgame_platform_init(&cfg);
}

static void close_screen(void)
{
    if (!A4S->gfx_on) return;
    acgame_platform_shutdown();
    A4S->gfx_on = 0;
    if (A4S->screen_bmp) {
        BITMAP *b = A4S->screen_bmp;
        A4S->screen_bmp = NULL;
        a4_free(b->dat);
        a4_free(b);
    }
    a4_free(A4S->tc_lut);
    A4S->tc_lut = NULL;
    screen = NULL;
    _a4_screen_w = 0;
    _a4_screen_h = 0;
    gfx_driver = NULL;
}

/* the colour cube a truecolour screen is shown in: index r*42 + g*6 + b,
 * r and b 0-5, g 0-6 */
static int cube_r(int v) { return (v * 5 + 127) / 255; }
static int cube_g(int v) { return (v * 6 + 127) / 255; }
static int cube_index(int r, int g, int b) { return cube_r(r) * 42 + cube_g(g) * 6 + cube_r(b); }

void a4_cube_palette(acgame_rgb8 pal[256])
{
    int i;
    for (i = 0; i < 256; i++) {
        if (i < 252) {
            pal[i].r = (uint8_t)(i / 42 * 255 / 5);
            pal[i].g = (uint8_t)(i / 6 % 7 * 255 / 6);
            pal[i].b = (uint8_t)(i % 6 * 255 / 5);
        } else pal[i].r = pal[i].g = pal[i].b = 0;
    }
}

/* 15/16-bit: every pixel value's index (65536); then, for 24/32-bit, the
 * three guns' parts (3 x 256) */
static unsigned char *make_cube_lut(int depth)
{
    unsigned char *t = (unsigned char *)a4_malloc(65536 + 768);
    long c;
    int v;
    if (!t) return NULL;
    if (depth == 15 || depth == 16)
        for (c = 0; c < 65536; c++) {
            int r, g, b;
            a4_unpack(depth, (uint32_t)c, &r, &g, &b);
            t[c] = (unsigned char)cube_index(r, g, b);
        }
    for (v = 0; v < 256; v++) {
        t[65536 + v] = (unsigned char)(cube_r(v) * 42);
        t[65536 + 256 + v] = (unsigned char)(cube_g(v) * 6);
        t[65536 + 512 + v] = (unsigned char)cube_r(v);
    }
    return t;
}

/* one row of a truecolour screen into the 8-bit frame */
void a4_cube_row(unsigned char *out, const unsigned char *row, int w, int depth, const unsigned char *lut)
{
    int x;
    const unsigned char *lr = lut + 65536, *lg = lr + 256, *lb = lg + 256;
    switch (depth) {
    case 15: { const uint16_t *p = (const uint16_t *)row; for (x = 0; x < w; x++) out[x] = lut[p[x] & 0x7FFF]; break; }
    case 16: { const uint16_t *p = (const uint16_t *)row; for (x = 0; x < w; x++) out[x] = lut[p[x]]; break; }
    case 24: for (x = 0; x < w; x++, row += 3) out[x] = (unsigned char)(lr[row[0]] + lg[row[1]] + lb[row[2]]); break;
    default: {
        const uint32_t *p = (const uint32_t *)row;
        for (x = 0; x < w; x++) { uint32_t c = p[x]; out[x] = (unsigned char)(lr[(c >> 16) & 255] + lg[(c >> 8) & 255] + lb[c & 255]); }
        break;
    }
    }
}

int set_gfx_mode(int card, int w, int h, int v_w, int v_h)
{
    BITMAP *b;
    int aw;
    (void)v_w; (void)v_h;
    allegro_error[0] = 0;
    close_screen();
    if (card == GFX_TEXT) return 0;
    if (w <= 0 || h <= 0) { if (card == GFX_SAFE) { w = 320; h = 200; } else { a4_set_error("Bad screen size"); return -1; } }
    /* ACGame wants a width that is a multiple of 8 (c2p): round up, and
     * the game's bitmap keeps the size it asked for */
    aw = (w + 7) & ~7;
    if (open_acgame(card, aw, h) != 0) {
        if (card == GFX_SAFE && open_acgame(GFX_AUTODETECT, 320, 200) == 0) { w = 320; h = 200; aw = 320; }
        else { a4_set_error("Unable to open an 8-bit screen (acgame.library)"); return -1; }
    }
    b = create_bitmap_ex(a4_valid_depth(_color_depth) ? _color_depth : 8, aw, h);
    if (b && a4_bdepth(b) != 8 && !(A4S->tc_lut = make_cube_lut(a4_bdepth(b)))) { destroy_bitmap(b); b = NULL; }
    if (!b) { acgame_platform_shutdown(); a4_set_error("Not enough memory for the screen"); return -1; }
    /* the game sees its own width; the pad on the right stays black */
    b->w = w;
    b->cr = w;
    b->id = BMP_ID_VIDEO;
    A4S->screen_bmp = b;
    A4S->gfx_on = 1;
    A4S->gfx_card = card;
    A4S->screen_dirty = 1;
    A4S->palette_dirty = 1;
    A4S->refresh_rate = A4S->requested_refresh > 0 ? A4S->requested_refresh : 50;
    {
        acgame_platform_info info;
        int planar = acgame_platform_get_info(&info) == 0 ? info.planar : 0;
        A4S->gfx_drv.id = planar ? GFX_ACGAME_AGA : GFX_ACGAME_RTG;
        A4S->gfx_drv.name = planar ? "ACGame AGA" : "ACGame RTG";
        A4S->gfx_drv.desc = A4S->gfx_drv.name;
        A4S->gfx_drv.ascii_name = A4S->gfx_drv.name;
    }
    A4S->gfx_drv.w = w;
    A4S->gfx_drv.h = h;
    A4S->gfx_drv.linear = TRUE;
    A4S->gfx_drv.windowed = FALSE;
    gfx_driver = &A4S->gfx_drv;
    screen = b;
    _a4_screen_w = w;
    _a4_screen_h = h;
    set_palette(default_palette);
    a4_update_palette_color();
    a4_present();
    return 0;
}

void a4_gfx_shutdown(void) { close_screen(); }

void request_refresh_rate(int rate) { A4S->requested_refresh = rate; }
int get_refresh_rate(void) { return A4S->gfx_on ? A4S->refresh_rate : 0; }
int get_gfx_mode(void) { return A4S->gfx_on ? A4S->gfx_card : GFX_TEXT; }
int get_gfx_mode_type(int card) { (void)card; return 0x1 | 0x4; }   /* fullscreen, magic */

GFX_MODE_LIST *get_gfx_mode_list(int card)
{
    static const int sizes[][2] = { { 320, 200 }, { 320, 240 }, { 320, 256 }, { 640, 400 }, { 640, 480 }, { 640, 512 }, { 800, 600 } };
    static const int depths[] = { 8, 15, 16, 24, 32 };
    GFX_MODE_LIST *l;
    int i, k, n = (int)(sizeof(sizes) / sizeof(sizes[0])), nd = (int)(sizeof(depths) / sizeof(depths[0]));
    (void)card;
    l = (GFX_MODE_LIST *)a4_calloc(sizeof(GFX_MODE_LIST));
    if (!l) return NULL;
    l->mode = (GFX_MODE *)a4_calloc(sizeof(GFX_MODE) * (size_t)(n * nd + 1));
    if (!l->mode) { a4_free(l); return NULL; }
    for (k = 0; k < nd; k++)
        for (i = 0; i < n; i++) {
            GFX_MODE *m = &l->mode[k * n + i];
            m->width = sizes[i][0]; m->height = sizes[i][1]; m->bpp = depths[k];
        }
    l->num_modes = n * nd;
    return l;
}

void destroy_gfx_mode_list(GFX_MODE_LIST *l)
{
    if (!l) return;
    a4_free(l->mode);
    a4_free(l);
}

/* ---- showing it -------------------------------------------------------------------- */

void a4_mark_screen(BITMAP *bmp)
{
    if (A4S->screen_bmp && bmp && a4_bitmap_root(bmp) == A4S->screen_bmp) A4S->screen_dirty = 1;
}

void a4_present(void)
{
    acgame_indexed_surface *frame;
    BITMAP *b = A4S->screen_bmp;
    int y, i, w, d;
    if (!A4S->gfx_on || !b) return;
    frame = acgame_platform_begin_indexed_frame();
    if (!frame) return;
    w = (int)frame->width < (int)((b->w + 7) & ~7) ? (int)frame->width : (int)((b->w + 7) & ~7);
    d = a4_bdepth(b);
    if (d == 8) {
        for (y = 0; y < b->h && y < (int)frame->height; y++)
            memcpy(frame->pixels + (size_t)y * frame->pitch, b->line[y], (size_t)w);
        for (i = 0; i < 256; i++) {
            frame->palette[i].r = (uint8_t)a4_pal63to255(A4S->palette[i][0]);
            frame->palette[i].g = (uint8_t)a4_pal63to255(A4S->palette[i][1]);
            frame->palette[i].b = (uint8_t)a4_pal63to255(A4S->palette[i][2]);
        }
    } else {
        for (y = 0; y < b->h && y < (int)frame->height; y++)
            a4_cube_row(frame->pixels + (size_t)y * frame->pitch, b->line[y], w, d, A4S->tc_lut);
        a4_cube_palette(frame->palette);
    }
    acgame_platform_present_indexed(frame);
    A4S->screen_dirty = 0;
    A4S->palette_dirty = 0;
    A4S->last_present_ms = acgame_platform_ticks_ms();
}

void a4_present_if_dirty(void)
{
    if (!A4S->gfx_on) return;
    if (A4S->screen_dirty) { a4_present(); return; }
    if (A4S->palette_dirty && A4S->screen_bmp && a4_bdepth(A4S->screen_bmp) != 8) {
        A4S->palette_dirty = 0;                 /* the cube is shown; palette_color has the change */
        return;
    }
    if (A4S->palette_dirty) {
        acgame_rgb8 pal[256];
        int i;
        for (i = 0; i < 256; i++) {
            pal[i].r = (uint8_t)a4_pal63to255(A4S->palette[i][0]);
            pal[i].g = (uint8_t)a4_pal63to255(A4S->palette[i][1]);
            pal[i].b = (uint8_t)a4_pal63to255(A4S->palette[i][2]);
        }
        /* a still picture with a new palette (a fade): ACGame shows it at
         * the next blank without converting the picture again */
        if (acgame_platform_set_palette(pal) != 0) { a4_present(); return; }
        {
            acgame_indexed_surface *frame = acgame_platform_begin_indexed_frame();
            if (frame) memcpy(frame->palette, pal, sizeof(pal));
        }
        A4S->palette_dirty = 0;
    }
}

void a4_flush_screen(void) { a4_present(); }

/* vsync: show what is pending, then wait for the next 1/refresh tick */
void vsync(void)
{
    uint32_t period = 1000u / (uint32_t)(A4S->refresh_rate > 0 ? A4S->refresh_rate : 50);
    uint32_t now, next;
    a4_poll_point();
    a4_present_if_dirty();
    now = acgame_platform_ticks_ms();
    next = (now / period + 1) * period;
    while ((int32_t)(acgame_platform_ticks_ms() - next) < 0) {
        a4_os_delay_ms(1);
        if (!a4_os_timer_async()) a4_timer_dispatch();
    }
}
