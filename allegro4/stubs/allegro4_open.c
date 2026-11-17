/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * How a game gets allegro4.library. The game says to acgame.library "I need
 * Allegro 4" (ACG_OpenAllegro(4), acgame.library 1.2 on), and acgame.library
 * opens the allegro4.library that goes with it. With an older acgame.library
 * the stubs open allegro4.library themselves: the copy in the game's own
 * Libs/ drawer first (PROGDIR:Libs/allegro4.library), then LIBS:.
 *
 * Both are closed as the game exits; closing allegro4.library also does
 * allegro_exit() for a game that did not.
 */
#include <exec/types.h>
#include <proto/exec.h>
#include <stdio.h>
#include <stdlib.h>

#include "allegro4_stubs.h"

#define A4_LIB_NAME "allegro4.library"
#define A4_LIB_VERSION 1
#define ACG_LIB_NAME "acgame.library"

struct Library *Allegro4Base;
static struct Library *acg_for_allegro;
static int a4_closed;

static struct Library *acg_open_allegro(struct Library *acg, long version)
{
    register long _d0 __asm("d0") = version;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = acg;
    __asm volatile ("jsr -144(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (struct Library *)_d0;
}

static struct Library *a4_open(void)
{
    struct Library *b = NULL;
    acg_for_allegro = OpenLibrary((CONST_STRPTR)"PROGDIR:Libs/" ACG_LIB_NAME, 1);
    if (!acg_for_allegro) acg_for_allegro = OpenLibrary((CONST_STRPTR)ACG_LIB_NAME, 1);
    if (acg_for_allegro && (acg_for_allegro->lib_Version > 1 || acg_for_allegro->lib_Revision >= 2))
        b = acg_open_allegro(acg_for_allegro, 4);
    if (b && b->lib_Version < A4_LIB_VERSION) { CloseLibrary(b); b = NULL; }
    if (!b) b = OpenLibrary((CONST_STRPTR)"PROGDIR:Libs/" A4_LIB_NAME, A4_LIB_VERSION);
    if (!b) b = OpenLibrary((CONST_STRPTR)A4_LIB_NAME, A4_LIB_VERSION);
    return b;
}

struct Library *a4_base(void)
{
    if (!Allegro4Base && !a4_closed) {
        Allegro4Base = a4_open();
        if (!Allegro4Base) {
            a4_closed = 1;
            fputs("This game needs " A4_LIB_NAME " " "1.0 (in its Libs/ drawer or LIBS:)\n", stderr);
            exit(20);
        }
    }
    return Allegro4Base;
}

__attribute__((destructor)) static void a4_close(void)
{
    a4_closed = 1;
    if (Allegro4Base) { CloseLibrary(Allegro4Base); Allegro4Base = NULL; }
    if (acg_for_allegro) { CloseLibrary(acg_for_allegro); acg_for_allegro = NULL; }
}
