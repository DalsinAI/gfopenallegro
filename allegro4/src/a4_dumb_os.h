/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 * What a4_dumb.c plays music with: gfopenmusic.library on the Amiga
 * (a4_dumb_gm.c), a fake in the host tests. A song of NULL is silence. */
#ifndef A4_DUMB_OS_H
#define A4_DUMB_OS_H

#define A4_MUSIC_STOPPED 0
#define A4_MUSIC_PLAYING 1
#define A4_MUSIC_PAUSED  2

void *a4_music_open(const char *name);          /* NULL: no library, or it can't read the file */
int a4_music_play(void *song, int volume);      /* volume 0-256; loops for ever; 0 on success */
void a4_music_stop(void *song);
void a4_music_pause(void *song);
void a4_music_resume(void *song);
void a4_music_volume(void *song, int volume);
int a4_music_state(void *song);                 /* A4_MUSIC_ */
long a4_music_position_ms(void *song);
void a4_music_close(void *song);
void a4_music_exit(void);                       /* closes the library */

#endif
