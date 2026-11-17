/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library's system calls (a4_os_*) on AmigaOS 3.x: memory from
 * exec, files through dos.library, time from timer.device's E-clock, and
 * the timer task that calls the game's timer routines on their own, as
 * Allegro 4 does on a PC.
 *
 * Allegro games name files the Unix way ("./data/x.dat", "../save"); the
 * names are turned into AmigaDOS ones ("data/x.dat", "/save") here.
 */
#include "allegro4_state.h"

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/execbase.h>
#include <devices/timer.h>
#include <dos/dos.h>
#include <dos/dostags.h>
#include "../include/oa_protos_begin.h"
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/timer.h>
#include "../include/oa_protos_end.h"

#include "../src/a4_internal.h"
#include "a4_lib_state.h"

const unsigned long a4_lib_state_size = sizeof(struct a4_lib_state);

/* ---- memory ------------------------------------------------------------------- */

void *a4_malloc(size_t n) { return AllocVec(n ? n : 1, MEMF_ANY); }
void *a4_calloc(size_t n) { return AllocVec(n ? n : 1, MEMF_ANY | MEMF_CLEAR); }
void *a4_realloc(void *p, size_t oldn, size_t n)
{
    void *q = AllocVec(n ? n : 1, MEMF_ANY);
    if (!q) return NULL;
    if (p) { memcpy(q, p, oldn < n ? oldn : n); FreeVec(p); }
    return q;
}
void a4_free(void *p) { if (p) FreeVec(p); }

/* ---- names ------------------------------------------------------------------ */

/* "./a" -> "a", "../a" -> "/a", "a/./b" -> "a/b", "a/../b" -> "a//b" */
static void amiga_name(char *d, int size, const char *s)
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

/* ---- files ------------------------------------------------------------------ */

struct a4_file { BPTR fh; };

a4_file *a4_os_open(const char *name, int write)
{
    char path[512];
    a4_file *f;
    BPTR fh;
    amiga_name(path, sizeof(path), name);
    fh = Open((CONST_STRPTR)path, write ? MODE_NEWFILE : MODE_OLDFILE);
    if (!fh) return NULL;
    f = (a4_file *)a4_malloc(sizeof(*f));
    if (!f) { Close(fh); return NULL; }
    f->fh = fh;
    return f;
}
long a4_os_read(a4_file *f, void *buf, long n) { return Read(f->fh, buf, n); }
long a4_os_write(a4_file *f, const void *buf, long n) { return Write(f->fh, (APTR)buf, n); }
int a4_os_close(a4_file *f) { int ok = Close(f->fh); a4_free(f); return ok ? 0 : -1; }

/* AmigaDOS counts from 1 Jan 1978, Unix from 1 Jan 1970 */
#define AMIGA_EPOCH 252460800L

static long ds_to_unix(const struct DateStamp *ds)
{
    return AMIGA_EPOCH + ds->ds_Days * 86400L + ds->ds_Minute * 60L + ds->ds_Tick / TICKS_PER_SECOND;
}

int a4_os_stat(const char *name, int *isdir, long *size, long *mtime)
{
    char path[512];
    struct FileInfoBlock *fib;
    BPTR lock;
    int ok = 0;
    amiga_name(path, sizeof(path), name);
    lock = Lock((CONST_STRPTR)path, SHARED_LOCK);
    if (!lock) return 0;
    fib = (struct FileInfoBlock *)AllocDosObject(DOS_FIB, NULL);
    if (fib && Examine(lock, fib)) {
        ok = 1;
        if (isdir) *isdir = fib->fib_DirEntryType > 0;
        if (size) *size = fib->fib_Size;
        if (mtime) *mtime = ds_to_unix(&fib->fib_Date);
    }
    if (fib) FreeDosObject(DOS_FIB, fib);
    UnLock(lock);
    return ok;
}

int a4_os_delete(const char *name)
{
    char path[512];
    amiga_name(path, sizeof(path), name);
    return DeleteFile((CONST_STRPTR)path) ? 0 : -1;
}

struct amiga_dir { BPTR lock; struct FileInfoBlock *fib; };

void *a4_os_opendir(const char *dir)
{
    char path[512];
    struct amiga_dir *d = (struct amiga_dir *)a4_calloc(sizeof(*d));
    if (!d) return NULL;
    amiga_name(path, sizeof(path), dir);
    d->lock = Lock((CONST_STRPTR)path, SHARED_LOCK);
    d->fib = (struct FileInfoBlock *)AllocDosObject(DOS_FIB, NULL);
    if (!d->lock || !d->fib || !Examine(d->lock, d->fib) || d->fib->fib_DirEntryType <= 0) {
        a4_os_closedir(d);
        return NULL;
    }
    return d;
}

int a4_os_readdir(void *dp, char *name, int size, int *isdir, long *fsize, long *mtime)
{
    struct amiga_dir *d = (struct amiga_dir *)dp;
    int i;
    if (!ExNext(d->lock, d->fib)) return 0;
    for (i = 0; i < size - 1 && d->fib->fib_FileName[i]; i++) name[i] = d->fib->fib_FileName[i];
    name[i] = 0;
    if (isdir) *isdir = d->fib->fib_DirEntryType > 0;
    if (fsize) *fsize = d->fib->fib_Size;
    if (mtime) *mtime = ds_to_unix(&d->fib->fib_Date);
    return 1;
}

void a4_os_closedir(void *dp)
{
    struct amiga_dir *d = (struct amiga_dir *)dp;
    if (!d) return;
    if (d->fib) FreeDosObject(DOS_FIB, d->fib);
    if (d->lock) UnLock(d->lock);
    a4_free(d);
}

/* ---- time --------------------------------------------------------------------- */

uint64_t a4_os_micros(void)
{
    struct EClockVal ev;
    ULONG freq = ReadEClock(&ev);
    uint64_t t = ((uint64_t)ev.ev_hi << 32) | ev.ev_lo;
    return t / freq * 1000000u + (t % freq) * 1000000u / freq;
}

/* a timer.device wait from the calling (game) task; Delay() only has 20 ms steps */
void a4_os_delay_ms(unsigned ms)
{
    struct a4_lib_state *l = A4L;
    if (!l->delay_port) {
        l->delay_port = CreateMsgPort();
        if (l->delay_port) {
            l->delay_io = (struct timerequest *)CreateIORequest(l->delay_port, sizeof(struct timerequest));
            if (l->delay_io && OpenDevice((CONST_STRPTR)TIMERNAME, UNIT_MICROHZ, (struct IORequest *)l->delay_io, 0) != 0) {
                DeleteIORequest((struct IORequest *)l->delay_io);
                l->delay_io = NULL;
            }
        }
    }
    if (!l->delay_io) { Delay(ms / 20 + 1); return; }
    l->delay_io->tr_node.io_Command = TR_ADDREQUEST;
    l->delay_io->tr_time.tv_secs = ms / 1000;
    l->delay_io->tr_time.tv_micro = (ms % 1000) * 1000;
    DoIO((struct IORequest *)l->delay_io);
}

/* ---- the timer task --------------------------------------------------------- */

/* The task's a4 is the opener's state (given in tc_UserData before it ran),
 * so the core's code runs in it as in the game's task. It calls what is due,
 * then sleeps on timer.device until the next time, never more than 5 ms, so
 * a timer added meanwhile starts on time. */
static void timer_task_main(void)
{
    struct Task *me = FindTask(NULL);
    struct MsgPort *port;
    struct timerequest *io = NULL;
    a4_state_ptr = (struct a4_state *)me->tc_UserData;
    port = CreateMsgPort();
    if (port) io = (struct timerequest *)CreateIORequest(port, sizeof(struct timerequest));
    if (io && OpenDevice((CONST_STRPTR)TIMERNAME, UNIT_MICROHZ, (struct IORequest *)io, 0) != 0) {
        DeleteIORequest((struct IORequest *)io);
        io = NULL;
    }
    while (io && !A4L->timer_quit) {
        uint64_t now, next;
        uint32_t wait;
        int i;
        a4_timer_dispatch();
        now = a4_os_micros();
        next = now + 5000;
        for (i = 0; i < A4_MAX_TIMERS; i++) {
            struct a4_timer *t = &A4S->timers[i];
            if (t->period_us && (t->proc || t->param_proc) && t->due_us < next) next = t->due_us;
        }
        if (A4S->retrace_due_us < next) next = A4S->retrace_due_us;
        wait = next > now ? (uint32_t)(next - now) : 50;
        if (wait < 50) wait = 50;
        io->tr_node.io_Command = TR_ADDREQUEST;
        io->tr_time.tv_secs = 0;
        io->tr_time.tv_micro = wait;
        SendIO((struct IORequest *)io);
        if (Wait((1UL << port->mp_SigBit) | SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C) {
            if (!CheckIO((struct IORequest *)io)) AbortIO((struct IORequest *)io);
        }
        WaitIO((struct IORequest *)io);
    }
    if (io) { CloseDevice((struct IORequest *)io); DeleteIORequest((struct IORequest *)io); }
    if (port) DeleteMsgPort(port);
    Forbid();                               /* the owner frees nothing of ours before we are gone */
    A4L->timer_task = NULL;
    Signal(A4L->timer_owner, SIGF_SINGLE);
}

int a4_os_timer_start(void)
{
    struct Process *p;
    if (A4L->timer_task) return 0;
    A4L->timer_quit = 0;
    A4L->timer_owner = FindTask(NULL);
    Forbid();                               /* tc_UserData set before it runs */
    p = CreateNewProcTags(NP_Entry, (ULONG)timer_task_main, NP_Name, (ULONG)"allegro4 timers",
                          NP_Priority, 2, NP_StackSize, 16384, TAG_DONE);
    if (p) {
        p->pr_Task.tc_UserData = a4_state_ptr;
        A4L->timer_task = &p->pr_Task;
    }
    Permit();
    return p ? 0 : -1;
}

void a4_os_timer_stop(void)
{
    struct Task *t;
    Forbid();
    t = A4L->timer_task;
    if (t) {
        A4L->timer_owner = FindTask(NULL);
        SetSignal(0, SIGF_SINGLE);
        A4L->timer_quit = 1;
        Signal(t, SIGBREAKF_CTRL_C);
        while (A4L->timer_task) Wait(SIGF_SINGLE);
    }
    Permit();
}

int a4_os_timer_async(void) { return A4L->timer_task != NULL; }
void a4_os_lock(void) { Forbid(); }
void a4_os_unlock(void) { Permit(); }

void a4_os_message(const char *text)
{
    BPTR out = Output();
    if (out) Write(out, (APTR)text, strlen(text));
}
void a4_os_title(const char *text) { (void)text; }

/* ---- the opener goes ---------------------------------------------------------- */

void a4_lib_cleanup(void)
{
    allegro_exit();
    a4_os_timer_stop();
    if (A4L->delay_io) {
        CloseDevice((struct IORequest *)A4L->delay_io);
        DeleteIORequest((struct IORequest *)A4L->delay_io);
        A4L->delay_io = NULL;
    }
    if (A4L->delay_port) { DeleteMsgPort(A4L->delay_port); A4L->delay_port = NULL; }
    if (A4L->acgame) { CloseLibrary(A4L->acgame); A4L->acgame = NULL; }
}
