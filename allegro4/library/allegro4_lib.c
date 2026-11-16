/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library 1.0: the Allegro 4 API for AmigaOS 3.x, drawing and
 * reading the keyboard and mouse through acgame.library. A game asks
 * acgame.library for it (ACG_OpenAllegro(4)) or opens it itself; the stubs
 * it links (liballeg.a) do either.
 *
 * Like acgame.library, every OpenLibrary gets a library base of its own,
 * with that game's state (struct a4_lib_state), so two games can run at
 * once. Each entry point puts the opener's state in a4 for the call
 * (allegro4_state.h) and gives the caller's back after. The entry points
 * and their order are made by tools/gen_lib.py from include/allegro.h
 * (allegro4_entries.h, library/calls.txt).
 *
 * Built bare by build-amiga.sh (no startup code, no C library). This file
 * goes first: its start() and RomTag lead the hunk.
 */
#include "allegro4_state.h"                 /* a4, before any function */

#include <exec/types.h>
#include <exec/resident.h>
#include <exec/libraries.h>
#include <exec/execbase.h>
#include <exec/memory.h>
#include <devices/timer.h>
#include <dos/dos.h>
#include "../include/oa_protos_begin.h"
#include <proto/exec.h>
#include "../include/oa_protos_end.h"

#include <allegro.h>

#define REG(r, decl) register decl __asm(#r)

#define A4_LIB_NAME "allegro4.library"
#define A4_LIB_VERSION 1
#define A4_LIB_REVISION 0

struct ExecBase *SysBase;
struct DosLibrary *DOSBase;
struct Device *TimerBase;

int start(void) { return -1; }      /* run as a program: nothing (stays first in the file) */

static const char lib_name[] = A4_LIB_NAME;
static const char lib_id[] = "allegro4.library 1.0 (16.11.2026) Allegro 4 on ACGame, AmiCradle Team\r\n";
static const char lib_ver[] __attribute__((used)) = "$VER: allegro4.library 1.0 (16.11.2026)";

struct a4_public;
int a4_install(struct a4_public *pub, int system_id);

/* in a4_os_amiga.c */
extern const unsigned long a4_lib_state_size;
void a4_lib_cleanup(void);

struct A4Base {
    struct Library lib;
    BPTR seglist;                   /* the master's */
    struct A4Base *master;          /* an opener's base: the master; the master: NULL */
    struct a4_state *state;         /* an opener's base: its game's state */
    struct timerequest timer;       /* the master's: TimerBase, for ReadEClock */
};

static struct Library *lib_open(REG(a6, struct A4Base *base));
static BPTR lib_close(REG(a6, struct A4Base *base));
static BPTR lib_expunge(REG(a6, struct A4Base *base));
static ULONG lib_null(void) { return 0; }

/* The opener's state in a4 for the call, and the caller's a4 back after. */
#define ENTER(b) struct a4_state *const a4_caller = a4_state_ptr; a4_state_ptr = (b)->state
#define LEAVE()  (a4_state_ptr = a4_caller)

#include "allegro4_entries.h"

static struct Library *lib_init(REG(d0, struct A4Base *base), REG(a0, BPTR seglist), REG(a6, struct ExecBase *sys));

static const struct { ULONG size; const APTR *vectors; APTR data; APTR init; } lib_inittable = {
    sizeof(struct A4Base), a4_vectors, NULL, (APTR)lib_init,
};
const struct Resident lib_romtag = {
    RTC_MATCHWORD, (struct Resident *)&lib_romtag, (APTR)(&lib_romtag + 1),
    RTF_AUTOINIT, A4_LIB_VERSION, NT_LIBRARY, 0, (char *)lib_name, (char *)lib_id, (APTR)&lib_inittable,
};

/* ---- no C library: GCC and the core call these ------------------------------ */

void *memcpy(void *to, const void *from, unsigned long n)
{
    UBYTE *d = to; const UBYTE *s = from;
    if (!(((ULONG)d | (ULONG)s) & 3)) {
        ULONG *dl = (ULONG *)d; const ULONG *sl = (const ULONG *)s;
        for (; n >= 16; n -= 16) { dl[0] = sl[0]; dl[1] = sl[1]; dl[2] = sl[2]; dl[3] = sl[3]; dl += 4; sl += 4; }
        for (; n >= 4; n -= 4) *dl++ = *sl++;
        d = (UBYTE *)dl; s = (const UBYTE *)sl;
    }
    while (n--) *d++ = *s++;
    return to;
}
void *memmove(void *to, const void *from, unsigned long n)
{
    UBYTE *d = to; const UBYTE *s = from;
    if (d <= s || d >= s + n) return memcpy(to, from, n);
    d += n; s += n;
    while (n--) *--d = *--s;
    return to;
}
void *memset(void *p, int c, unsigned long n)
{
    UBYTE *d = p;
    if (!((ULONG)d & 3)) {
        ULONG v = (UBYTE)c, *dl = (ULONG *)d;
        v |= v << 8; v |= v << 16;
        for (; n >= 16; n -= 16) { dl[0] = v; dl[1] = v; dl[2] = v; dl[3] = v; dl += 4; }
        for (; n >= 4; n -= 4) *dl++ = v;
        d = (UBYTE *)dl;
    }
    while (n--) *d++ = (UBYTE)c;
    return p;
}
int memcmp(const void *a, const void *b, unsigned long n)
{
    const UBYTE *x = a, *y = b;
    for (; n; n--, x++, y++)
        if (*x != *y) return *x < *y ? -1 : 1;
    return 0;
}
unsigned long strlen(const char *s) { const char *e = s; while (*e) e++; return (unsigned long)(e - s); }
int strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) { a++; b++; }
    return (int)(UBYTE)*a - (int)(UBYTE)*b;
}
char *strchr(const char *s, int c)
{
    for (;; s++) {
        if (*s == (char)c) return (char *)s;
        if (!*s) return NULL;
    }
}

/* ---- the library -------------------------------------------------------------- */

static VOID free_base(struct A4Base *base)
{
    FreeMem((UBYTE *)base - base->lib.lib_NegSize, base->lib.lib_NegSize + base->lib.lib_PosSize);
}

static VOID close_system(struct A4Base *base)
{
    if (TimerBase) { CloseDevice((struct IORequest *)&base->timer); TimerBase = NULL; }
    if (DOSBase) { CloseLibrary((struct Library *)DOSBase); DOSBase = NULL; }
}

static struct Library *lib_init(REG(d0, struct A4Base *base), REG(a0, BPTR seglist), REG(a6, struct ExecBase *sys))
{
    SysBase = sys;
    base->seglist = seglist;
    base->master = NULL;
    base->state = NULL;
    base->lib.lib_Revision = A4_LIB_REVISION;
    DOSBase = (struct DosLibrary *)OpenLibrary((CONST_STRPTR)"dos.library", 39);
    if (OpenDevice((CONST_STRPTR)TIMERNAME, UNIT_MICROHZ, (struct IORequest *)&base->timer, 0) == 0)
        TimerBase = base->timer.tr_node.io_Device;
    if (!DOSBase || !TimerBase) {
        close_system(base);
        free_base(base);
        return NULL;
    }
    return &base->lib;
}

/* The master hands each opener a base of its own (its own jump table and its
 * own state); exec never sees those in its list. acgame.library is opened
 * later, from the game's task, at the first call that wants it. */
static struct Library *lib_open(REG(a6, struct A4Base *base))
{
    struct A4Base *opener;
    if (base->master) return NULL;
    opener = (struct A4Base *)MakeLibrary((CONST_APTR)a4_vectors, NULL, NULL, sizeof(struct A4Base), 0);
    if (!opener) return NULL;
    opener->state = AllocVec(a4_lib_state_size, MEMF_PUBLIC | MEMF_CLEAR);
    if (!opener->state) { free_base(opener); return NULL; }
    opener->lib.lib_Node.ln_Type = NT_LIBRARY;
    opener->lib.lib_Node.ln_Name = (char *)lib_name;
    opener->lib.lib_Flags = LIBF_SUMUSED | LIBF_CHANGED;
    opener->lib.lib_Version = A4_LIB_VERSION;
    opener->lib.lib_Revision = A4_LIB_REVISION;
    opener->lib.lib_IdString = (APTR)lib_id;
    opener->lib.lib_OpenCnt = 1;
    opener->seglist = 0;
    opener->master = base;
    base->lib.lib_OpenCnt++;
    base->lib.lib_Flags &= ~LIBF_DELEXP;
    return &opener->lib;
}

static BPTR lib_close(REG(a6, struct A4Base *base))
{
    struct A4Base *master = base->master;
    if (!master) return 0;
    {
        struct a4_state *const caller = a4_state_ptr;
        a4_state_ptr = base->state;
        a4_lib_cleanup();                   /* a game that did not call allegro_exit */
        a4_state_ptr = caller;
    }
    FreeVec(base->state);
    free_base(base);
    master->lib.lib_OpenCnt--;
    if (master->lib.lib_OpenCnt == 0 && (master->lib.lib_Flags & LIBF_DELEXP))
        return lib_expunge(master);
    return 0;
}

static BPTR lib_expunge(REG(a6, struct A4Base *base))
{
    BPTR seglist;
    if (base->master) return 0;
    if (base->lib.lib_OpenCnt) { base->lib.lib_Flags |= LIBF_DELEXP; return 0; }
    seglist = base->seglist;
    Remove(&base->lib.lib_Node);
    close_system(base);
    free_base(base);
    return seglist;
}
