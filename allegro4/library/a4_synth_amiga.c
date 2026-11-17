/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library's MIDI: the core's a4_synth_* calls, each going to the
 * opener's own gfopensynth.library synth (GFOpenSynth: General MIDI and
 * MT-32 music). The library is opened when a game installs sound with
 * MIDI: PROGDIR:Libs/ first, then LIBS:. Two ways to sound:
 *   A4_SYNTH_PORT  AkikoPlus's MIDI port: the synth in the machine plays,
 *                  as a real one plugged into the port would
 *   A4_SYNTH_MIX   no port: the synth runs here from a SoundFont and the
 *                  core mixes it with the samples, out through
 *                  acgame.library (AHI, or Paula)
 * With no gfopensynth.library, or no port and no SoundFont, music is
 * silent as it was and the game runs on.
 */
#include "allegro4_state.h"

#include <exec/types.h>
#include <utility/tagitem.h>
#include "../include/oa_protos_begin.h"
#include <proto/exec.h>
#include "../include/oa_protos_end.h"
#include <libraries/gfopensynth.h>

#include "../src/a4_internal.h"
#include "a4_lib_state.h"

#define GFOPENSYNTH_BASE_NAME (A4L->synth_lib)
#include <inline/gfopensynth.h>

#define SYN ((struct GSSynth *)A4L->synth)

int a4_synth_open(unsigned rate)
{
    struct TagItem tags[3];
    if (A4L->synth) return A4L->synth_mode;
    if (!A4L->synth_lib) {
        A4L->synth_lib = OpenLibrary((CONST_STRPTR)"PROGDIR:Libs/" GFOPENSYNTHNAME, GFOPENSYNTH_VERSION);
        if (!A4L->synth_lib) A4L->synth_lib = OpenLibrary((CONST_STRPTR)GFOPENSYNTHNAME, GFOPENSYNTH_VERSION);
        if (!A4L->synth_lib) return A4_SYNTH_NONE;
    }
    tags[0].ti_Tag = GSA_Output; tags[0].ti_Data = GSOUT_PORT;
    tags[1].ti_Tag = GSA_Rate;   tags[1].ti_Data = rate;
    tags[2].ti_Tag = TAG_DONE;   tags[2].ti_Data = 0;
    A4L->synth_mode = A4_SYNTH_PORT;
    if (!(A4L->synth = GSOpenSynthA(tags))) {
        tags[0].ti_Data = GSOUT_CALLER;
        A4L->synth_mode = A4_SYNTH_MIX;
        if (!(A4L->synth = GSOpenSynthA(tags))) A4L->synth_mode = A4_SYNTH_NONE;
    }
    return A4L->synth_mode;
}

void a4_synth_close(void)
{
    if (A4L->synth) { GSCloseSynth(SYN); A4L->synth = NULL; }
    A4L->synth_mode = A4_SYNTH_NONE;
    if (A4L->synth_lib) { CloseLibrary(A4L->synth_lib); A4L->synth_lib = NULL; }
}

int a4_synth_play(const unsigned char *smf, unsigned long len, int loop)
{
    struct TagItem tags[2];
    if (!A4L->synth) return -1;
    tags[0].ti_Tag = GSA_Loop; tags[0].ti_Data = (ULONG)(loop != 0);
    tags[1].ti_Tag = TAG_DONE; tags[1].ti_Data = 0;
    return GSPlayMemA(SYN, smf, len, tags) ? 0 : -1;
}

void a4_synth_stop(void) { if (A4L->synth) GSStopFile(SYN); }
void a4_synth_pause(int pause) { if (A4L->synth) GSPauseFile(SYN, (ULONG)(pause != 0)); }
void a4_synth_seek(unsigned long beat) { if (A4L->synth) GSSeekFile(SYN, beat); }
void a4_synth_bytes(const unsigned char *data, unsigned long len) { if (A4L->synth) GSWriteBytes(SYN, data, len); }
void a4_synth_volume(int v) { if (A4L->synth) GSSetVolume(SYN, (ULONG)(v >= 255 ? GS_VOLUME_FULL : v < 0 ? 0 : v)); }
int a4_synth_playing(void) { return A4L->synth ? (int)GSGetAttr(SYN, GSA_Playing) : 0; }
unsigned long a4_synth_beat(void) { return A4L->synth ? GSGetAttr(SYN, GSA_Beat) : 0; }
unsigned long a4_synth_ms(void) { return A4L->synth ? GSGetAttr(SYN, GSA_Position) : 0; }
unsigned long a4_synth_loops(void) { return A4L->synth ? GSGetAttr(SYN, GSA_Loops) : 0; }
unsigned long a4_synth_length_ms(const unsigned char *smf, unsigned long len)
{
    return A4L->synth_lib ? GSMemLength(smf, len) : 0;
}
void a4_synth_render(int16_t *buf, unsigned frames)
{
    if (!A4L->synth || GSRenderS16(SYN, (WORD *)buf, frames) != frames) memset(buf, 0, (size_t)frames * 4);
}
