/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * A4LibSmoke: allegro4.library on the Amiga, linked as a game links
 * (liballeg.a). Opens a 320x200 screen, draws, blits a sprite, counts a
 * 100 Hz timer for a second, and prints what it saw. Esc or 5 s ends it.
 * Prints PASS when the timer ran 80-120 times in that second.
 *   A4LibSmoke [RTG]
 */
#include <allegro.h>
#include <stdio.h>
#include <string.h>

static volatile int ticks;
static void tick(void) { ticks++; }

int main(int argc, char **argv)
{
    BITMAP *spr, *buf;
    int i, t0, t1, frames = 0;
    if (allegro_init() != 0) { printf("allegro_init failed\n"); return 20; }
    install_keyboard();
    install_timer();
    if (install_int_ex(tick, BPS_TO_TIMER(100)) != 0) { printf("install_int_ex failed\n"); return 20; }
    if (set_gfx_mode(argc > 1 && !strcmp(argv[1], "RTG") ? GFX_ACGAME_RTG : GFX_AUTODETECT, 320, 200, 0, 0) != 0) {
        printf("set_gfx_mode: %s\n", allegro_error);
        return 20;
    }
    buf = create_bitmap(SCREEN_W, SCREEN_H);
    spr = create_bitmap(32, 32);
    clear_to_color(spr, 0);
    circlefill(spr, 16, 16, 14, 44);
    t0 = ticks;
    rest(1000);
    t1 = ticks;
    for (i = 0; i < 250 && !key[KEY_ESC]; i++) {
        clear_to_color(buf, 1);
        rectfill(buf, 10, 10, 310, 30, 15);
        textprintf_ex(buf, font, 14, 16, 0, -1, "allegro4.library %d ticks/s", t1 - t0);
        draw_sprite(buf, spr, i % 288, 80);
        draw_sprite_h_flip(buf, spr, 288 - i % 288, 120);
        blit(buf, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        vsync();
        frames++;
    }
    destroy_bitmap(spr);
    destroy_bitmap(buf);
    allegro_exit();
    printf("A4LibSmoke: timer %d/s, %d frames, %s\n", t1 - t0, frames,
           t1 - t0 >= 80 && t1 - t0 <= 120 ? "PASS" : "FAIL");
    return t1 - t0 >= 80 && t1 - t0 <= 120 ? 0 : 5;
}
