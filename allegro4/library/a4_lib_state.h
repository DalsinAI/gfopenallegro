/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library: what an opener has besides the core's struct a4_state.
 * The core clears its own state at install_allegro; these fields come after
 * it and stay: the opener's acgame.library, its timer task and its delay
 * timer. Include after a4_internal.h.
 */
#ifndef A4_LIB_STATE_H
#define A4_LIB_STATE_H

#include <exec/types.h>
#include <exec/ports.h>
#include <exec/tasks.h>
#include <devices/timer.h>

struct a4_lib_state {
    struct a4_state core;                   /* first: a4 points at both */
    struct Library *acgame;                 /* this opener's acgame.library */
    int acgame_tried;
    struct Task *timer_task;                /* runs the timers (a4_os_amiga.c) */
    struct Task *timer_owner;               /* signalled with SIGF_SINGLE as the task ends */
    volatile int timer_quit;
    struct MsgPort *delay_port;             /* the game task's, for rest() */
    struct timerequest *delay_io;
};

#define A4L ((struct a4_lib_state *)a4_state_ptr)

/* a4_os_amiga.c */
extern const unsigned long a4_lib_state_size;
void a4_lib_cleanup(void);                  /* the opener goes: everything it left open */
extern struct Device *TimerBase;

#endif
