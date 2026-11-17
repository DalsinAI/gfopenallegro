/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT */
#ifndef FAKE_SYNTH_H
#define FAKE_SYNTH_H

/* the tests' synth: what the core asked of it, and what it answers */
struct fake_synth {
    int mode;                       /* what a4_synth_open answers (A4_SYNTH_) */
    int open, opens, closes, rate;
    int plays, stops, loop, paused, volume;
    int playing;
    unsigned long beat, ms, loops, length_ms;
    long seeks, last_seek;
    unsigned char smf[512];         /* the last song given */
    unsigned long smf_len;
    unsigned char bytes[64];        /* midi_out's */
    unsigned long nbytes;
    int level;                      /* a4_synth_render writes this in every sample */
    unsigned long rendered;
};
extern struct fake_synth fake_synth;
#endif
