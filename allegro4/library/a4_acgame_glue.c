/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library's way to the screen, keys and mouse: the core's
 * acgame_platform_* calls, each going to the opener's own acgame.library
 * (each opener of allegro4.library opens one, so each game has its own
 * screen). acgame.library is opened at the first call, from the game's
 * task: PROGDIR:Libs/ first (the copy the game ships with), then LIBS:.
 */
#include "allegro4_state.h"

#include <exec/types.h>
#include "../include/oa_protos_begin.h"
#include <proto/exec.h>
#include "../include/oa_protos_end.h"
#include <libraries/acgame.h>

#include "../src/a4_internal.h"
#include "a4_lib_state.h"

#define ACGAME_BASE_NAME (A4L->acgame)
#include <inline/acgame.h>

static int acg(void)
{
    if (!A4L->acgame && !A4L->acgame_tried) {
        A4L->acgame_tried = 1;
        A4L->acgame = OpenLibrary((CONST_STRPTR)"PROGDIR:Libs/" ACGAME_LIB_NAME, ACGAME_LIB_VERSION);
        if (!A4L->acgame) A4L->acgame = OpenLibrary((CONST_STRPTR)ACGAME_LIB_NAME, ACGAME_LIB_VERSION);
    }
    return A4L->acgame != NULL;
}

int acgame_platform_init(const acgame_video_config *config)
{
    if (!acg()) { a4_set_error("acgame.library is missing"); return -1; }
    return ACG_PlatformInit(config);
}
void acgame_platform_shutdown(void) { if (A4L->acgame) ACG_PlatformShutdown(); }
acgame_indexed_surface *acgame_platform_begin_indexed_frame(void) { return acg() ? ACG_BeginIndexedFrame() : NULL; }
int acgame_platform_present_indexed(const acgame_indexed_surface *frame) { return acg() ? ACG_PresentIndexed(frame) : -1; }
int acgame_platform_set_palette(const acgame_rgb8 palette[256]) { return acg() ? ACG_SetPalette(palette) : -1; }
int acgame_platform_display_is_planar(void) { return acg() ? ACG_DisplayIsPlanar() : 0; }
int acgame_platform_get_info(acgame_platform_info *info) { return acg() ? ACG_GetInfo(info) : -1; }
void acgame_platform_poll(acgame_input_state *state) { if (acg()) ACG_Poll(state); else memset(state, 0, sizeof(*state)); }
const uint8_t *acgame_platform_rawkeys(void) { return acg() ? ACG_RawKeys() : NULL; }
int acgame_platform_pointer(int *x, int *y)
{
    LONG lx, ly; int r;
    if (!acg()) return -1;
    r = ACG_Pointer(&lx, &ly);
    *x = lx; *y = ly;
    return r;
}
int acgame_platform_show_pointer(int show) { return acg() ? ACG_ShowPointer(show) : -1; }
uint32_t acgame_platform_ticks_ms(void) { return (uint32_t)(a4_os_micros() / 1000u); }
int acgame_platform_audio_s16stereo(const int16_t *samples, unsigned frames, unsigned sample_rate)
{
    return acg() ? ACG_AudioS16Stereo((const WORD *)samples, frames, sample_rate) : -1;
}
