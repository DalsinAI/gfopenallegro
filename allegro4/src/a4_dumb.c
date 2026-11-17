/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * dumb.h and aldumb.h: a DUH names a module file; a player hands it to the
 * music library (a4_dumb_os.h), which loops it as DUMB does. Game-side.
 */
#include <stdlib.h>
#include <string.h>
#include "aldumb.h"
#include "a4_dumb_os.h"

struct DUH { char name[512]; };

struct AL_DUH_PLAYER {
    void *song;             /* NULL: silent */
    float volume;
    int stopped;            /* al_stop_duh'd: nothing more to poll */
    int paused;
    long pos;               /* silent: where the game asked to start */
};

int dumb_resampling_quality = 2;
int dumb_it_max_to_mix = 64;

/* Unix names to AmigaDOS ones, as allegro4.library opens files:
 * "./a" -> "a", "../a" -> "/a", "a/./b" -> "a/b", "\" -> "/" */
static void a4_dumb_name(char *d, int size, const char *s)
{
    int n = 0;
    while (*s && n < size - 1) {
        int start = n == 0 || d[n - 1] == '/' || d[n - 1] == ':';
        if (start && s[0] == '.' && s[1] == '/') { s += 2; continue; }
        if (start && s[0] == '.' && s[1] == 0) { s += 1; continue; }
        if (start && s[0] == '.' && s[1] == '.' && (s[2] == '/' || s[2] == 0)) {
            d[n++] = '/';
            s += s[2] ? 3 : 2;
            continue;
        }
        if (*s == '\\') { d[n++] = '/'; s++; continue; }
        d[n++] = *s++;
    }
    d[n] = 0;
}

static int vol256(float v)
{
    if (!(v > 0.0f)) return 0;
    if (v >= 1.0f) return 256;
    return (int)(v * 256.0f + 0.5f);
}

void dumb_register_stdfiles(void) { }
void dumb_register_dat_mod(long type) { (void)type; }
void dumb_register_dat_s3m(long type) { (void)type; }
void dumb_register_dat_xm(long type) { (void)type; }
void dumb_register_dat_it(long type) { (void)type; }
void dumb_exit(void) { a4_music_exit(); }

static DUH *load(const char *filename)
{
    DUH *d;
    if (!filename || !exists(filename)) return NULL;
    d = (DUH *)calloc(1, sizeof(*d));
    if (!d) return NULL;
    a4_dumb_name(d->name, (int)sizeof(d->name), filename);
    return d;
}

DUH *dumb_load_mod(const char *filename) { return load(filename); }
DUH *dumb_load_mod_quick(const char *filename) { return load(filename); }
DUH *dumb_load_s3m(const char *filename) { return load(filename); }
DUH *dumb_load_s3m_quick(const char *filename) { return load(filename); }
DUH *dumb_load_xm(const char *filename) { return load(filename); }
DUH *dumb_load_xm_quick(const char *filename) { return load(filename); }
DUH *dumb_load_it(const char *filename) { return load(filename); }
DUH *dumb_load_it_quick(const char *filename) { return load(filename); }
void unload_duh(DUH *duh) { free(duh); }
long duh_get_length(DUH *duh) { (void)duh; return 0; }

AL_DUH_PLAYER *al_start_duh(DUH *duh, int n_channels, long pos, float volume, long bufsize, int freq)
{
    AL_DUH_PLAYER *dp;
    (void)n_channels; (void)bufsize; (void)freq;
    if (!duh) return NULL;
    dp = (AL_DUH_PLAYER *)calloc(1, sizeof(*dp));
    if (!dp) return NULL;
    dp->volume = volume;
    dp->pos = pos;
    dp->song = a4_music_open(duh->name);
    if (dp->song && a4_music_play(dp->song, vol256(volume)) != 0) {
        a4_music_close(dp->song);
        dp->song = NULL;
    }
    return dp;
}

void al_stop_duh(AL_DUH_PLAYER *dp)
{
    if (!dp) return;
    if (dp->song) { a4_music_stop(dp->song); a4_music_close(dp->song); }
    free(dp);
}

void al_pause_duh(AL_DUH_PLAYER *dp)
{
    if (!dp || dp->paused) return;
    dp->paused = 1;
    if (dp->song) a4_music_pause(dp->song);
}

void al_resume_duh(AL_DUH_PLAYER *dp)
{
    if (!dp || !dp->paused) return;
    dp->paused = 0;
    if (dp->song) a4_music_resume(dp->song);
}

void al_duh_set_priority(AL_DUH_PLAYER *dp, int priority) { (void)dp; (void)priority; }

void al_duh_set_volume(AL_DUH_PLAYER *dp, float volume)
{
    if (!dp) return;
    dp->volume = volume;
    if (dp->song) a4_music_volume(dp->song, vol256(volume));
}

float al_duh_get_volume(AL_DUH_PLAYER *dp) { return dp ? dp->volume : 0.0f; }

int al_poll_duh(AL_DUH_PLAYER *dp)
{
    if (!dp) return 1;
    if (dp->stopped) return 1;
    if (dp->song && !dp->paused && a4_music_state(dp->song) == A4_MUSIC_STOPPED) dp->stopped = 1;
    return dp->stopped;
}

long al_duh_get_position(AL_DUH_PLAYER *dp)
{
    long ms;
    if (!dp) return -1;
    if (!dp->song) return dp->pos;
    ms = a4_music_position_ms(dp->song);
    return (long)((ms / 1000) * 65536L + ((ms % 1000) * 65536L) / 1000);
}
