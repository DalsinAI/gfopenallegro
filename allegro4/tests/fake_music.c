/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 * The host tests' music library: records what aldumb asks of it. */
#include <string.h>
#include "a4_dumb_os.h"
#include "fake_music.h"

struct fake_music fmus;

void *a4_music_open(const char *name)
{
    if (!fmus.present) return NULL;
    strncpy(fmus.name, name, sizeof(fmus.name) - 1);
    fmus.opens++;
    return &fmus;
}
int a4_music_play(void *s, int volume) { (void)s; fmus.volume = volume; fmus.state = A4_MUSIC_PLAYING; return 0; }
void a4_music_stop(void *s) { (void)s; fmus.state = A4_MUSIC_STOPPED; }
void a4_music_pause(void *s) { (void)s; fmus.pauses++; fmus.state = A4_MUSIC_PAUSED; }
void a4_music_resume(void *s) { (void)s; fmus.state = A4_MUSIC_PLAYING; }
void a4_music_volume(void *s, int volume) { (void)s; fmus.volume = volume; }
int a4_music_state(void *s) { (void)s; return fmus.state; }
long a4_music_position_ms(void *s) { (void)s; return fmus.pos_ms; }
void a4_music_close(void *s) { (void)s; fmus.closes++; }
void a4_music_exit(void) { fmus.exits++; }
