/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * aldumb's music on the Amiga: gfopenmusic.library, opened at the first
 * player (version 1). Without it every player is silent. Game-side.
 */
#include <exec/types.h>
#include <proto/exec.h>
#include <libraries/gfopenmusic.h>
#define GFOPENMUSIC_BASE_NAME a4_gm_base
#include <inline/gfopenmusic.h>
#include "a4_dumb_os.h"

static struct Library *a4_gm_base;
static int a4_gm_tried;

static int gm(void)
{
    if (!a4_gm_base && !a4_gm_tried) {
        a4_gm_tried = 1;
        a4_gm_base = OpenLibrary((CONST_STRPTR)GFOPENMUSICNAME, GFOPENMUSIC_VERSION);
    }
    return a4_gm_base != NULL;
}

void *a4_music_open(const char *name)
{
    return gm() ? (void *)GMOpenA((CONST_STRPTR)name, NULL) : NULL;
}

int a4_music_play(void *song, int volume)
{
    GMSetVolume((struct GMSong *)song, (ULONG)volume);
    return GMPlay((struct GMSong *)song, GM_LOOP_FOREVER, 0) ? 0 : -1;
}

void a4_music_stop(void *song) { GMStop((struct GMSong *)song); }
void a4_music_pause(void *song) { GMPause((struct GMSong *)song); }
void a4_music_resume(void *song) { GMResume((struct GMSong *)song); }
void a4_music_volume(void *song, int volume) { GMSetVolume((struct GMSong *)song, (ULONG)volume); }
void a4_music_close(void *song) { GMClose((struct GMSong *)song); }

int a4_music_state(void *song)
{
    ULONG s = GMGetAttr((struct GMSong *)song, GMA_State);
    return s == GMS_PLAYING ? A4_MUSIC_PLAYING : s == GMS_PAUSED ? A4_MUSIC_PAUSED : A4_MUSIC_STOPPED;
}

long a4_music_position_ms(void *song) { return (long)GMGetAttr((struct GMSong *)song, GMA_Position); }

void a4_music_exit(void)
{
    if (a4_gm_base) { CloseLibrary(a4_gm_base); a4_gm_base = NULL; }
    a4_gm_tried = 0;
}
