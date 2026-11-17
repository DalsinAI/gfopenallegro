/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Timers. Allegro 4 calls a game's timer routines on their own, as
 * interrupts; on AmigaOS a task of the library's own (a4_os_timer_start,
 * timer.device) calls them at their times, so a game that waits in
 * `while (!ticks);` runs as on a PC. Where there is no task (the host
 * tests) they are called at the poll points instead. retrace_count counts
 * at 70 Hz, Allegro 4's simulated retrace.
 */
#include "a4_internal.h"

#define RETRACE_US (1000000u / 70u)

static uint32_t speed_to_us(long speed)
{
    uint64_t us;
    if (speed <= 0) speed = 1;
    us = (uint64_t)speed * 1000000u / (uint64_t)TIMERS_PER_SECOND;
    if (us < 100) us = 100;                 /* 10 kHz is Allegro's practical top */
    return (uint32_t)us;
}

/* call what is due; never more than a few catch-up calls in a row, so a
 * stalled machine does not run a timer hundreds of times */
void a4_timer_dispatch(void)
{
    uint64_t now;
    int i;
    if (!A4S->timer_on) return;
    now = a4_os_micros();
    for (i = 0; i < A4_MAX_TIMERS; i++) {
        struct a4_timer *t = &A4S->timers[i];
        int runs = 0;
        if (!t->period_us || (!t->proc && !t->param_proc)) continue;
        while (now >= t->due_us && runs < 8) {
            if (t->param_proc) t->param_proc(t->param);
            else t->proc();
            t->due_us += t->period_us;
            runs++;
        }
        if (now >= t->due_us) t->due_us = now + t->period_us;
    }
    while (now >= A4S->retrace_due_us) {
        retrace_count++;
        A4S->retrace_due_us += RETRACE_US;
        if (now > A4S->retrace_due_us + 1000000u) A4S->retrace_due_us = now + RETRACE_US;
    }
}

int install_timer(void)
{
    if (A4S->timer_on) return 0;
    memset(A4S->timers, 0, sizeof(A4S->timers));
    A4S->retrace_due_us = a4_os_micros() + RETRACE_US;
    A4S->timer_on = 1;
    if (a4_os_timer_start() != 0) {
        /* no task: the poll points run the timers */
    }
    return 0;
}

void remove_timer(void)
{
    if (!A4S->timer_on) return;
    a4_os_timer_stop();
    A4S->timer_on = 0;
    memset(A4S->timers, 0, sizeof(A4S->timers));
}

static int add_timer(void (*proc)(void), void (*pproc)(void *), void *param, long speed)
{
    int i, slot = -1;
    if (!A4S->timer_on) install_timer();
    a4_os_lock();
    for (i = 0; i < A4_MAX_TIMERS; i++) {
        struct a4_timer *t = &A4S->timers[i];
        if ((proc && t->proc == proc) || (pproc && t->param_proc == pproc && t->param == param)) { slot = i; break; }
    }
    if (slot < 0)
        for (i = 0; i < A4_MAX_TIMERS; i++)
            if (!A4S->timers[i].proc && !A4S->timers[i].param_proc) { slot = i; break; }
    if (slot >= 0) {
        struct a4_timer *t = &A4S->timers[slot];
        uint32_t us = speed_to_us(speed);
        int existing = t->proc || t->param_proc;
        t->proc = proc;
        t->param_proc = pproc;
        t->param = param;
        t->period_us = us;
        /* a speed change keeps the time to the next call; a new one waits a period */
        if (!existing) t->due_us = a4_os_micros() + us;
    }
    a4_os_unlock();
    return slot >= 0 ? 0 : -1;
}

int install_int_ex(void (*proc)(void), long speed) { return proc ? add_timer(proc, NULL, NULL, speed) : -1; }
int install_int(void (*proc)(void), long speed) { return install_int_ex(proc, MSEC_TO_TIMER(speed)); }
int install_param_int_ex(void (*proc)(void *), void *param, long speed) { return proc ? add_timer(NULL, proc, param, speed) : -1; }
int install_param_int(void (*proc)(void *), void *param, long speed) { return install_param_int_ex(proc, param, MSEC_TO_TIMER(speed)); }

void remove_int(void (*proc)(void))
{
    int i;
    a4_os_lock();
    for (i = 0; i < A4_MAX_TIMERS; i++)
        if (A4S->timers[i].proc == proc) memset(&A4S->timers[i], 0, sizeof(A4S->timers[i]));
    a4_os_unlock();
}

void remove_param_int(void (*proc)(void *), void *param)
{
    int i;
    a4_os_lock();
    for (i = 0; i < A4_MAX_TIMERS; i++)
        if (A4S->timers[i].param_proc == proc && A4S->timers[i].param == param) memset(&A4S->timers[i], 0, sizeof(A4S->timers[i]));
    a4_os_unlock();
}

void rest_callback(unsigned int time, void (*callback)(void))
{
    uint64_t end = a4_os_micros() + (uint64_t)time * 1000u;
    a4_poll_point();
    a4_present_if_dirty();
    if (time == 0) return;
    while (a4_os_micros() < end) {
        if (callback) callback();
        else a4_os_delay_ms(time > 5 ? 2 : 1);
        if (!a4_os_timer_async()) a4_timer_dispatch();
    }
    a4_poll_point();
}

void rest(unsigned int time) { rest_callback(time, NULL); }

int timer_can_simulate_retrace(void) { return FALSE; }
void timer_simulate_retrace(int enable) { (void)enable; }
int timer_is_using_retrace(void) { return FALSE; }
