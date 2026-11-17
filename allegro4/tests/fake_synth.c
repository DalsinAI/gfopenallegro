/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * The tests' synth behind the core's a4_synth_* calls (the library's is
 * gfopensynth.library, library/a4_synth_amiga.c): it keeps what was asked
 * and answers what the test set.
 */
#include "a4_internal.h"
#include "fake_synth.h"

struct fake_synth fake_synth;

int a4_synth_open(unsigned rate)
{
    if (fake_synth.mode == A4_SYNTH_NONE) return A4_SYNTH_NONE;
    fake_synth.open = 1; fake_synth.opens++; fake_synth.rate = (int)rate;
    return fake_synth.mode;
}
void a4_synth_close(void) { if (fake_synth.open) { fake_synth.open = 0; fake_synth.closes++; } }
int a4_synth_play(const unsigned char *smf, unsigned long len, int loop)
{
    if (len > sizeof(fake_synth.smf)) return -1;
    memcpy(fake_synth.smf, smf, len);
    fake_synth.smf_len = len;
    fake_synth.loop = loop;
    fake_synth.plays++;
    fake_synth.playing = 1;
    fake_synth.paused = 0;
    fake_synth.beat = fake_synth.ms = fake_synth.loops = 0;
    return 0;
}
void a4_synth_stop(void) { fake_synth.stops++; fake_synth.playing = 0; }
void a4_synth_pause(int pause) { fake_synth.paused = pause; }
void a4_synth_seek(unsigned long beat) { fake_synth.seeks++; fake_synth.last_seek = (long)beat; fake_synth.beat = beat; }
void a4_synth_bytes(const unsigned char *data, unsigned long len)
{
    while (len-- && fake_synth.nbytes < sizeof(fake_synth.bytes)) fake_synth.bytes[fake_synth.nbytes++] = *data++;
}
void a4_synth_volume(int volume) { fake_synth.volume = volume; }
int a4_synth_playing(void) { return fake_synth.playing; }
unsigned long a4_synth_beat(void) { return fake_synth.beat; }
unsigned long a4_synth_ms(void) { return fake_synth.ms; }
unsigned long a4_synth_loops(void) { return fake_synth.loops; }
unsigned long a4_synth_length_ms(const unsigned char *smf, unsigned long len) { (void)smf; (void)len; return fake_synth.length_ms; }
void a4_synth_render(int16_t *buf, unsigned frames)
{
    unsigned i;
    for (i = 0; i < frames * 2; i++) buf[i] = (int16_t)fake_synth.level;
    fake_synth.rendered += frames;
}
