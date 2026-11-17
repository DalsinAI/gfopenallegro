/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * acgame.library's calls for the host tests: a screen that keeps every
 * presented frame, keys and a pointer the test sets, the test's clock,
 * and an audio sink.
 */
#include "fake_acgame.h"
#include <stdint.h>
#include <string.h>

extern uint64_t a4_os_micros(void);

struct fake_acgame fake;

int acgame_platform_init(const acgame_video_config *c)
{
    if (fake.fail_init || !c || (c->width & 7u)) return -1;
    memset(&fake.frame, 0, sizeof(fake.frame));
    fake.cfg = *c;
    fake.open = 1;
    fake.frame.width = (uint16_t)c->width;
    fake.frame.height = (uint16_t)c->height;
    fake.frame.pitch = c->width;
    fake.frame.pixels = fake.pixels;
    return 0;
}
void acgame_platform_shutdown(void) { fake.open = 0; }
acgame_indexed_surface *acgame_platform_begin_indexed_frame(void) { return fake.open ? &fake.frame : NULL; }
int acgame_platform_present_indexed(const acgame_indexed_surface *f)
{
    if (!fake.open || !f) return -1;
    fake.presents++;
    memcpy(fake.shown, f->pixels, (size_t)f->pitch * f->height);
    memcpy(fake.shown_pal, f->palette, sizeof(fake.shown_pal));
    return 0;
}
int acgame_platform_set_palette(const acgame_rgb8 p[256]) { fake.palette_sets++; memcpy(fake.shown_pal, p, sizeof(fake.shown_pal)); return fake.open ? 0 : -1; }
int acgame_platform_display_is_planar(void) { return fake.open ? 1 : -1; }
int acgame_platform_get_info(acgame_platform_info *i)
{
    if (!fake.open) return -1;
    memset(i, 0, sizeof(*i));
    i->planar = 1;
    i->screen_width = fake.cfg.width;
    i->screen_height = fake.cfg.height;
    return 0;
}
int acgame_platform_present_ham8(const uint8_t *h, size_t p, const acgame_rgb8 b[64]) { (void)h; (void)p; (void)b; return -1; }
void acgame_platform_poll(acgame_input_state *s)
{
    memset(s, 0, sizeof(*s));
    s->mouse_buttons = fake.buttons;
    s->mouse_dx = (int16_t)fake.dx;
    s->mouse_dy = (int16_t)fake.dy;
    memcpy(s->key, fake.keys, sizeof(s->key));
    s->pad.buttons = fake.pad_buttons;
    fake.dx = fake.dy = 0;
    fake.polls++;
}
const uint8_t *acgame_platform_rawkeys(void) { return fake.raw; }
int acgame_platform_pointer(int *x, int *y) { if (!fake.open) return -1; *x = fake.px; *y = fake.py; return 0; }
int acgame_platform_show_pointer(int show) { fake.pointer_shown = show; return fake.open ? 0 : -1; }
uint32_t acgame_platform_ticks_ms(void) { return (uint32_t)(a4_os_micros() / 1000u); }
int acgame_platform_audio_s16stereo(const int16_t *s, unsigned frames, unsigned rate)
{
    (void)rate;
    if (!fake.audio_ok) return -1;
    fake.audio_frames += frames;
    if (frames) fake.audio_last = s[0];
    return 0;
}
