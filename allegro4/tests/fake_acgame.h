/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT */
#ifndef FAKE_ACGAME_H
#define FAKE_ACGAME_H
#include "acgame/platform.h"

struct fake_acgame {
    int open, fail_init, presents, palette_sets, polls, pointer_shown, audio_ok;
    acgame_video_config cfg;
    acgame_indexed_surface frame;
    uint8_t pixels[1024 * 768];
    uint8_t shown[1024 * 768];
    acgame_rgb8 shown_pal[256];
    uint8_t raw[128];
    uint8_t keys[ACGAME_KEY_COUNT];
    int px, py, dx, dy;
    uint8_t buttons;
    uint32_t pad_buttons;
    unsigned long audio_frames;
    int audio_last;
};
extern struct fake_acgame fake;
#endif
