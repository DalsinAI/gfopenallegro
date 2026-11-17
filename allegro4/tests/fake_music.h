/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT */
#ifndef FAKE_MUSIC_H
#define FAKE_MUSIC_H
struct fake_music {
    int present, opens, closes, pauses, exits, state, volume;
    long pos_ms;
    char name[512];
};
extern struct fake_music fmus;
#endif
