/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Host unit tests of allegro4.library's core, on a fake acgame.library
 * (tests/fake_acgame.c) and the test clock. Run by tests/run_tests.sh.
 */
#include <allegro.h>
#include "fake_acgame.h"
#include "fake_music.h"
#include "fake_synth.h"
#include <aldumb.h>
#include <stdio.h>
#include <unistd.h>

extern uint64_t a4_test_clock_us;
extern int a4_test_clock_step_us;

static int failures, checks;
#define CHECK(c) do { checks++; if (!(c)) { failures++; fprintf(stderr, "%s:%d: CHECK(%s) failed\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { long _a = (long)(a), _b = (long)(b); checks++; if (_a != _b) { failures++; \
    fprintf(stderr, "%s:%d: %s == %ld, wanted %s == %ld\n", __FILE__, __LINE__, #a, _a, #b, _b); } } while (0)

static char tmpdir[256];
static const char *tmp(const char *name) { static char b[4][512]; static int i; i = (i + 1) & 3; snprintf(b[i], 512, "%s/%s", tmpdir, name); return b[i]; }

/* ---- bitmaps and drawing ---------------------------------------------------------- */

static void test_bitmaps(void)
{
    BITMAP *b = create_bitmap(16, 8), *s;
    int x, y, n;
    CHECK(b != NULL);
    CHECK_EQ(b->w, 16); CHECK_EQ(b->h, 8);
    CHECK_EQ(b->cl, 0); CHECK_EQ(b->cr, 16); CHECK_EQ(b->cb, 8);
    clear_to_color(b, 3);
    CHECK_EQ(getpixel(b, 15, 7), 3);
    CHECK_EQ(getpixel(b, 16, 0), -1);
    putpixel(b, 2, 2, 9);
    CHECK_EQ(b->line[2][2], 9);
    putpixel(b, -1, 2, 9);                      /* clipped, no crash */
    hline(b, -5, 0, 100, 7);
    for (x = 0; x < 16; x++) CHECK_EQ(b->line[0][x], 7);
    set_clip_rect(b, 4, 4, 7, 6);
    rectfill(b, 0, 0, 15, 7, 1);
    n = 0;
    for (y = 0; y < 8; y++) for (x = 0; x < 16; x++) n += b->line[y][x] == 1;
    CHECK_EQ(n, 4 * 3);
    CHECK_EQ(b->line[4][4], 1); CHECK_EQ(b->line[6][7], 1); CHECK_EQ(b->line[7][7], 3);
    set_clip_state(b, FALSE);
    clear_bitmap(b);
    line(b, 0, 0, 7, 7, 5);
    for (x = 0; x < 8; x++) CHECK_EQ(b->line[x][x], 5);
    rect(b, 0, 0, 15, 7, 2);
    CHECK_EQ(b->line[0][15], 2); CHECK_EQ(b->line[7][0], 2); CHECK_EQ(b->line[3][15], 2); CHECK_EQ(b->line[3][1], 0);
    s = create_sub_bitmap(b, 4, 2, 4, 4);
    CHECK(s != NULL);
    clear_to_color(s, 6);
    CHECK_EQ(b->line[2][4], 6); CHECK_EQ(b->line[5][7], 6); CHECK_EQ(b->line[6][4], 0);
    CHECK(is_sub_bitmap(s));
    CHECK(is_same_bitmap(s, b));
    destroy_bitmap(s);
    clear_bitmap(b);
    xor_mode(TRUE);
    hline(b, 0, 1, 3, 0x0F);
    hline(b, 0, 1, 1, 0x0F);
    solid_mode();
    CHECK_EQ(b->line[1][0], 0); CHECK_EQ(b->line[1][3], 0x0F);
    destroy_bitmap(b);

    b = create_bitmap(21, 21);
    clear_bitmap(b);
    circlefill(b, 10, 10, 5, 4);
    CHECK_EQ(b->line[10][5], 4); CHECK_EQ(b->line[10][15], 4); CHECK_EQ(b->line[5][10], 4); CHECK_EQ(b->line[15][10], 4);
    CHECK_EQ(b->line[10][4], 0); CHECK_EQ(b->line[4][10], 0); CHECK_EQ(b->line[6][6], 0);
    n = 0;
    for (y = 0; y < 21; y++) for (x = 0; x < 21; x++) n += b->line[y][x] == 4;
    CHECK(n > 70 && n < 100);                   /* pi*5.5^2 is about 95 */
    clear_bitmap(b);
    rectfill(b, 2, 2, 8, 8, 1);
    floodfill(b, 0, 0, 2);
    CHECK_EQ(b->line[0][0], 2); CHECK_EQ(b->line[20][20], 2); CHECK_EQ(b->line[5][5], 1);
    clear_bitmap(b);
    triangle(b, 0, 0, 20, 0, 0, 20, 3);
    CHECK_EQ(b->line[1][1], 3); CHECK_EQ(b->line[19][19], 0);
    destroy_bitmap(b);
}

/* ---- blits and sprites -------------------------------------------------------------- */

static BITMAP *pattern(int w, int h)
{
    BITMAP *b = create_bitmap(w, h);
    int x, y;
    for (y = 0; y < h; y++) for (x = 0; x < w; x++) b->line[y][x] = (unsigned char)((x + 1) + y * 16);
    return b;
}

static void test_blits(void)
{
    BITMAP *src = pattern(8, 4), *dst = create_bitmap(10, 10), *spr;
    RLE_SPRITE *rle;
    int x, y;
    clear_bitmap(dst);
    blit(src, dst, 0, 0, 1, 1, 8, 4);
    CHECK_EQ(dst->line[1][1], 1); CHECK_EQ(dst->line[4][8], 8 + 48);
    clear_bitmap(dst);
    blit(src, dst, 0, 0, -3, -2, 8, 4);         /* clipped on two sides */
    CHECK_EQ(dst->line[0][0], 4 + 32); CHECK_EQ(dst->line[1][4], 8 + 48); CHECK_EQ(dst->line[2][0], 0);
    clear_bitmap(dst);
    blit(src, dst, 6, 0, 8, 0, 8, 1);           /* runs off the source and the destination */
    CHECK_EQ(dst->line[0][8], 7); CHECK_EQ(dst->line[0][9], 8);
    /* overlapping blit on one bitmap, downwards */
    clear_bitmap(dst);
    for (x = 0; x < 10; x++) dst->line[0][x] = (unsigned char)(x + 1);
    dst->line[1][0] = 99;
    blit(dst, dst, 0, 0, 0, 1, 10, 2);
    CHECK_EQ(dst->line[1][0], 1); CHECK_EQ(dst->line[2][0], 99);   /* as memmove */

    spr = create_bitmap(3, 2);
    clear_bitmap(spr);
    spr->line[0][0] = 5; spr->line[0][2] = 6; spr->line[1][1] = 7;
    clear_to_color(dst, 9);
    draw_sprite(dst, spr, 0, 0);
    CHECK_EQ(dst->line[0][0], 5); CHECK_EQ(dst->line[0][1], 9); CHECK_EQ(dst->line[0][2], 6); CHECK_EQ(dst->line[1][1], 7);
    clear_to_color(dst, 9);
    draw_sprite_h_flip(dst, spr, 0, 0);
    CHECK_EQ(dst->line[0][0], 6); CHECK_EQ(dst->line[0][2], 5);
    clear_to_color(dst, 9);
    draw_sprite_v_flip(dst, spr, 0, 0);
    CHECK_EQ(dst->line[1][0], 5); CHECK_EQ(dst->line[0][1], 7);
    clear_to_color(dst, 9);
    draw_sprite_vh_flip(dst, spr, 0, 0);
    CHECK_EQ(dst->line[1][2], 5); CHECK_EQ(dst->line[1][0], 6);
    clear_to_color(dst, 9);
    draw_sprite(dst, spr, 8, 9);                /* clipped */
    CHECK_EQ(dst->line[9][8], 5); CHECK_EQ(dst->line[9][9], 9);
    clear_to_color(dst, 9);
    masked_blit(spr, dst, 0, 0, 2, 2, 3, 2);
    CHECK_EQ(dst->line[2][2], 5); CHECK_EQ(dst->line[2][3], 9);

    /* RLE: draws the same as the bitmap */
    rle = get_rle_sprite(spr);
    CHECK(rle != NULL);
    {
        BITMAP *a = create_bitmap(10, 10), *b = create_bitmap(10, 10);
        int same = 1;
        clear_to_color(a, 2); clear_to_color(b, 2);
        draw_sprite(a, spr, 7, 3);
        draw_rle_sprite(b, rle, 7, 3);
        for (y = 0; y < 10; y++) for (x = 0; x < 10; x++) same &= a->line[y][x] == b->line[y][x];
        CHECK(same);
        clear_to_color(a, 2); clear_to_color(b, 2);
        draw_sprite(a, spr, 8, -1);
        draw_rle_sprite(b, rle, 8, -1);
        for (y = 0; y < 10; y++) for (x = 0; x < 10; x++) same &= a->line[y][x] == b->line[y][x];
        CHECK(same);
        destroy_bitmap(a); destroy_bitmap(b);
    }
    destroy_rle_sprite(rle);

    /* stretch: 2x */
    clear_bitmap(dst);
    stretch_blit(src, dst, 0, 0, 2, 2, 0, 0, 4, 4);
    CHECK_EQ(dst->line[0][0], 1); CHECK_EQ(dst->line[0][1], 1); CHECK_EQ(dst->line[0][2], 2);
    CHECK_EQ(dst->line[3][3], 2 + 16);
    /* rotate by 0 is a plain sprite; by 64 (a quarter turn) moves pixels */
    clear_to_color(dst, 9);
    rotate_sprite(dst, spr, 2, 2, 0);
    CHECK_EQ(dst->line[2][2], 5); CHECK_EQ(dst->line[2][4], 6); CHECK_EQ(dst->line[3][3], 7);
    {
        BITMAP *sq = create_bitmap(4, 4);
        clear_bitmap(sq);
        sq->line[0][0] = 1;                     /* top left */
        clear_bitmap(dst);
        rotate_sprite(dst, sq, 3, 3, itofix(64));
        /* a quarter turn clockwise puts the top left corner at the top right */
        CHECK_EQ(dst->line[3][6], 1);
        destroy_bitmap(sq);
    }
    destroy_bitmap(spr);
    destroy_bitmap(src);
    destroy_bitmap(dst);
}

/* ---- palettes, colour tables, fixed point --------------------------------------------------- */

static void test_palette_and_fixed(void)
{
    PALETTE p, q;
    COLOR_MAP *cm;
    int i;
    for (i = 0; i < 256; i++) { p[i].r = (unsigned char)(i & 63); p[i].g = (unsigned char)((i >> 2) & 63); p[i].b = 0; }
    p[200].r = 63; p[200].g = 63; p[200].b = 63;
    p[10].r = 0; p[10].g = 0; p[10].b = 0;
    set_palette(p);
    get_palette(q);
    CHECK_EQ(q[37].r, 37); CHECK_EQ(q[200].b, 63);
    CHECK_EQ(makecol(255, 255, 255), 200);
    CHECK_EQ(getr(200), 255);
    CHECK_EQ(bestfit_color(p, 63, 63, 63), 200);
    cm = (COLOR_MAP *)malloc(sizeof(COLOR_MAP));
    create_trans_table(cm, p, 128, 128, 128, NULL);
    /* half of white over black: about mid grey's nearest */
    {
        int c = cm->data[200][10];
        CHECK(p[c].r > 24 && p[c].r < 38);
    }
    free(cm);
    {
        PALETTE out;
        PALETTE black;
        memset(black, 0, sizeof(black));
        fade_interpolate(black, p, out, 32, 0, 255);
        CHECK(out[200].r >= 31 && out[200].r <= 33);
    }
    CHECK_EQ(fixsin(itofix(64)), itofix(1));
    CHECK_EQ(fixcos(0), itofix(1));
    CHECK(ABS(fixsin(itofix(128))) < 4);
    CHECK_EQ(fixsin(itofix(192)), -itofix(1));
    CHECK(ABS(fixsin(itofix(32)) - 46341) < 8);           /* sin 45 degrees */
    CHECK(ABS(fixatan2(itofix(1), itofix(1)) - itofix(32)) < 64);
    CHECK(ABS(fixatan2(itofix(-1), itofix(-1)) + itofix(96)) < 64);
    CHECK_EQ(fixsqrt(itofix(4)), itofix(2));
    CHECK(ABS(fixhypot(itofix(3), itofix(4)) - itofix(5)) < 4);
    CHECK_EQ(fixmul(itofix(3), ftofix(0.5)), ftofix(1.5));
    CHECK_EQ(fixdiv(itofix(3), itofix(2)), ftofix(1.5));
    CHECK_EQ(fixtoi(ftofix(2.5)), 3);
}

/* ---- the screen on ACGame ------------------------------------------------------------- */

static void test_screen(void)
{
    BITMAP *buf;
    int before;
    fake.fail_init = 1;
    CHECK(set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0);
    CHECK(allegro_error[0] != 0);
    fake.fail_init = 0;
    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 321, 200, 0, 0), 0);
    CHECK_EQ(fake.cfg.width, 328);              /* rounded for c2p */
    CHECK_EQ(SCREEN_W, 321);
    CHECK_EQ(screen->w, 321);
    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 320, 240, 0, 0), 0);
    CHECK_EQ(SCREEN_W, 320); CHECK_EQ(SCREEN_H, 240);
    CHECK_EQ(fake.cfg.mode, ACGAME_VIDEO_INDEXED8);
    CHECK(gfx_driver != NULL);
    {
        PALETTE p;
        memset(p, 0, sizeof(p));
        p[5].r = 63; p[5].g = 32; p[5].b = 1;
        set_palette(p);
        CHECK_EQ(fake.shown_pal[5].r, 255);
        CHECK_EQ(fake.shown_pal[5].g, 130);
        CHECK_EQ(fake.shown_pal[5].b, 4);
    }
    buf = create_bitmap(320, 240);
    clear_to_color(buf, 5);
    buf->line[239][319] = 7;
    before = fake.presents;
    blit(buf, screen, 0, 0, 0, 0, 320, 240);
    CHECK_EQ(fake.presents, before + 1);       /* a whole frame shows at once */
    CHECK_EQ(fake.shown[0], 5);
    CHECK_EQ(fake.shown[239 * 320 + 319], 7);
    before = fake.presents;
    putpixel(screen, 1, 1, 9);                  /* small draws wait for a poll point */
    CHECK_EQ(fake.presents, before);
    vsync();
    CHECK_EQ(fake.presents, before + 1);
    CHECK_EQ(fake.shown[320 + 1], 9);
    destroy_bitmap(screen);                     /* ignored: set_gfx_mode owns it */
    CHECK(screen != NULL);
    destroy_bitmap(buf);
}

/* ---- keyboard, mouse, joystick -------------------------------------------------------- */

static void test_input(void)
{
    int k;
    CHECK_EQ(install_keyboard(), 0);
    memset(fake.raw, 0, sizeof(fake.raw));
    clear_keybuf();
    fake.raw[0x45] = 1;                         /* Esc */
    poll_keyboard();
    CHECK(key[KEY_ESC]);
    CHECK(keypressed());
    k = readkey();
    CHECK_EQ(k >> 8, KEY_ESC); CHECK_EQ(k & 255, 27);
    fake.raw[0x45] = 0;
    poll_keyboard();
    CHECK(!key[KEY_ESC]);
    CHECK(!keypressed());
    fake.raw[0x60] = 1;                         /* left shift */
    fake.raw[0x20] = 1;                         /* A */
    poll_keyboard();
    CHECK(key_shifts & KB_SHIFT_FLAG);
    k = readkey();
    CHECK_EQ(k & 255, 'A'); CHECK_EQ(k >> 8, KEY_A);
    fake.raw[0x60] = 0; fake.raw[0x20] = 0;
    fake.raw[0x4C] = 1;                         /* cursor up */
    poll_keyboard();
    CHECK(key[KEY_UP]);
    fake.raw[0x4C] = 0;
    poll_keyboard();
    clear_keybuf();
    simulate_keypress(('x') | (KEY_X << 8));
    CHECK_EQ(readkey() & 255, 'x');
    CHECK_EQ(scancode_to_ascii(KEY_B), 'b');
    CHECK(strcmp(scancode_to_name(KEY_SPACE), "SPACE") == 0);

    CHECK_EQ(install_mouse(), 3);
    fake.px = 100; fake.py = 50; fake.buttons = 1;
    poll_mouse();
    CHECK_EQ(mouse_x, 100); CHECK_EQ(mouse_y, 50); CHECK_EQ(mouse_b, 1);
    fake.px = 5000;
    poll_mouse();
    CHECK_EQ(mouse_x, SCREEN_W - 1);            /* the range */
    fake.buttons = 0;

    CHECK_EQ(install_joystick(JOY_TYPE_AUTODETECT), 0);
    CHECK_EQ(num_joysticks, 1);
    fake.keys[ACGAME_KEY_LEFT] = 1;
    fake.pad_buttons = 1u << ACGAME_PAD_B;
    poll_joystick();
    CHECK(joy[0].stick[0].axis[0].d1);
    CHECK_EQ(joy[0].stick[0].axis[0].pos, -128);
    CHECK(joy[0].button[1].b);
    CHECK(!joy[0].button[0].b);
    fake.keys[ACGAME_KEY_LEFT] = 0;
    fake.pad_buttons = 0;
    poll_joystick();
}

/* ---- timers ------------------------------------------------------------------------------ */

static volatile int ticks, pticks;
static void tick(void) { ticks++; }
static void ptick(void *p) { pticks += *(int *)p; }

static void test_timers(void)
{
    static int add = 2;
    a4_test_clock_us = 1000000;
    a4_test_clock_step_us = 1000;
    CHECK_EQ(install_timer(), 0);
    ticks = 0;
    CHECK_EQ(install_int_ex(tick, BPS_TO_TIMER(60)), 0);
    rest(1000);
    CHECK(ticks >= 59 && ticks <= 61);
    CHECK_EQ(install_param_int(ptick, &add, 10), 0);
    pticks = 0;
    rest(100);
    CHECK(pticks >= 18 && pticks <= 22);
    remove_param_int(ptick, &add);
    install_int_ex(tick, BPS_TO_TIMER(120));    /* a new speed for the same routine */
    ticks = 0;
    rest(500);
    CHECK(ticks >= 59 && ticks <= 61);
    remove_int(tick);
    ticks = 0;
    rest(100);
    CHECK_EQ(ticks, 0);
    {
        int r = retrace_count;
        rest(1000);
        CHECK(retrace_count - r >= 69 && retrace_count - r <= 71);
    }
    a4_test_clock_us = 0;
}

/* ---- packfiles, LZSS and datafiles ------------------------------------------------------- */

/* a tiny LZSS writer for the tests: literals, plus one back reference */
static int lz_pack(const unsigned char *in, int n, unsigned char *out)
{
    int o = 0, i = 0;
    while (i < n) {
        int flagpos = o++, bit, flags = 0;
        for (bit = 0; bit < 8 && i < n; bit++) {
            /* a run of the same byte 3+ long after the first: a reference to r-1 */
            int run = 0;
            if (i > 0) while (i + run < n && in[i + run] == in[i - 1] && run < 18) run++;
            if (run >= 3) {
                int r = (4096 - 18 + i - 1) & 4095;        /* where in[i-1] sits in the ring */
                out[o++] = (unsigned char)(r & 255);
                out[o++] = (unsigned char)(((r >> 4) & 0xF0) | (run - 3));
                i += run;
            } else {
                flags |= 1 << bit;
                out[o++] = in[i++];
            }
        }
        out[flagpos] = (unsigned char)flags;
    }
    return o;
}

static void put32(FILE *f, long v) { fputc((int)(v >> 24) & 255, f); fputc((int)(v >> 16) & 255, f); fputc((int)(v >> 8) & 255, f); fputc((int)v & 255, f); }
static void put16(FILE *f, int v) { fputc((v >> 8) & 255, f); fputc(v & 255, f); }

static void put_name(FILE *f, const char *name)
{
    put32(f, DAT_PROPERTY); put32(f, DAT_NAME); put32(f, (long)strlen(name)); fwrite(name, 1, strlen(name), f);
}

static void test_files(void)
{
    unsigned char text[200], packed[400];
    int n, i;
    FILE *f;
    PACKFILE *pf;
    DATAFILE *d, *o;
    for (i = 0; i < 200; i++) text[i] = (unsigned char)(i < 100 ? 'a' + i % 7 : 'z');
    n = lz_pack(text, 200, packed);
    CHECK(n < 190);
    f = fopen(tmp("lz.bin"), "wb");
    put32(f, F_PACK_MAGIC);
    fwrite(packed, 1, (size_t)n, f);
    fclose(f);
    pf = pack_fopen(tmp("lz.bin"), F_READ_PACKED);
    CHECK(pf != NULL);
    if (pf) {
        unsigned char got[260];
        long r = pack_fread(got, 260, pf);
        CHECK_EQ(r, 200);
        CHECK(memcmp(got, text, 200) == 0);
        pack_fclose(pf);
    }
    /* writing and reading words, longs and lines */
    pf = pack_fopen(tmp("words.bin"), F_WRITE);
    pack_iputw(0x1234, pf); pack_mputw(0x1234, pf); pack_iputl(0x12345678, pf); pack_mputl(-2, pf);
    pack_fputs("one\ntwo\r\nthree", pf);
    pack_fclose(pf);
    pf = pack_fopen(tmp("words.bin"), F_READ);
    CHECK_EQ(pack_igetw(pf), 0x1234); CHECK_EQ(pack_mgetw(pf), 0x1234);
    CHECK_EQ(pack_igetl(pf), 0x12345678); CHECK_EQ(pack_mgetl(pf), -2);
    {
        char line[32];
        CHECK(pack_fgets(line, 32, pf) && !strcmp(line, "one"));
        CHECK(pack_fgets(line, 32, pf) && !strcmp(line, "two"));
        CHECK(pack_fgets(line, 32, pf) && !strcmp(line, "three"));
        CHECK(pack_fgets(line, 32, pf) == NULL);
        CHECK(pack_feof(pf));
    }
    pack_fclose(pf);
    CHECK(exists(tmp("words.bin")));
    CHECK_EQ(file_size_ex(tmp("words.bin")), 2 + 2 + 4 + 4 + 14);

    /* a datafile: an 8-bit bitmap, a palette, packed data, nested files ("ALL." first, and as the grabber writes one) */
    f = fopen(tmp("test.dat"), "wb");
    put32(f, F_NOPACK_MAGIC);
    put32(f, DAT_MAGIC);
    put32(f, 5);
    put_name(f, "SPRITE");
    put32(f, DAT_BITMAP); put32(f, 2 + 4 + 8); put32(f, 2 + 4 + 8);
    put16(f, 8); put16(f, 4); put16(f, 2);
    for (i = 0; i < 8; i++) fputc(i + 1, f);
    put_name(f, "PAL");
    put32(f, DAT_PALETTE); put32(f, 768); put32(f, 768);
    for (i = 0; i < 256; i++) { fputc(i, f); fputc(255 - i, f); fputc(128, f); }
    put_name(f, "TEXT");
    put32(f, DAT_DATA); put32(f, n); put32(f, -200);    /* grabber order: bytes in file, then -object size (LZSS) */
    fwrite(packed, 1, (size_t)n, f);
    put_name(f, "INNER");
    put32(f, DAT_FILE); put32(f, 4 + 4 + 12 + 1 + 4 + 4 + 4 + 3); put32(f, 4 + 4 + 12 + 1 + 4 + 4 + 4 + 3);
    put32(f, DAT_MAGIC); put32(f, 1);
    put_name(f, "X"); put32(f, DAT_DATA); put32(f, 3); put32(f, 3); fwrite("xyz", 1, 3, f);
    put_name(f, "GRAB");
    put32(f, DAT_FILE); put32(f, 4 + 12 + 1 + 4 + 4 + 4 + 2); put32(f, 4 + 12 + 1 + 4 + 4 + 4 + 2);
    put32(f, 1);
    put_name(f, "Y"); put32(f, DAT_DATA); put32(f, 2); put32(f, 2); fwrite("yy", 1, 2, f);
    fclose(f);
    d = load_datafile(tmp("test.dat"));
    CHECK(d != NULL);
    if (d) {
        BITMAP *b = (BITMAP *)d[0].dat;
        RGB *p = (RGB *)d[1].dat;
        CHECK_EQ(d[0].type, DAT_BITMAP);
        CHECK_EQ(b->w, 4); CHECK_EQ(b->h, 2); CHECK_EQ(b->line[1][3], 8);
        CHECK_EQ(d[1].type, DAT_PALETTE); CHECK_EQ(p[255].r, 63); CHECK_EQ(p[255].g, 0); CHECK_EQ(p[0].b, 32);
        CHECK_EQ(d[2].type, DAT_DATA); CHECK_EQ(d[2].size, 200);
        CHECK(memcmp(d[2].dat, text, 200) == 0);
        CHECK_EQ(d[3].type, DAT_FILE);
        CHECK_EQ(d[4].type, DAT_FILE);
        CHECK_EQ(d[5].type, DAT_END);
        o = find_datafile_object(d, "GRAB/Y");
        CHECK(o && o->size == 2 && !memcmp(o->dat, "yy", 2));
        CHECK(!strcmp(get_datafile_property(&d[1], DAT_NAME), "PAL"));
        o = find_datafile_object(d, "sprite");
        CHECK(o == &d[0]);
        o = find_datafile_object(d, "INNER/X");
        CHECK(o && o->size == 3 && !memcmp(o->dat, "xyz", 3));
        unload_datafile(d);
    }
    o = load_datafile_object(tmp("test.dat"), "TEXT");
    CHECK(o != NULL);
    if (o) { CHECK_EQ(o->type, DAT_DATA); CHECK(memcmp(o->dat, text, 200) == 0); unload_datafile_object(o); }
    o = load_datafile_object(tmp("test.dat"), "SPRITE");
    CHECK(o && o->type == DAT_BITMAP && ((BITMAP *)o->dat)->line[0][0] == 1);
    unload_datafile_object(o);
    o = load_datafile_object(tmp("test.dat"), "INNER/X");
    CHECK(o && !memcmp(o->dat, "xyz", 3));
    unload_datafile_object(o);
    o = load_datafile_object(tmp("test.dat"), "GRAB/Y");
    CHECK(o && !memcmp(o->dat, "yy", 2));
    unload_datafile_object(o);
    o = load_datafile_object(tmp("test.dat"), "GRAB");
    CHECK(o && o->type == DAT_FILE && ((DATAFILE *)o->dat)[0].size == 2 && ((DATAFILE *)o->dat)[1].type == DAT_END);
    unload_datafile_object(o);
    CHECK(load_datafile_object(tmp("test.dat"), "NOPE") == NULL);

    /* the same datafile packed whole */
    {
        FILE *in = fopen(tmp("test.dat"), "rb");
        static unsigned char raw[4096], pk[8192];
        long len = (long)fread(raw, 1, sizeof(raw), in);
        int pn;
        fclose(in);
        pn = lz_pack(raw + 4, (int)len - 4, pk);
        f = fopen(tmp("packed.dat"), "wb");
        put32(f, F_PACK_MAGIC);
        fwrite(pk, 1, (size_t)pn, f);
        fclose(f);
        d = load_datafile(tmp("packed.dat"));
        CHECK(d != NULL);
        if (d) {
            CHECK_EQ(((BITMAP *)d[0].dat)->line[0][2], 3);
            CHECK(memcmp(d[2].dat, text, 200) == 0);
            unload_datafile(d);
        }
        pf = pack_fopen(tmp("packed.dat#PAL"), F_READ);
        CHECK(pf != NULL);
        if (pf) { CHECK_EQ(pack_getc(pf), 0); CHECK_EQ(pack_getc(pf), 255); pack_fclose(pf); }
    }
}

/* ---- pictures --------------------------------------------------------------------------------- */

static void test_pictures(void)
{
    BITMAP *b = pattern(13, 7), *l;
    PALETTE p, q;
    int x, y, same = 1, i;
    for (i = 0; i < 256; i++) { p[i].r = (unsigned char)(i & 63); p[i].g = (unsigned char)(63 - (i & 63)); p[i].b = (unsigned char)(i >> 2); }
    b->line[3][5] = 0xC5;                       /* needs a PCX run byte */
    CHECK_EQ(save_bitmap(tmp("t.pcx"), b, p), 0);
    l = load_bitmap(tmp("t.pcx"), q);
    CHECK(l != NULL);
    if (l) {
        CHECK_EQ(l->w, 13); CHECK_EQ(l->h, 7);
        for (y = 0; y < 7; y++) for (x = 0; x < 13; x++) same &= l->line[y][x] == b->line[y][x];
        CHECK(same);
        CHECK_EQ(q[77].r, p[77].r); CHECK_EQ(q[77].b, p[77].b);
        destroy_bitmap(l);
    }
    CHECK_EQ(save_bitmap(tmp("t.bmp"), b, p), 0);
    l = load_bitmap(tmp("t.bmp"), q);
    CHECK(l != NULL);
    if (l) {
        same = 1;
        for (y = 0; y < 7; y++) for (x = 0; x < 13; x++) same &= l->line[y][x] == b->line[y][x];
        CHECK(same);
        CHECK_EQ(q[200].g, p[200].g);
        destroy_bitmap(l);
    }
    destroy_bitmap(b);
}

/* ---- text --------------------------------------------------------------------------------- */

static void test_text(void)
{
    BITMAP *b = create_bitmap(64, 16);
    int x, y, n = 0;
    CHECK(font != NULL);
    CHECK_EQ(text_height(font), 8);
    CHECK_EQ(text_length(font, "abc"), 24);
    clear_bitmap(b);
    textout_ex(b, font, "A", 0, 0, 7, -1);
    for (y = 0; y < 8; y++) for (x = 0; x < 8; x++) n += b->line[y][x] == 7;
    CHECK(n > 10 && n < 40);
    CHECK_EQ(b->line[0][0], 0);                 /* 'A' starts in its middle */
    clear_to_color(b, 3);
    textout_ex(b, font, " ", 0, 0, 7, 2);
    CHECK_EQ(b->line[0][0], 2);                 /* the background colour */
    clear_bitmap(b);
    textprintf_centre_ex(b, font, 32, 8, 5, -1, "%d", 42);
    n = 0;
    for (y = 8; y < 16; y++) for (x = 0; x < 64; x++) n += b->line[y][x] == 5;
    CHECK(n > 10);
    CHECK_EQ(b->line[8][20], 0);                /* centred: nothing at the far left */
    {
        char buf[16];
        uszprintf(buf, 16, "%s-%d", "x", 7);
        CHECK(!strcmp(buf, "x-7"));
    }
    destroy_bitmap(b);
}

/* ---- sound -------------------------------------------------------------------------------- */

static void test_sound(void)
{
    SAMPLE *s;
    int16_t out[2 * 64];
    int v;
    CHECK_EQ(install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL), 0);
    s = create_sample(8, FALSE, 22050, 10);
    memset(s->data, 255, 10);                   /* full positive */
    v = play_sample(s, 255, 128, 1000, FALSE);
    CHECK(v >= 0);
    a4_mix_s16stereo(out, 64, 22050);
    CHECK(out[0] > 10000); CHECK(out[1] > 10000);
    CHECK_EQ(out[2 * 20], 0);                   /* ten frames long, then silence */
    CHECK(voice_check(v) == NULL);              /* play_sample's voice ends with it */
    v = play_sample(s, 255, 0, 1000, TRUE);     /* looped, hard left */
    a4_mix_s16stereo(out, 64, 22050);
    CHECK(out[2 * 40] > 10000); CHECK_EQ(out[2 * 40 + 1], 0);
    stop_sample(s);
    a4_mix_s16stereo(out, 64, 22050);
    CHECK_EQ(out[0], 0);
    /* WAV round trip */
    ((unsigned char *)s->data)[3] = 7;
    CHECK_EQ(save_sample(tmp("t.wav"), s), 0);
    {
        SAMPLE *l = load_sample(tmp("t.wav"));
        CHECK(l && l->len == 10 && l->bits == 8 && ((unsigned char *)l->data)[3] == 7);
        destroy_sample(l);
    }
    destroy_sample(s);
    remove_sound();
}

/* ---- MIDI on the synth ---------------------------------------------------------------------- */

void a4_audio_pump(void);
enum { SYNTH_NONE, SYNTH_PORT, SYNTH_MIX };     /* a4_internal.h's A4_SYNTH_ */

static void pump_ms(unsigned ms)
{
    a4_test_clock_us += (uint64_t)ms * 1000u;
    a4_audio_pump();
}

static void test_midi(void)
{
    static const unsigned char t0[] = { 0x00, 0xFF, 0x51, 0x03, 0x07, 0xA1, 0x20, 0x00, 0xFF, 0x2F, 0x00 };
    static const unsigned char t1[] = { 0x00, 0x90, 0x3C, 0x64, 0x60, 0x80, 0x3C, 0x00, 0x00, 0xFF, 0x2F, 0x00 };
    MIDI *m;
    FILE *fp;
    int dv, mv;
    unsigned long before;

    /* a MIDI file as a game ships it */
    fp = fopen(tmp("song.mid"), "wb");
    fwrite("MThd\0\0\0\6\0\1\0\2\0\140", 1, 14, fp);
    fwrite("MTrk\0\0\0", 1, 7, fp); fputc(sizeof(t0), fp); fwrite(t0, 1, sizeof(t0), fp);
    fwrite("MTrk\0\0\0", 1, 7, fp); fputc(sizeof(t1), fp); fwrite(t1, 1, sizeof(t1), fp);
    fclose(fp);
    m = load_midi(tmp("song.mid"));
    CHECK(m != NULL && m->divisions == 96 && m->track[0].len == (int)sizeof(t0) && m->track[1].len == (int)sizeof(t1));

    /* no synth: silent, as before, and the game goes on */
    memset(&fake_synth, 0, sizeof(fake_synth));
    a4_test_clock_us = 5000000;
    CHECK_EQ(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL), 0);
    CHECK_EQ(midi_driver->id, MIDI_NONE);
    CHECK_EQ(play_midi(m, FALSE), 0);
    CHECK_EQ(midi_pos, 0);
    midi_out((unsigned char *)"\x90\x40\x7f", 3);
    CHECK_EQ(fake_synth.plays, 0); CHECK_EQ(fake_synth.nbytes, 0);
    stop_midi();
    CHECK_EQ(midi_pos, -1);
    CHECK_EQ(get_midi_length(m), 0);
    remove_sound();
    CHECK_EQ(fake_synth.closes, 0);

    /* MIDI_NONE asked: the synth is left alone */
    fake_synth.mode = SYNTH_PORT;
    CHECK_EQ(install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL), 0);
    CHECK_EQ(fake_synth.opens, 0);
    remove_sound();

    /* the synth on the MIDI port: it plays itself, nothing is mixed here */
    CHECK_EQ(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL), 0);
    CHECK_EQ(fake_synth.opens, 1); CHECK_EQ(fake_synth.rate, 22050);
    CHECK(midi_driver->id != MIDI_NONE && strcmp(midi_driver->name, "GFOpenSynth") == 0);
    CHECK_EQ(fake_synth.volume, 255);
    CHECK_EQ(play_midi(m, FALSE), 0);
    CHECK_EQ(fake_synth.plays, 1); CHECK_EQ(fake_synth.loop, 0);
    /* what it was given is the file again */
    CHECK_EQ(fake_synth.smf_len, 14 + 8 + sizeof(t0) + 8 + sizeof(t1));
    CHECK(memcmp(fake_synth.smf, "MThd\0\0\0\6\0\1\0\2\0\140", 14) == 0);
    CHECK(memcmp(fake_synth.smf + 14, "MTrk\0\0\0", 7) == 0 && fake_synth.smf[21] == sizeof(t0));
    CHECK(memcmp(fake_synth.smf + 22, t0, sizeof(t0)) == 0);
    CHECK(memcmp(fake_synth.smf + 22 + sizeof(t0) + 8, t1, sizeof(t1)) == 0);
    CHECK_EQ(midi_pos, 0);
    fake_synth.beat = 3; fake_synth.ms = 2500;
    fake.audio_ok = 1;
    pump_ms(20);
    CHECK_EQ(midi_pos, 3); CHECK_EQ(midi_time, 2);
    CHECK_EQ(fake_synth.rendered, 0);
    midi_pause();
    CHECK_EQ(fake_synth.paused, 1);
    midi_pause();
    midi_resume();
    CHECK_EQ(fake_synth.paused, 0);
    CHECK_EQ(midi_seek(1), 0);
    CHECK_EQ(fake_synth.last_seek, 1); CHECK_EQ(midi_pos, 1);
    set_volume(-1, 128);
    CHECK_EQ(fake_synth.volume, 128);
    get_volume(&dv, &mv);
    CHECK_EQ(dv, 255); CHECK_EQ(mv, 128);
    midi_out((unsigned char *)"\x90\x40\x7f", 3);
    CHECK(fake_synth.nbytes == 3 && fake_synth.bytes[0] == 0x90 && fake_synth.bytes[2] == 0x7f);
    /* played once: at its end midi_pos goes negative */
    fake_synth.playing = 0;
    pump_ms(20);
    CHECK_EQ(midi_pos, -1);
    /* its length, without playing it */
    fake_synth.length_ms = 61500;
    CHECK_EQ(get_midi_length(m), 61); CHECK_EQ(midi_time, 61);
    /* looped between beats 2 and 6 */
    CHECK_EQ(play_looped_midi(m, 2, 6), 0);
    CHECK_EQ(fake_synth.loop, 1); CHECK_EQ(fake_synth.last_seek, 2); CHECK_EQ(midi_pos, 2);
    fake_synth.beat = 5;
    pump_ms(20);
    CHECK_EQ(midi_pos, 5);
    fake_synth.beat = 6;
    pump_ms(20);
    CHECK_EQ(fake_synth.last_seek, 2); CHECK_EQ(midi_pos, 2);
    fake_synth.beat = 0; fake_synth.loops = 1;           /* the song ended before beat 6 and began again */
    pump_ms(20);
    CHECK_EQ(fake_synth.beat, 2); CHECK_EQ(midi_pos, 2);
    /* a plain loop is the synth's own */
    CHECK_EQ(play_midi(m, TRUE), 0);
    before = (unsigned long)fake_synth.seeks;
    fake_synth.beat = 0; fake_synth.loops = 1;
    pump_ms(20);
    CHECK_EQ(fake_synth.seeks, before); CHECK_EQ(midi_pos, 0);
    play_midi(NULL, FALSE);
    CHECK_EQ(midi_pos, -1); CHECK_EQ(fake_synth.playing, 0);
    remove_sound();
    CHECK_EQ(fake_synth.closes, 1); CHECK_EQ(fake_synth.open, 0);

    /* no port: the synth is mixed with the samples and goes out with them */
    fake_synth.mode = SYNTH_MIX;
    fake_synth.level = 1000;
    fake.audio_frames = 0; fake.audio_last = 0;
    CHECK_EQ(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL), 0);
    CHECK_EQ(play_midi(m, FALSE), 0);
    pump_ms(100);
    CHECK_EQ(fake_synth.rendered, 2205);
    CHECK_EQ(fake.audio_frames, 2205);
    CHECK_EQ(fake.audio_last, 1000);
    {
        SAMPLE *s = create_sample(16, FALSE, 22050, 4410);
        int i;
        for (i = 0; i < 4410; i++) ((unsigned short *)s->data)[i] = 0x8000 + 32000;
        play_sample(s, 255, 128, 1000, FALSE);
        fake_synth.level = 20000;
        pump_ms(50);
        CHECK(fake.audio_last > 20000 && fake.audio_last <= 32767);     /* added, and clipped not wrapped */
        destroy_sample(s);
    }
    remove_sound();
    CHECK_EQ(fake_synth.closes, 2);
    destroy_midi(m);
    a4_test_clock_us = 0;
    memset(&fake_synth, 0, sizeof(fake_synth));
}

/* ---- directory searches ---------------------------------------------------------------------- */

static void test_find(void)
{
    struct al_ffblk ff;
    char pat[600];
    int found = 0;
    snprintf(pat, sizeof(pat), "%s/*.pcx", tmpdir);
    if (al_findfirst(pat, &ff, FA_ARCH | FA_RDONLY) == 0) {
        do { found += !strcmp(ff.name, "t.pcx"); } while (al_findnext(&ff) == 0);
        al_findclose(&ff);
    }
    CHECK_EQ(found, 1);
    snprintf(pat, sizeof(pat), "%s/*.none", tmpdir);
    CHECK(al_findfirst(pat, &ff, FA_ALL) != 0);
    CHECK(!strcmp(get_extension("data/x.dat"), "dat"));
    CHECK(!strcmp(get_filename("data/x.dat"), "x.dat"));
    {
        char b[64];
        replace_extension(b, "a/b.pcx", "bmp", 64);
        CHECK(!strcmp(b, "a/b.bmp"));
        append_filename(b, "a", "c.txt", 64);
        CHECK(!strcmp(b, "a/c.txt"));
    }
}

/* ---- the GUI (src/a4_gui.c) ------------------------------------------------------------ */

static int tm_x, tm_y, tm_reads, tm_z;
static int t_mouse_x(void) { return tm_x; }
static int t_mouse_y(void) { return tm_y; }
static int t_mouse_z(void) { return tm_z; }
static int t_mouse_b(void) { if (tm_reads > 0) { tm_reads--; return 1; } return 0; }
static void t_click(int x, int y) { tm_x = x; tm_y = y; tm_reads = 3; }

static const char *items[] = { "apple", "banana", "cherry", "damson", "elder" };
static char *t_getter(int index, int *size)
{
    if (index < 0) { *size = 5; return NULL; }
    return (char *)items[index];
}
static int f1_calls;
static int t_f1(void) { f1_calls++; return D_O_K; }
static int slider_seen = -1;
static int t_slider_cb(void *dp3, int d2) { (void)dp3; slider_seen = d2; return D_O_K; }

static void test_gui(void)
{
    static char ebuf[16];
    BITMAP *b;
    DIALOG_PLAYER *p;
    int th, n, fw;
    DIALOG dlg[] = {
        /* proc              x    y    w    h   fg  bg key  flags      d1  d2  dp                 dp2                   dp3 */
        { d_box_proc,         0,   0, 320, 200, 15,  1,  0, 0,          0,  0, NULL,              NULL,                 NULL },
        { d_button_proc,     10,  10,  60,  16, 15,  1, 'o', D_EXIT,     0,  0, (void *)"&OK",     NULL,                 NULL },
        { d_edit_proc,       10,  40, 100,  10, 15,  1,  0, 0,         10,  0, ebuf,              NULL,                 NULL },
        { d_list_proc,       10,  60, 100,  44, 15,  1,  0, D_EXIT,     0,  0, (void *)t_getter,  NULL,                 NULL },
        { d_slider_proc,    150,  10, 101,  10, 15,  1,  0, 0,        100, 10, NULL,              (void *)t_slider_cb,  NULL },
        { d_keyboard_proc,    0,   0,   5,   5,  0,  0,  0, 0,     KEY_F1,  0, (void *)t_f1,      NULL,                 NULL },
        { d_radio_proc,     150,  40,  60,   8, 15,  1,  0, D_SELECTED, 1,  0, (void *)"one",     NULL,                 NULL },
        { d_radio_proc,     150,  50,  60,   8, 15,  1,  0, 0,          1,  0, (void *)"two",     NULL,                 NULL },
        { d_check_proc,     150,  60,  60,   8, 15,  1,  0, 0,          1,  0, (void *)"check",   NULL,                 NULL },
        { d_textbox_proc,   150,  80, 120,  30, 15,  1,  0, 0,          0,  0, (void *)"one two three four five six seven eight nine ten eleven twelve", NULL, NULL },
        { d_text_proc,      200, 150,  50,   8, 15,  1,  0, D_HIDDEN,   0,  0, (void *)"hidden",  NULL,                 NULL },
        { NULL,               0,   0,   0,   0,  0,  0,  0, 0,          0,  0, NULL,              NULL,                 NULL },
    };

    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0), 0);
    install_keyboard();
    clear_keybuf();
    b = gui_get_screen();
    CHECK(b == screen);
    th = text_height(font);

    /* _draw_scrollable_frame (Liquid War 5's own boxes): frame always, bar only when rows overflow */
    {
        DIALOG f = { NULL, 20, 120, 60, 40, 5, 2, 0, 0, 0, 0, NULL, NULL, NULL };
        clear_to_color(b, 0);
        _draw_scrollable_frame(&f, 3, 0, 4, 5, 2);
        CHECK_EQ(getpixel(b, 20, 120), 5);
        CHECK_EQ(getpixel(b, 79, 159), 5);
        CHECK_EQ(getpixel(b, 70, 140), 0);           /* no bar: 3 rows fit in 4 */
        _draw_scrollable_frame(&f, 20, 0, 4, 5, 2);
        CHECK_EQ(getpixel(b, 67, 140), 5);           /* the bar's edge line */
        CHECK_EQ(getpixel(b, 75, 155), 2);           /* bar background below the thumb */
        CHECK_EQ(getpixel(b, 72, 125), 5);           /* the thumb at the top */
    }

    /* & shortcuts */
    CHECK_EQ(gui_strlen("&File"), text_length(font, "File"));
    CHECK_EQ(gui_strlen("a&&b"), text_length(font, "a&b"));
    {
        BITMAP *t = create_bitmap(64, 16);
        clear_to_color(t, 0);
        fw = gui_textout_ex(t, "&F", 0, 0, 9, -1, FALSE);
        CHECK_EQ(fw, text_length(font, "F"));
        CHECK_EQ(getpixel(t, 0, th), 9);             /* the underline */
        CHECK_EQ(getpixel(t, fw + 1, th), 0);
        destroy_bitmap(t);
    }

    gui_mouse_x = t_mouse_x; gui_mouse_y = t_mouse_y; gui_mouse_z = t_mouse_z; gui_mouse_b = t_mouse_b;
    tm_x = 300; tm_y = 190; tm_reads = 0; tm_z = 0;

    /* start, draw, focus */
    p = init_dialog(dlg, 2);
    CHECK(p != NULL);
    CHECK(active_dialog == dlg);
    CHECK_EQ(dlg[5].w, 0);                           /* d_keyboard_proc has no size */
    CHECK(dlg[2].flags & D_GOTFOCUS);
    CHECK(dlg[9].d1 > 1);                            /* the text box wrapped */
    clear_to_color(screen, 0);
    CHECK(update_dialog(p));
    CHECK_EQ(getpixel(screen, 10, 10), 15);          /* the button's frame */
    CHECK_EQ(getpixel(screen, 69, 25), 15);          /* and its shadow */
    CHECK_EQ(getpixel(screen, 200, 150), 1);         /* hidden text: only the box under it */

    /* typing into the edit box */
    simulate_ukeypress('h', KEY_H);
    simulate_ukeypress('i', KEY_I);
    CHECK(update_dialog(p));
    CHECK(strcmp(ebuf, "hi") == 0);
    CHECK_EQ(dlg[2].d2, 2);
    simulate_keypress(KEY_BACKSPACE << 8);
    simulate_keypress(KEY_HOME << 8);
    simulate_ukeypress('a', KEY_A);
    CHECK(update_dialog(p));
    CHECK(strcmp(ebuf, "ah") == 0);
    for (n = 0; n < 12; n++) simulate_ukeypress('x', KEY_X);
    CHECK(update_dialog(p));
    CHECK_EQ((int)strlen(ebuf), 10);                 /* d1 is the most */

    /* a key no object uses: d_keyboard_proc gets it */
    simulate_keypress(KEY_F1 << 8);
    CHECK(update_dialog(p));
    CHECK_EQ(f1_calls, 1);

    /* Tab: the focus moves on to the list */
    simulate_keypress(KEY_TAB << 8);
    CHECK(update_dialog(p));
    CHECK(dlg[3].flags & D_GOTFOCUS);
    CHECK(!(dlg[2].flags & D_GOTFOCUS));
    simulate_keypress(KEY_DOWN << 8);
    simulate_keypress(KEY_DOWN << 8);
    CHECK(update_dialog(p));
    CHECK_EQ(dlg[3].d1, 2);
    simulate_keypress(KEY_END << 8);
    CHECK(update_dialog(p));
    CHECK_EQ(dlg[3].d1, 4);
    CHECK_EQ(dlg[3].d2, 4 - (44 - 4) / th + 1);      /* scrolled to show it */

    /* a click in the list */
    simulate_keypress(KEY_HOME << 8);
    CHECK(update_dialog(p));
    t_click(30, 60 + 2 + th + 1);
    CHECK(update_dialog(p));
    CHECK_EQ(dlg[3].d1, 1);

    /* a click on the slider's middle */
    t_click(150 + 50, 14);
    CHECK(update_dialog(p));
    CHECK_EQ(dlg[4].d2, 50);
    CHECK_EQ(slider_seen, 50);
    simulate_keypress(KEY_RIGHT << 8);
    CHECK(update_dialog(p));                          /* the slider has the focus now */
    CHECK_EQ(dlg[4].d2, 51);
    tm_z = 3;
    CHECK(update_dialog(p));
    CHECK_EQ(dlg[4].d2, 54);                          /* the wheel */

    /* radio buttons: one of a group */
    t_click(155, 52);
    CHECK(update_dialog(p));
    CHECK(dlg[7].flags & D_SELECTED);
    CHECK(!(dlg[6].flags & D_SELECTED));

    /* a check box toggles */
    t_click(152, 62);
    CHECK(update_dialog(p));
    CHECK(dlg[8].flags & D_SELECTED);
    t_click(152, 62);
    CHECK(update_dialog(p));
    CHECK(!(dlg[8].flags & D_SELECTED));

    /* the button's shortcut (&OK) closes the dialog */
    simulate_ukeypress('o', KEY_O);
    CHECK(!update_dialog(p));
    CHECK_EQ(shutdown_dialog(p), 1);
    CHECK(active_dialog == NULL);

    /* a click on the D_EXIT button closes it too, and Esc gives -1 */
    p = init_dialog(dlg, -1);
    t_click(20, 15);
    CHECK(!update_dialog(p));
    CHECK_EQ(shutdown_dialog(p), 1);
    p = init_dialog(dlg, -1);
    simulate_keypress(KEY_ESC << 8);
    CHECK(!update_dialog(p));
    CHECK_EQ(shutdown_dialog(p), -1);

    /* a double click on a D_EXIT list closes on that list */
    p = init_dialog(dlg, -1);
    t_click(30, 60 + 3);
    CHECK(update_dialog(p));
    t_click(30, 60 + 3);
    CHECK(!update_dialog(p));
    CHECK_EQ(shutdown_dialog(p), 3);
    CHECK_EQ(dlg[3].d1, 0);

    /* placing */
    centre_dialog(dlg);
    CHECK_EQ(dlg[0].x, 0);
    CHECK_EQ(dlg[0].y, 0);
    position_dialog(dlg, 10, 20);
    CHECK_EQ(dlg[1].x, 20);
    CHECK_EQ(dlg[1].y, 30);
    set_dialog_color(dlg, 3, 4);
    CHECK_EQ(dlg[7].fg, 3);
    CHECK_EQ(dlg[7].bg, 4);

    CHECK_EQ(set_window_close_button(0), 0);
    set_window_close_hook(NULL);
    gui_mouse_x = NULL;
}

/* names some games read (Liquid War 5) */
static void test_compat(void)
{
    CHECK(strncmp(allegro_id, "Allegro 4", 9) == 0);
    CHECK(timer_driver && timer_driver->name && keyboard_driver->name && mouse_driver->name && joystick_driver->name);
    CHECK(KB_NORMAL != KB_EXTENDED);
    {
        BITMAP *cb = create_bitmap(2, 2);                 /* clear() is a function now, for C++ */
        clear_to_color(cb, 9);
        clear(cb);
        CHECK_EQ(getpixel(cb, 1, 1), 0);
        destroy_bitmap(cb);
    }
    CHECK(os_type == OSTYPE_AMIGA && OSTYPE_LINUX != OSTYPE_AMIGA && OSTYPE_WIN95 != OSTYPE_WIN98);
    CHECK_EQ(palette_color[0], 0);
    CHECK_EQ(palette_color[37], 37);
    CHECK_EQ(palette_color[255], 255);
    CHECK(COLORCONV_REDUCE_TO_256 & COLORCONV_32_TO_8);
    set_color_conversion(COLORCONV_REDUCE_TO_256);
    CHECK_EQ(get_color_conversion(), COLORCONV_REDUCE_TO_256);
    ASSERT(0);                                      /* nothing without DEBUGMODE */
}

/* grab_font_from_bitmap, load_dat_font, midi_out (Timmy Time, Out of Cash) */
static void test_fonts_more(void)
{
    BITMAP *b = create_bitmap(12, 6);
    FONT *f;
    FILE *fp;
    PALETTE pal;
    char *names[2];
    int i;
    /* border 7; glyph A 3x4 at (1,1), glyph B 2x4 at (5,1), glyph C 3x4 at (8,1) */
    clear_to_color(b, 7);
    rectfill(b, 1, 1, 3, 4, 0);
    putpixel(b, 2, 2, 15);
    rectfill(b, 5, 1, 6, 4, 0);
    putpixel(b, 5, 1, 15);
    rectfill(b, 8, 1, 10, 4, 0);
    f = grab_font_from_bitmap(b);
    CHECK(f != NULL);
    if (f) {
        CHECK(is_mono_font(f));
        CHECK_EQ(get_font_range_begin(f, 0), 32);
        CHECK_EQ(get_font_range_end(f, 0), 34);
        CHECK_EQ(text_height(f), 4);
        CHECK_EQ(text_length(f, " !\""), 3 + 2 + 3);
        {
            BITMAP *t = create_bitmap(10, 6);
            clear_to_color(t, 0);
            textout_ex(t, f, " !", 0, 0, 9, -1);
            CHECK_EQ(getpixel(t, 1, 1), 9);          /* A's dot */
            CHECK_EQ(getpixel(t, 3, 0), 9);          /* B's dot */
            CHECK_EQ(getpixel(t, 0, 0), 0);
            destroy_bitmap(t);
        }
        destroy_font(f);
    }
    putpixel(b, 9, 2, 20);                           /* a second colour: a colour font */
    f = grab_font_from_bitmap(b);
    CHECK(f && is_color_font(f));
    destroy_font(f);
    destroy_bitmap(b);

    fp = fopen(tmp("font.dat"), "wb");
    CHECK(fp != NULL);
    if (!fp) return;
    put32(fp, F_NOPACK_MAGIC);
    put32(fp, DAT_MAGIC);
    put32(fp, 3);
    put_name(fp, "PAL");
    put32(fp, DAT_PALETTE); put32(fp, 768); put32(fp, 768);
    for (i = 0; i < 256; i++) { fputc((i & 63) << 2, fp); fputc(4, fp); fputc(8, fp); }   /* 8-bit guns */
    put_name(fp, "SMALL");
    put32(fp, DAT_FONT); put32(fp, 2 + 95 * 8); put32(fp, 2 + 95 * 8);
    put16(fp, 8);
    for (i = 0; i < 95 * 8; i++) fputc(0x80, fp);
    put_name(fp, "BIG");
    put32(fp, DAT_FONT); put32(fp, 2 + 95 * 16); put32(fp, 2 + 95 * 16);
    put16(fp, 16);
    for (i = 0; i < 95 * 16; i++) fputc(0xC0, fp);
    fclose(fp);
    memset(pal, 0, sizeof(pal));
    f = load_dat_font(tmp("font.dat"), pal, NULL);
    CHECK(f && text_height(f) == 8);
    CHECK_EQ(pal[5].r, 5);
    destroy_font(f);
    names[0] = (char *)"BIG"; names[1] = NULL;
    f = load_dat_font(tmp("font.dat"), NULL, names);
    CHECK(f && text_height(f) == 16);
    destroy_font(f);
    names[0] = (char *)"NOPE";
    CHECK(load_dat_font(tmp("font.dat"), NULL, names) == NULL);
    midi_out((unsigned char *)"\x90\x40\x7f", 3);   /* silent, and safe */
}

static char *slurp(const char *path)
{
    static char buf[2048];
    FILE *f = fopen(path, "rb");
    size_t n = 0;
    buf[0] = 0;
    if (f) { n = fread(buf, 1, sizeof(buf) - 1, f); fclose(f); }
    buf[n] = 0;
    return buf;
}

/* config files: Overgod keeps options and keys in overgod.cfg; KQ pushes and pops */
static void test_config(void)
{
    FILE *f = fopen(tmp("overgod.cfg"), "w");
    char *t;
    CHECK(f != NULL);
    if (!f) return;
    fputs("# Overgod\nversion = 3\n\n[Options]\nsound = 1\r\nvolume=200\n# keys below\n[Keys]\nleft = 0x52\nname = Player One\n", f);
    fclose(f);
    set_config_file(tmp("overgod.cfg"));
    CHECK_EQ(get_config_int(NULL, "version", 0), 3);
    CHECK_EQ(get_config_int("options", "SOUND", 0), 1);         /* no case */
    CHECK_EQ(get_config_int("[Options]", "volume", 0), 200);
    CHECK_EQ(get_config_int("Keys", "left", 0), 0x52);
    CHECK_EQ(get_config_hex("Keys", "left", 0), 0x52);
    CHECK(strcmp(get_config_string("Keys", "name", ""), "Player One") == 0);
    CHECK_EQ(get_config_int("Keys", "missing", -9), -9);
    CHECK(get_config_float("Options", "volume", 0.0f) == 200.0f);
    set_config_int("Options", "volume", -40);
    set_config_int("Keys", "fire", 57);
    set_config_string("Net", "host", "amiga");
    set_config_int(NULL, "runs", 2);
    set_config_float("Options", "gamma", 1.5f);
    set_config_string("Options", "sound", NULL);                 /* taken out */
    CHECK_EQ(get_config_int("Options", "volume", 0), -40);
    CHECK_EQ(get_config_int("Options", "sound", 7), 7);
    set_config_id("Net", "mode", AL_ID('U','D','P',' '));
    CHECK_EQ(get_config_id("Net", "mode", 0), AL_ID('U','D','P',' '));
    flush_config_file();
    t = slurp(tmp("overgod.cfg"));
    CHECK(strstr(t, "# Overgod\nversion = 3\nruns = 2\n") != NULL);
    CHECK(strstr(t, "[Options]\nvolume = -40\ngamma = 1.5\n# keys below\n") != NULL);
    CHECK(strstr(t, "left = 0x52\nname = Player One\nfire = 57\n") != NULL);
    CHECK(strstr(t, "\n[Net]\nhost = amiga\nmode = UDP\n") != NULL);
    CHECK(strstr(t, "sound") == NULL);
    /* read back as a new run would */
    set_config_file(NULL);
    CHECK_EQ(get_config_int("Keys", "fire", 0), 0);
    set_config_file(tmp("overgod.cfg"));
    CHECK_EQ(get_config_int("Keys", "fire", 0), 57);
    CHECK_EQ(get_config_int(NULL, "runs", 0), 2);
    /* an override wins and is never written */
    override_config_data("[Keys]\nfire = 99\n", 18);
    CHECK_EQ(get_config_int("Keys", "fire", 0), 99);
    override_config_file(NULL);
    CHECK_EQ(get_config_int("Keys", "fire", 0), 57);
    /* KQ Lives: push, its own file, pop back */
    push_config_state();
    CHECK_EQ(get_config_int("Keys", "fire", 7), 7);
    set_config_data("[game]\nspeed = 4\n", 18);
    CHECK_EQ(get_config_int("game", "speed", 0), 4);
    pop_config_state();
    CHECK_EQ(get_config_int("Keys", "fire", 0), 57);
    CHECK_EQ(get_config_int("game", "speed", 3), 3);
    set_config_int("Keys", "fire", 58);
    set_config_file(NULL);                                      /* writes it back, as allegro_exit does */
    t = slurp(tmp("overgod.cfg"));
    CHECK(strstr(t, "fire = 58\n") != NULL);
}

/* truecolour: Atomic Tanks (16 or 32-bit) and Rafkill (16-bit) */
static int near(int a, int b) { return a - b <= 2 && b - a <= 2; }
static int near8(int a, int b) { return a - b <= 8 && b - a <= 8; }   /* 5 bits a gun */

static void test_truecolour(void)
{
    BITMAP *a, *b, *spr;
    RLE_SPRITE *rle;
    RGB red = { 63, 0, 0, 0 };
    int c, i;

    set_color_conversion(COLORCONV_TOTAL);              /* Allegro's own default */
    /* the formats */
    CHECK_EQ(makecol15(255, 0, 255), MASK_COLOR_15);
    CHECK_EQ(makecol16(255, 0, 255), MASK_COLOR_16);
    CHECK_EQ(makecol32(255, 0, 255), MASK_COLOR_32);
    CHECK_EQ(makecol24(1, 2, 3), 0x010203);
    CHECK_EQ(makeacol32(1, 2, 3, 4), 0x04010203);
    CHECK_EQ(geta32(makeacol32(1, 2, 3, 200)), 200);
    c = makecol16(200, 100, 50);
    CHECK(near8(getr16(c), 200) && near8(getg16(c), 100) && near8(getb16(c), 50));
    c = makecol15(200, 100, 50);
    CHECK(near8(getr15(c), 200) && near8(getg15(c), 100) && near8(getb15(c), 50));
    CHECK_EQ(getr16(makecol16(255, 255, 255)), 255);
    CHECK_EQ(_rgb_scale_5[31], 255);
    CHECK_EQ(_rgb_scale_6[63], 255);
    CHECK_EQ(_rgb_r_shift_16, 11);

    /* bitmaps at the colour depth */
    set_color_depth(16);
    CHECK_EQ(get_color_depth(), 16);
    CHECK_EQ(makecol(255, 0, 0), makecol16(255, 0, 0));
    CHECK(near(getg(makecol(10, 120, 30)), 120));
    a = create_bitmap(40, 30);
    CHECK(a != NULL);
    if (!a) return;
    CHECK_EQ(bitmap_color_depth(a), 16);
    CHECK_EQ(bitmap_mask_color(a), MASK_COLOR_16);
    CHECK_EQ(a->vtable->color_depth, 16);
    clear_to_color(a, makecol(0, 0, 255));
    CHECK_EQ(getpixel(a, 39, 29), makecol16(0, 0, 255));
    putpixel(a, 3, 4, makecol(255, 255, 0));
    CHECK_EQ(getpixel(a, 3, 4), makecol16(255, 255, 0));
    _putpixel16(a, 5, 5, 0x1234);
    CHECK_EQ(_getpixel16(a, 5, 5), 0x1234);
    CHECK_EQ(getpixel(a, 40, 0), -1);
    rectfill(a, 10, 10, 19, 12, makecol(0, 255, 0));
    CHECK_EQ(getpixel(a, 19, 12), makecol16(0, 255, 0));
    CHECK_EQ(getpixel(a, 20, 12), makecol16(0, 0, 255));
    hline(a, 0, 20, 39, makecol(255, 255, 255));
    CHECK_EQ(getpixel(a, 39, 20), 0xFFFF);
    floodfill(a, 15, 11, makecol(255, 0, 0));
    CHECK_EQ(getpixel(a, 10, 10), makecol16(255, 0, 0));
    CHECK_EQ(getpixel(a, 9, 10), makecol16(0, 0, 255));
    {
        BITMAP *sub = create_sub_bitmap(a, 10, 10, 5, 5);
        CHECK(sub && bitmap_color_depth(sub) == 16);
        if (sub) { putpixel(sub, 1, 1, 7); destroy_bitmap(sub); }
        CHECK_EQ(getpixel(a, 11, 11), 7);
    }

    /* 24 and 32-bit pixels */
    b = create_bitmap_ex(24, 8, 8);
    CHECK(b && bitmap_color_depth(b) == 24);
    if (b) {
        putpixel(b, 7, 7, 0x123456);
        CHECK_EQ(getpixel(b, 7, 7), 0x123456);
        CHECK_EQ(_getpixel24(b, 7, 7), 0x123456);
        CHECK_EQ(b->line[7][21], 0x12);                     /* R, G, B in memory */
        destroy_bitmap(b);
    }
    b = create_bitmap_ex(32, 40, 30);
    CHECK(b != NULL);
    if (!b) { destroy_bitmap(a); return; }
    circlefill(b, 20, 15, 5, makecol32(9, 8, 7));
    CHECK_EQ(_getpixel32(b, 20, 15), makecol32(9, 8, 7));
    CHECK_EQ(getpixel(b, 0, 0), 0);

    /* blits between depths */
    blit(a, b, 0, 0, 0, 0, 40, 30);
    c = getpixel(b, 3, 4);
    CHECK(near(getr32(c), 255) && near(getg32(c), 255) && getb32(c) == 0);
    CHECK_EQ(getpixel(b, 39, 29), makecol32(0, 0, 255));
    set_color(5, &red);
    {
        BITMAP *e = create_bitmap_ex(8, 4, 4);
        clear_to_color(e, 5);
        blit(e, a, 0, 0, 0, 0, 4, 4);
        CHECK_EQ(getpixel(a, 0, 0), makecol16(255, 0, 0));
        /* an 8-bit sprite on a truecolour bitmap: 0 is clear, the rest through the palette */
        putpixel(e, 1, 1, 0);
        clear_to_color(a, 0);
        draw_sprite(a, e, 0, 0);
        CHECK_EQ(getpixel(a, 1, 1), 0);
        CHECK_EQ(getpixel(a, 2, 2), makecol16(255, 0, 0));
        destroy_bitmap(e);
    }
    CHECK_EQ(palette_color[5], makecol16(255, 0, 0));    /* palette_color follows the depth */

    /* sprites with the mask */
    spr = create_bitmap(4, 4);
    clear_to_color(spr, MASK_COLOR_16);
    putpixel(spr, 2, 2, makecol(255, 255, 255));
    clear_to_color(a, makecol(0, 0, 0));
    draw_sprite(a, spr, 10, 10);
    CHECK_EQ(getpixel(a, 12, 12), 0xFFFF);
    CHECK_EQ(getpixel(a, 11, 11), 0);
    masked_blit(spr, a, 0, 0, 20, 20, 4, 4);
    CHECK_EQ(getpixel(a, 22, 22), 0xFFFF);
    CHECK_EQ(getpixel(a, 21, 21), 0);
    draw_sprite_h_flip(a, spr, 0, 20);
    CHECK_EQ(getpixel(a, 1, 22), 0xFFFF);
    stretch_sprite(a, spr, 30, 0, 8, 8);
    CHECK_EQ(getpixel(a, 34, 4), 0xFFFF);
    CHECK_EQ(getpixel(a, 30, 0), 0);
    rotate_sprite(a, spr, 0, 0, itofix(64));
    rle = get_rle_sprite(spr);
    CHECK(rle && rle->color_depth == 16);
    if (rle) {
        clear_to_color(a, makecol(0, 0, 255));
        draw_rle_sprite(a, rle, 5, 5);
        CHECK_EQ(getpixel(a, 7, 7), 0xFFFF);
        CHECK_EQ(getpixel(a, 6, 6), makecol16(0, 0, 255));
        destroy_rle_sprite(rle);
    }

    /* blenders */
    clear_to_color(a, 0);
    set_trans_blender(0, 0, 0, 128);
    draw_trans_sprite(a, spr, 0, 0);
    c = getpixel(a, 2, 2);
    CHECK(getr16(c) > 110 && getr16(c) < 140 && near(getr16(c), getb16(c)));
    CHECK_EQ(getpixel(a, 1, 1), 0);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    clear_to_color(b, makecol32(200, 0, 0));
    set_trans_blender(0, 0, 0, 64);
    rectfill(b, 0, 0, 3, 3, makecol32(0, 0, 200));
    c = getpixel(b, 1, 1);
    CHECK(near(getr32(c), 150) && near(getb32(c), 50));
    solid_mode();
    set_add_blender(0, 0, 0, 255);
    clear_to_color(b, makecol32(100, 100, 100));
    {
        BITMAP *s32 = create_bitmap_ex(32, 2, 2);
        clear_to_color(s32, makecol32(100, 50, 0));
        draw_trans_sprite(b, s32, 0, 0);
        CHECK_EQ(getpixel(b, 1, 1), makecol32(200, 150, 100));
        set_multiply_blender(0, 0, 0, 255);
        clear_to_color(b, makecol32(128, 128, 128));
        clear_to_color(s32, makecol32(255, 128, 0));
        draw_trans_sprite(b, s32, 0, 0);
        c = getpixel(b, 0, 0);
        CHECK(near(getr32(c), 128) && near(getg32(c), 64) && getb32(c) == 0);
        set_screen_blender(0, 0, 0, 255);
        clear_to_color(b, makecol32(128, 0, 0));
        clear_to_color(s32, makecol32(128, 0, 0));
        draw_trans_sprite(b, s32, 0, 0);
        CHECK(near(getr32(getpixel(b, 0, 0)), 192));
        /* the alpha blender: a 32-bit sprite's own alpha */
        set_alpha_blender();
        clear_to_color(b, 0);
        clear_to_color(s32, makeacol32(255, 255, 255, 64));
        draw_trans_sprite(b, s32, 0, 0);
        CHECK(near(getr32(getpixel(b, 0, 0)), 64));
        /* lit: towards the blender's colour by the light level */
        set_trans_blender(255, 0, 0, 0);
        clear_to_color(s32, makecol32(0, 0, 255));
        clear_to_color(b, 0);
        draw_lit_sprite(b, s32, 0, 0, 255);
        CHECK_EQ(getpixel(b, 0, 0), makecol32(255, 0, 0));
        draw_lit_sprite(b, s32, 0, 0, 0);
        CHECK_EQ(getpixel(b, 0, 0), makecol32(0, 0, 255));
        destroy_bitmap(s32);
    }
    set_trans_blender(0, 0, 0, 255);

    /* text in truecolour */
    clear_to_color(a, 0);
    textout_ex(a, font, "I", 0, 0, makecol(0, 255, 0), makecol(0, 0, 255));
    {
        int on = 0, bg = 0, y, x;
        for (y = 0; y < 8; y++) for (x = 0; x < 8; x++) {
            int p = getpixel(a, x, y);
            if (p == makecol16(0, 255, 0)) on++;
            else if (p == makecol16(0, 0, 255)) bg++;
        }
        CHECK(on > 0 && bg > 0 && on + bg == 64);
    }

    /* pictures: a 32-bit one saved as a 24-bit BMP comes back at the depth asked for */
    clear_to_color(b, makecol32(10, 20, 30));
    putpixel(b, 0, 0, makecol32(250, 0, 5));
    CHECK_EQ(save_bmp(tmp("tc.bmp"), b, NULL), 0);
    set_color_depth(32);
    {
        BITMAP *l = load_bmp(tmp("tc.bmp"), NULL);
        CHECK(l && bitmap_color_depth(l) == 32 && l->w == 40);
        if (l) { CHECK_EQ(getpixel(l, 0, 0), makecol32(250, 0, 5)); CHECK_EQ(getpixel(l, 5, 5), makecol32(10, 20, 30)); destroy_bitmap(l); }
        set_color_depth(16);
        l = load_bitmap(tmp("tc.bmp"), NULL);
        CHECK(l && bitmap_color_depth(l) == 16);
        if (l) { CHECK_EQ(getpixel(l, 5, 5), makecol16(10, 20, 30)); destroy_bitmap(l); }
        set_color_conversion(COLORCONV_NONE);
        l = load_bitmap(tmp("tc.bmp"), NULL);
        CHECK(l && bitmap_color_depth(l) == 24);
        destroy_bitmap(l);
        set_color_conversion(COLORCONV_TOTAL);
    }

    /* a 16-bit screen, shown through the 6x7x6 cube on the 8-bit one */
    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0), 0);
    CHECK_EQ(bitmap_color_depth(screen), 16);
    clear_to_color(screen, makecol(255, 0, 0));
    putpixel(screen, 1, 0, makecol(255, 255, 255));
    putpixel(screen, 2, 0, makecol(0, 128, 0));
    vsync();
    CHECK_EQ(fake.shown[0], 210);                        /* red: 5 * 42 */
    CHECK_EQ(fake.shown[1], 251);                        /* white */
    CHECK_EQ(fake.shown[2], 18);                         /* green 3 of 6: 3 * 6 */
    CHECK(fake.shown_pal[210].r == 255 && fake.shown_pal[210].g == 0 && fake.shown_pal[210].b == 0);
    CHECK(fake.shown_pal[251].r == 255 && fake.shown_pal[251].g == 255);
    set_palette(default_palette);                        /* does not touch the cube */
    CHECK(fake.shown_pal[210].r == 255 && fake.shown_pal[210].g == 0);
    {
        GFX_MODE_LIST *ml = get_gfx_mode_list(GFX_AUTODETECT);
        int has16 = 0;
        for (i = 0; ml && i < ml->num_modes; i++) if (ml->mode[i].bpp == 16 && ml->mode[i].width == 320) has16 = 1;
        CHECK(has16);
        destroy_gfx_mode_list(ml);
    }
    set_color_depth(32);
    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0), 0);
    CHECK_EQ(bitmap_color_depth(screen), 32);
    clear_to_color(screen, makecol(0, 0, 255));
    vsync();
    CHECK_EQ(fake.shown[100], 5);                        /* blue */
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

    /* mixer and 8-bit again */
    set_mixer_quality(1);
    CHECK_EQ(get_mixer_quality(), 1);
    CHECK(get_mixer_voices() > 0);
    destroy_bitmap(spr);
    destroy_bitmap(a);
    destroy_bitmap(b);
    set_color_depth(8);
    CHECK_EQ(palette_color[5], 5);
    a = create_bitmap(1, 1);
    CHECK_EQ(bitmap_color_depth(a), 8);
    destroy_bitmap(a);
}

/* a palette as Allegro 4.0's grabber kept it: 4 bytes a colour, 6-bit (KRaptor) */
static void test_old_palette(void)
{
    FILE *f = fopen(tmp("pal4.dat"), "wb");
    DATAFILE *d;
    int i;
    put32(f, F_NOPACK_MAGIC);
    put32(f, DAT_MAGIC);
    put32(f, 1);
    put_name(f, "PAL");
    put32(f, DAT_PALETTE); put32(f, 1024); put32(f, 1024);
    for (i = 0; i < 256; i++) { fputc(i & 63, f); fputc(63 - (i & 63), f); fputc(7, f); fputc(0xEE, f); }
    fclose(f);
    d = load_datafile(tmp("pal4.dat"));
    CHECK(d != NULL);
    if (d) {
        RGB *p = (RGB *)d[0].dat;
        CHECK_EQ(p[1].r, 1); CHECK_EQ(p[1].g, 62); CHECK_EQ(p[1].b, 7);
        CHECK_EQ(p[255].r, 63); CHECK_EQ(p[255].g, 0); CHECK_EQ(p[255].b, 7);
        unload_datafile(d);
    }
}

/* ---- configuration ------------------------------------------------------------------------ */

static void test_config_kraptor(void)
{
    static const char script[] =
        "# Kraptor's level script\r\n"
        "top = 1\r\n"
        "[Nivel_1]\r\n"
        "  enemigos = 12  \r\n"
        "speed=0x1F\r\n"
        "scale = 1.5\r\n"
        "name = \"first level\"\r\n"
        "ia = up down \"to the left\" 7\r\n"
        "[sound]\n"
        "card = SB16\n"
        "blank =\n"
        "last = 9";                                 /* no newline at the end */
    char line[128];
    FILE *fp;
    int n;
    char **av;

    set_config_data(script, (int)strlen(script));
    CHECK_EQ(get_config_int(NULL, "top", 0), 1);
    CHECK_EQ(get_config_int("nivel_1", "ENEMIGOS", 0), 12);       /* any case */
    CHECK_EQ(get_config_int("[Nivel_1]", "enemigos", 0), 12);     /* with brackets */
    CHECK_EQ(get_config_int("Nivel_1", "speed", 0), 31);           /* 0x */
    CHECK_EQ(get_config_hex("Nivel_1", "speed", 0), 0x1F);
    CHECK(get_config_float("Nivel_1", "scale", 0) == 1.5f);
    CHECK(get_config_float("Nivel_1", "nothing", 2.25f) == 2.25f);
    CHECK_EQ(get_config_int("Nivel_1", "top", -5), -5);            /* top is in the global section */
    CHECK_EQ(get_config_int("sound", "last", 0), 9);
    CHECK(strcmp(get_config_string("sound", "blank", "def"), "") == 0);
    CHECK(strcmp(get_config_string("sound", "missing", "def"), "def") == 0);
    CHECK_EQ(get_config_id("sound", "card", 0), (int)AL_ID('S', 'B', '1', '6'));
    CHECK_EQ(get_config_int("sound", "card", 4), 0);               /* not a number: 0, as 4.4's strtol */
    av = get_config_argv("Nivel_1", "ia", &n);
    CHECK_EQ(n, 4);
    if (av && n == 4) {
        CHECK(strcmp(av[0], "up") == 0);
        CHECK(strcmp(av[2], "to the left") == 0);
        CHECK(strcmp(av[3], "7") == 0);
        CHECK(av[4] == NULL);
    }
    CHECK(get_config_argv("x", "y", &n) == NULL);
    CHECK_EQ(n, 0);

    /* an override wins, and set_config_* writes into it when it has the name */
    override_config_data("[sound]\ncard = GUS\n", 18);
    CHECK_EQ(get_config_id("sound", "card", 0), (int)AL_ID('G', 'U', 'S', ' '));
    CHECK_EQ(get_config_int("sound", "last", 0), 9);
    override_config_data(NULL, 0);
    CHECK_EQ(get_config_id("sound", "card", 0), (int)AL_ID('S', 'B', '1', '6'));

    /* a file: made on set, kept comments, written on flush, read back */
    fp = fopen(tmp("k.cfg"), "w");
    if (fp) { fputs("# my settings\n[video]\nw = 320\n", fp); fclose(fp); }
    set_config_file(tmp("k.cfg"));
    CHECK_EQ(get_config_int("video", "w", 0), 320);
    set_config_int("video", "w", 640);
    set_config_int("video", "h", -480);
    set_config_hex("video", "mask", 0xBEEF);
    set_config_float("sound", "volume", 0.75f);
    set_config_id("sound", "card", AL_ID('A', 'H', 'I', ' '));
    set_config_string(NULL, "lang", "es");
    flush_config_file();
    fp = fopen(tmp("k.cfg"), "r");
    CHECK(fp != NULL);
    if (fp) {
        CHECK(fgets(line, sizeof(line), fp) && strcmp(line, "# my settings\n") == 0);
        fclose(fp);
    }
    set_config_file(NULL);
    CHECK_EQ(get_config_int("video", "w", 0), 0);
    set_config_file(tmp("k.cfg"));
    CHECK_EQ(get_config_int("video", "w", 0), 640);
    CHECK_EQ(get_config_int("video", "h", 0), -480);
    CHECK_EQ(get_config_hex("video", "mask", 0), 0xBEEF);
    CHECK(get_config_float("sound", "volume", 0) == 0.75f);
    CHECK_EQ(get_config_id("sound", "card", 0), (int)AL_ID('A', 'H', 'I', ' '));
    CHECK(strcmp(get_config_string("", "lang", ""), "es") == 0);
    set_config_string("video", "h", "");                           /* an empty value removes it */
    CHECK_EQ(get_config_int("video", "h", 7), 7);

    /* push and pop keep the file; the inner state starts empty */
    push_config_state();
    CHECK_EQ(get_config_int("video", "w", 1), 1);
    set_config_data("[video]\nw = 2\n", 14);
    CHECK_EQ(get_config_int("video", "w", 1), 2);
    pop_config_state();
    CHECK_EQ(get_config_int("video", "w", 0), 640);
    pop_config_state();                                             /* nothing pushed: no change */
    CHECK_EQ(get_config_int("video", "w", 0), 640);
    set_config_file(NULL);
}

/* ---- menus (Kraptor's menu bar) ------------------------------------------------------- */

static int mn_calls, mn_last;
static MENU *mn_active;
static int mn_new(void) { mn_calls++; mn_last = 1; mn_active = active_menu; return D_O_K; }
static int mn_quit(void) { mn_calls++; mn_last = 2; return D_CLOSE; }
static int mn_sub(void) { mn_calls++; mn_last = 3; return D_REDRAW; }
static int mb_reads;
static int t_mouse_b_held(void) { return mb_reads > 0 ? (mb_reads--, 1) : 0; }
static int dm_x, dm_y, dm_w, dm_h, dm_items;
static void t_draw_menu(int x, int y, int w, int h) { dm_x = x; dm_y = y; dm_w = w; dm_h = h; }
static void t_draw_item(MENU *m, int x, int y, int w, int h, int bar, int sel) { (void)m; (void)x; (void)y; (void)w; (void)h; (void)bar; (void)sel; dm_items++; }

/* KRaptor installs the mouse before its 640x480 mode: the new mode must
 * give the pointer the whole screen, not the old 320x200 range */
static void test_mouse_new_mode(void)
{
    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0), 0);
    CHECK_EQ(install_mouse(), 3);
    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0), 0);
    fake.px = 600; fake.py = 400; fake.buttons = 0;
    poll_mouse();
    CHECK_EQ(mouse_x, 600); CHECK_EQ(mouse_y, 400);
    fake.px = 5000; fake.py = 5000;
    poll_mouse();
    CHECK_EQ(mouse_x, 639); CHECK_EQ(mouse_y, 479);
    fake.px = fake.py = 0;
    poll_mouse();
}

static void test_menus(void)
{
    static MENU sub[] = {
        { "&Easy", mn_sub, NULL, D_SELECTED, NULL },
        { "&Hard", mn_sub, NULL, 0, NULL },
        { NULL, NULL, NULL, 0, NULL },
    };
    static MENU game[] = {
        { "&New\tF2", mn_new, NULL, 0, NULL },
        { "", NULL, NULL, 0, NULL },
        { "&Level", NULL, sub, 0, NULL },
        { "&Off", mn_new, NULL, D_DISABLED, NULL },
        { "&Quit", mn_quit, NULL, 0, NULL },
        { NULL, NULL, NULL, 0, NULL },
    };
    static MENU top[] = {
        { "&Game", NULL, game, 0, NULL },
        { "&Help", mn_new, NULL, 0, NULL },
        { NULL, NULL, NULL, 0, NULL },
    };
    DIALOG dlg[] = {
        { d_menu_proc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, top, NULL, NULL },
        { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL },
    };
    MENU_PLAYER *mp;
    DIALOG_PLAYER *dp;
    int th = text_height(font), ih = th + 4, r;

    CHECK_EQ(set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0), 0);
    install_keyboard();
    clear_keybuf();
    gui_fg_color = 15; gui_bg_color = 1; gui_mg_color = 8;
    gui_mouse_x = t_mouse_x; gui_mouse_y = t_mouse_y; gui_mouse_z = t_mouse_z; gui_mouse_b = t_mouse_b;
    tm_x = 319; tm_y = 199; tm_reads = 0; tm_z = 0;

    /* a drop-down: drawn, keys move over the separator, Enter picks and calls the proc */
    clear_to_color(screen, 0);
    mp = init_menu(game, 10, 20);
    CHECK(mp != NULL);
    CHECK_EQ(getpixel(screen, 10, 20), 15);                 /* the frame */
    CHECK_EQ(getpixel(screen, 12, 22), 1);                  /* an item, not highlighted */
    simulate_keypress(KEY_DOWN << 8);                       /* New */
    simulate_keypress(KEY_DOWN << 8);                       /* over the separator to Level */
    CHECK(update_menu(mp));
    CHECK_EQ(getpixel(screen, 12, 21 + 2 * ih + 1), 15);    /* Level highlighted */
    CHECK_EQ(getpixel(screen, 12, 21 + 1), 1);              /* New no longer */
    simulate_keypress(KEY_UP << 8);
    simulate_keypress(KEY_ENTER << 8);
    CHECK(!update_menu(mp));
    mn_calls = 0; mn_active = NULL;
    CHECK_EQ(shutdown_menu(mp), 0);
    CHECK_EQ(mn_calls, 1);
    CHECK(mn_active == &game[0]);                           /* active_menu during the proc */
    CHECK_EQ(getpixel(screen, 10, 20), 0);                  /* what it covered is back */

    /* a child: Right opens it, Enter picks in it; the root gives its own open item */
    mp = init_menu(game, 10, 20);
    simulate_ukeypress('l', KEY_L);                         /* &Level: the shortcut opens it */
    simulate_keypress(KEY_DOWN << 8);                       /* Easy -> Hard */
    simulate_keypress(KEY_ENTER << 8);
    CHECK(!update_menu(mp));
    mn_calls = 0;
    CHECK_EQ(shutdown_menu(mp), 2);
    CHECK_EQ(mn_calls, 1);
    CHECK_EQ(mn_last, 3);

    /* Esc in a child goes back; Esc again ends with -1; a disabled item does nothing */
    mp = init_menu(game, 10, 20);
    simulate_keypress(KEY_DOWN << 8); simulate_keypress(KEY_DOWN << 8);
    simulate_keypress(KEY_RIGHT << 8);
    simulate_keypress(KEY_ESC << 8);
    simulate_keypress(KEY_DOWN << 8);                       /* Off, disabled */
    simulate_keypress(KEY_ENTER << 8);
    CHECK(update_menu(mp));
    simulate_keypress(KEY_ESC << 8);
    CHECK(!update_menu(mp));
    mn_calls = 0;
    CHECK_EQ(shutdown_menu(mp), -1);
    CHECK_EQ(mn_calls, 0);

    /* the mouse: a click on an item picks it; a click outside ends the menu */
    mp = init_menu(game, 10, 20);
    t_click(20, 21 + 4 * ih + 2);                           /* Quit */
    CHECK(update_menu(mp));                                 /* pressed */
    tm_reads = 0;
    CHECK(!update_menu(mp) || !update_menu(mp));
    mn_calls = 0;
    CHECK_EQ(shutdown_menu(mp), 4);
    CHECK_EQ(mn_last, 2);
    mp = init_menu(game, 10, 20);
    t_click(300, 190);
    CHECK(!update_menu(mp));
    CHECK_EQ(shutdown_menu(mp), -1);

    /* off the screen's edge: moved back on */
    mp = init_menu(game, 310, 190);
    CHECK(update_menu(mp));
    CHECK_EQ(shutdown_menu(mp), -1);
    CHECK_EQ(getpixel(screen, 319, 199), 0);

    /* the game's own look */
    {
        void (*dm)(int, int, int, int) = gui_menu_draw_menu;
        CHECK(dm != NULL);
    }
    gui_menu_draw_menu = t_draw_menu; gui_menu_draw_menu_item = t_draw_item;
    dm_items = 0;
    mp = init_menu(game, 30, 40);
    CHECK_EQ(dm_x, 30); CHECK_EQ(dm_y, 40);
    CHECK_EQ(dm_items, 5);
    CHECK(dm_w > text_length(font, "New") + text_length(font, "F2"));
    CHECK_EQ(dm_h, 5 * ih + 3);
    simulate_keypress(KEY_ESC << 8);
    update_menu(mp);
    shutdown_menu(mp);

    /* d_menu_proc: the bar sizes itself; Alt+G opens Game; a proc's D_CLOSE closes the dialog */
    dp = init_dialog(dlg, -1);
    CHECK(dlg[0].w > text_length(font, "Game") + text_length(font, "Help"));
    CHECK_EQ(dlg[0].h, ih + 2);
    tm_x = 0; tm_y = 0;                                     /* the pointer resting on the bar's edge changes nothing */
    fake.raw[0x64] = 1;                                     /* left Alt */
    simulate_keypress(KEY_G << 8);
    simulate_keypress(KEY_UP << 8);                         /* round to Quit */
    simulate_keypress(KEY_ENTER << 8);
    mn_last = 0;
    r = update_dialog(dp);
    fake.raw[0x64] = 0;
    poll_keyboard();
    CHECK(!r);
    CHECK_EQ(mn_last, 2);
    CHECK_EQ(shutdown_dialog(dp), 0);
    /* a click on Help (no child) calls its proc, and the dialog stays */
    dp = init_dialog(dlg, -1);
    mb_reads = 2; gui_mouse_b = t_mouse_b_held;
    tm_x = 1 + text_length(font, "Game") + 16 + 4; tm_y = 3;
    mn_last = 0;
    CHECK(update_dialog(dp));
    CHECK_EQ(mn_last, 1);
    CHECK(update_dialog(dp));
    shutdown_dialog(dp);
    gui_mouse_b = t_mouse_b;

    /* the aintern names and the small calls */
    CHECK(gui_shadow_box_proc == d_shadow_box_proc);
    CHECK(gui_button_proc == d_button_proc);
    CHECK(gui_mouse_focus);
    CHECK_EQ(palette_color[0], 0);
    CHECK_EQ(palette_color[200], 200);
    CHECK(&_default_font == font);
    reload_config_texts("es");
    CHECK(strcmp(get_config_text("Sound"), "Sound") == 0);
    CHECK_EQ(stricmp("Kraptor", "KRAPTOR"), 0);
    CHECK_EQ(fmul(itofix(3), itofix(4)), itofix(12));
    CHECK_EQ(fdiv(itofix(3), itofix(4)), ftofix(0.75));
    set_trans_blender(128, 128, 128, 128);
    {
        /* Allegro's text-box helper: counts lines, draws from the offset, clears below */
        static char tb[] = "one two three four five six seven eight nine ten";
        int ls = 0, cw = text_length(font, "x"), th2 = text_height(font);
        _draw_textbox(tb, &ls, 0, 0, TRUE, 8, 0, 0, cw * 14 + 8, th2 * 3 + 4, FALSE, 15, 1, 8);
        CHECK(ls >= 4);
        clear_to_color(screen, 0);
        _draw_textbox(tb, &ls, 1, 1, TRUE, 8, 0, 0, cw * 14 + 8, th2 * 3 + 4, FALSE, 15, 1, 8);
        CHECK_EQ(getpixel(screen, cw * 14, 2), 1);           /* the background of a drawn row */
        CHECK_EQ(getpixel(screen, cw * 14 + 20, 2), 0);      /* nothing outside the box */
        {
            int lc = 0;
            _draw_textbox(tb, &lc, 0, 0, FALSE, 8, 0, 0, cw * 14 + 8, th2 * 3 + 4, FALSE, 15, 1, 8);
            CHECK(lc >= ls - 1);                              /* without words: cut anywhere */
        }
    }
    CHECK(stricmp("a", "b") < 0);
    gui_mouse_x = NULL;
}

/* ---- FLI and FLC ------------------------------------------------------------------------ */

static unsigned char fl_buf[4096];
static int fl_n;
static void fl8(int v) { fl_buf[fl_n++] = (unsigned char)v; }
static void fl16(int v) { fl8(v & 255); fl8((v >> 8) & 255); }
static void fl32(long v) { fl16((int)(v & 0xFFFF)); fl16((int)((v >> 16) & 0xFFFF)); }
static void fl_put32(int at, long v) { fl_buf[at] = v & 255; fl_buf[at + 1] = (v >> 8) & 255; fl_buf[at + 2] = (v >> 16) & 255; fl_buf[at + 3] = (v >> 24) & 255; }
static int fl_frame_start(int chunks) { int at = fl_n; fl32(0); fl16(0xF1FA); fl16(chunks); fl32(0); fl32(0); return at; }
static void fl_end(int at) { fl_put32(at, fl_n - at); }

/* an 8x4 FLC: frame 1 sets colours 1-2 and fills by BYTE_RUN, frame 2 a DELTA_FLC, then the ring frame */
static int make_flc(void)
{
    int fr, ch, y;
    memset(fl_buf, 0, sizeof(fl_buf));
    fl_n = 0;
    fl32(0); fl16(0xAF12); fl16(2); fl16(8); fl16(4); fl16(8); fl16(3); fl32(40);
    while (fl_n < 128) fl8(0);
    fl_put32(80, 128);
    fr = fl_frame_start(2);
    ch = fl_n; fl32(0); fl16(4); fl16(1); fl8(1); fl8(2); fl8(252); fl8(0); fl8(0); fl8(0); fl8(252); fl8(4); fl_end(ch);
    ch = fl_n; fl32(0); fl16(15);
    for (y = 0; y < 4; y++) { fl8(2); fl8(4); fl8(1); fl8(-4 & 255); fl8(2); fl8(2); fl8(1); fl8(2); }
    if (fl_n & 1) fl8(0);
    fl_end(ch);
    fl_end(fr);
    fl_put32(84, fl_n);
    fr = fl_frame_start(1);
    ch = fl_n; fl32(0); fl16(7); fl16(2);
    fl16(0xFFFF);                                   /* skip a line */
    fl16(1); fl8(2); fl8(1); fl8(2); fl8(2);        /* line 1: x 2-3 = colour 2 */
    fl16(0x8000 | 2);                               /* line 2: last pixel 2, */
    fl16(1); fl8(0); fl8(-2 & 255); fl8(0); fl8(0); /* x 0-3 = 0 */
    fl_end(ch);
    fl_end(fr);
    fr = fl_frame_start(1);                         /* the ring frame: black */
    ch = fl_n; fl32(6); fl16(13);
    fl_end(fr);
    fl_put32(0, fl_n);
    return fl_n;
}

/* a 4x2 FLI: COLOR_64, FLI_COPY, then DELTA_FLI and BLACK */
static int make_fli(void)
{
    int fr, ch, i;
    memset(fl_buf, 0, sizeof(fl_buf));
    fl_n = 0;
    fl32(0); fl16(0xAF11); fl16(2); fl16(4); fl16(2); fl16(8); fl16(0); fl16(7);
    while (fl_n < 128) fl8(0);
    fr = fl_frame_start(2);
    ch = fl_n; fl32(0); fl16(11); fl16(1); fl8(5); fl8(1); fl8(63); fl8(31); fl8(1); fl_end(ch);
    ch = fl_n; fl32(0); fl16(16); for (i = 0; i < 8; i++) fl8(i); fl_end(ch);
    fl_end(fr);
    fr = fl_frame_start(2);
    ch = fl_n; fl32(0); fl16(12); fl16(1); fl16(1); fl8(1); fl8(1); fl8(-2 & 255); fl8(9); fl_end(ch);
    ch = fl_n; fl32(6); fl16(18);                   /* a postage stamp: skipped */
    fl_end(fr);
    fl_put32(0, fl_n);
    return fl_n;
}

/* Open Invaders: aldumb's players over the music library; the old names,
 * bmp_read/write at every depth, load_bitmap_font, the DOS driver ids */
static void test_aldumb(void)
{
    char path[400], unixname[420];
    FILE *fp;
    DUH *duh;
    AL_DUH_PLAYER *dp;
    snprintf(path, sizeof(path), "%s/tune.mod", tmpdir);
    fp = fopen(path, "wb");
    CHECK(fp != NULL);
    if (fp) { fputs("M.K.", fp); fclose(fp); }
    dumb_register_stdfiles();
    CHECK(dumb_load_mod_quick("no-such.mod") == NULL);
    duh = dumb_load_mod_quick(path);
    CHECK(duh != NULL);
    /* no music library: the player runs, silent, and never ends */
    memset(&fmus, 0, sizeof(fmus));
    dp = al_start_duh(duh, 2, 0, 0.5f, 4096, 22050);
    CHECK(dp != NULL);
    CHECK_EQ(fmus.opens, 0);
    CHECK_EQ(al_poll_duh(dp), 0);
    al_pause_duh(dp); al_resume_duh(dp);
    al_duh_set_volume(dp, 0.25f);
    CHECK(al_duh_get_volume(dp) == 0.25f);
    al_stop_duh(dp);
    /* with it: opened, played looping at the volume, paused, ended */
    fmus.present = 1;
    dp = al_start_duh(duh, 2, 0, 0.5f, 4096, 22050);
    CHECK(dp != NULL);
    CHECK_EQ(fmus.opens, 1);
    CHECK(strcmp(fmus.name, path) == 0);
    CHECK_EQ(fmus.state, 1);
    CHECK_EQ(fmus.volume, 128);
    al_duh_set_volume(dp, 2.0f);
    CHECK_EQ(fmus.volume, 256);
    al_pause_duh(dp);
    al_pause_duh(dp);
    CHECK_EQ(fmus.pauses, 1);
    CHECK_EQ(al_poll_duh(dp), 0);
    al_resume_duh(dp);
    fmus.pos_ms = 1500;
    CHECK_EQ(al_duh_get_position(dp), 98304);
    fmus.state = 0;                 /* the library stopped it */
    CHECK(al_poll_duh(dp) != 0);
    al_stop_duh(dp);
    CHECK_EQ(fmus.closes, 1);
    unload_duh(duh);
    /* Unix names reach the music library as AmigaDOS ones */
    if (chdir(tmpdir) == 0) {
        snprintf(unixname, sizeof(unixname), "./tune.mod");
        duh = dumb_load_mod(unixname);
        CHECK(duh != NULL);
        dp = al_start_duh(duh, 2, 0, 1.0f, 4096, 22050);
        CHECK(strcmp(fmus.name, "tune.mod") == 0);
        al_stop_duh(dp);
        unload_duh(duh);
        CHECK(chdir("/") == 0);
    }
    dumb_exit();
    CHECK_EQ(fmus.exits, 1);
    memset(&fmus, 0, sizeof(fmus));
}

static void test_open_invaders_compat(void)
{
    PALLETE p;
    uint8_t px[4];
    BITMAP *b;
    FONT *f;
    char path[400];
    get_pallete(p);
    CHECK(sizeof(p) == sizeof(PALETTE));
    CHECK(DAT_PALLETE == DAT_PALETTE);
    CHECK(GFX_VGA != GFX_AUTODETECT && GFX_MODEX != GFX_VESA1);
    bmp_write16(px, 0xF81F); CHECK_EQ(bmp_read16(px), 0xF81F);
    bmp_write15(px, 0x7C1F); CHECK_EQ(bmp_read15(px), 0x7C1F);
    bmp_write32(px, 0x00FF00FF); CHECK_EQ((long)bmp_read32(px), 0x00FF00FFL);
    bmp_write24(px, 0x123456);
    CHECK(px[0] == 0x12 && px[1] == 0x34 && px[2] == 0x56);
    CHECK_EQ(bmp_read24(px), 0x123456);
    CHECK_EQ(is_windowed_mode(), 0);
    CHECK_EQ(set_gfx_mode(GFX_VGA, 320, 200, 0, 0), 0);
    /* load_bitmap_font, and load_font of a .pcx: a glyph grid */
    b = create_bitmap(8, 6);
    clear_to_color(b, 7);
    rectfill(b, 1, 1, 2, 4, 0);
    putpixel(b, 1, 1, 15);
    rectfill(b, 4, 1, 6, 4, 0);
    snprintf(path, sizeof(path), "%s/font.pcx", tmpdir);
    CHECK_EQ(save_pcx(path, b, default_palette), 0);
    destroy_bitmap(b);
    f = load_bitmap_font(path, NULL, NULL);
    CHECK(f != NULL);
    if (f) {
        CHECK_EQ(text_height(f), 4);
        CHECK_EQ(text_length(f, " !"), 2 + 3);
        make_trans_font(f);
        destroy_font(f);
    }
    f = load_font(path, NULL, NULL);
    CHECK(f != NULL);
    if (f) destroy_font(f);
    CHECK(load_bitmap_font("no-such.pcx", NULL, NULL) == NULL);
}

static void test_fli(void)
{
    int n;
    CHECK_EQ(next_fli_frame(0), FLI_NOT_OPEN);
    CHECK_EQ(open_memory_fli(fl_buf), FLI_ERROR);  /* zeros: not a FLI */

    make_flc();
    CHECK_EQ(open_memory_fli(fl_buf), FLI_OK);
    CHECK(fli_bitmap != NULL);
    CHECK_EQ(fli_bitmap->w, 8); CHECK_EQ(fli_bitmap->h, 4);
    CHECK(fli_timer > 0);
    CHECK_EQ(next_fli_frame(0), FLI_OK);
    CHECK_EQ(fli_frame, 1);
    CHECK_EQ(fli_pal_dirty_from, 1); CHECK_EQ(fli_pal_dirty_to, 2);
    CHECK_EQ(fli_palette[1].r, 63); CHECK_EQ(fli_palette[1].g, 0);
    CHECK_EQ(fli_palette[2].g, 63); CHECK_EQ(fli_palette[2].b, 1);
    CHECK_EQ(fli_bmp_dirty_from, 0); CHECK_EQ(fli_bmp_dirty_to, 3);
    CHECK_EQ(getpixel(fli_bitmap, 0, 0), 1); CHECK_EQ(getpixel(fli_bitmap, 3, 3), 1);
    CHECK_EQ(getpixel(fli_bitmap, 4, 0), 2); CHECK_EQ(getpixel(fli_bitmap, 6, 2), 1);
    reset_fli_variables();
    CHECK(fli_bmp_dirty_from > fli_bmp_dirty_to);
    CHECK_EQ(next_fli_frame(0), FLI_OK);
    CHECK_EQ(fli_frame, 2);
    CHECK_EQ(fli_bmp_dirty_from, 1); CHECK_EQ(fli_bmp_dirty_to, 2);
    CHECK(fli_pal_dirty_from > fli_pal_dirty_to);
    CHECK_EQ(getpixel(fli_bitmap, 2, 1), 2); CHECK_EQ(getpixel(fli_bitmap, 3, 1), 2);
    CHECK_EQ(getpixel(fli_bitmap, 2, 0), 1);       /* line 0 skipped */
    CHECK_EQ(getpixel(fli_bitmap, 0, 2), 0); CHECK_EQ(getpixel(fli_bitmap, 3, 2), 0);
    CHECK_EQ(getpixel(fli_bitmap, 7, 2), 2);       /* the last-pixel word */
    CHECK_EQ(next_fli_frame(0), FLI_EOF);
    CHECK_EQ(next_fli_frame(1), FLI_OK);           /* the ring frame, then back to frame 2 */
    CHECK_EQ(fli_frame, 1);
    CHECK_EQ(getpixel(fli_bitmap, 0, 0), 0);
    CHECK_EQ(next_fli_frame(1), FLI_OK);
    CHECK_EQ(fli_frame, 2);
    CHECK_EQ(getpixel(fli_bitmap, 2, 1), 2);
    close_fli();
    CHECK(fli_bitmap == NULL);

    n = make_fli();
    CHECK_EQ(open_memory_fli(fl_buf), FLI_OK);
    CHECK_EQ(next_fli_frame(0), FLI_OK);
    CHECK_EQ(fli_palette[5].r, 63); CHECK_EQ(fli_palette[5].g, 31); CHECK_EQ(fli_palette[5].b, 1);
    CHECK_EQ(getpixel(fli_bitmap, 3, 1), 7);
    CHECK_EQ(next_fli_frame(0), FLI_OK);
    CHECK_EQ(getpixel(fli_bitmap, 1, 1), 9); CHECK_EQ(getpixel(fli_bitmap, 2, 1), 9);
    CHECK_EQ(getpixel(fli_bitmap, 0, 1), 4); CHECK_EQ(getpixel(fli_bitmap, 3, 1), 7);
    CHECK_EQ(next_fli_frame(1), FLI_OK);           /* no ring frame: from the start */
    CHECK_EQ(getpixel(fli_bitmap, 1, 1), 5);
    close_fli();

    /* a file, and play_fli to the end */
    {
        FILE *o = fopen(tmp("t.fli"), "wb");
        BITMAP *b = create_bitmap(4, 2);
        CHECK(o != NULL);
        if (o) { fwrite(fl_buf, 1, n, o); fclose(o); }
        clear_bitmap(b);
        CHECK_EQ(play_fli(tmp("t.fli"), b, 0, NULL), FLI_OK);
        CHECK_EQ(getpixel(b, 2, 1), 9);
        CHECK(fli_bitmap == NULL);
        CHECK_EQ(open_fli(tmp("missing.fli")), FLI_ERROR);
        /* a truncated frame is an error, not a crash */
        fl_buf[128] = 0xFF; fl_buf[129] = 0x7F;
        CHECK_EQ(open_memory_fli(fl_buf), FLI_OK);
        CHECK_EQ(next_fli_frame(0), FLI_ERROR);
        close_fli();
        destroy_bitmap(b);
    }
}

int main(void)
{
    snprintf(tmpdir, sizeof(tmpdir), "%s/a4test-%d", getenv("TMPDIR") ? getenv("TMPDIR") : "/tmp", (int)getpid());
    {
        char cmd[400];
        snprintf(cmd, sizeof(cmd), "mkdir -p '%s'", tmpdir);
        if (system(cmd) != 0) return 2;
    }
    CHECK_EQ(allegro_init(), 0);
    test_bitmaps();
    test_blits();
    test_palette_and_fixed();
    test_screen();
    test_input();
    test_timers();
    test_files();
    test_pictures();
    test_text();
    test_sound();
    test_midi();
    test_find();
    test_gui();
    test_compat();
    test_fonts_more();
    test_config();
    test_old_palette();
    test_config_kraptor();
    test_mouse_new_mode();
    test_menus();
    test_fli();
    test_truecolour();
    test_aldumb();
    test_open_invaders_compat();
    allegro_exit();
    CHECK(!fake.open);
    {
        char cmd[400];
        snprintf(cmd, sizeof(cmd), "rm -rf '%s'", tmpdir);
        if (system(cmd) != 0) fprintf(stderr, "could not remove %s\n", tmpdir);
    }
    printf("allegro4 host tests: %d checks, %d failed\n", checks, failures);
    return failures ? 1 : 0;
}
