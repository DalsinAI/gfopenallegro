/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * The host build's system calls (the C library and POSIX), for the unit
 * tests. Time is the test's clock (a4_test_clock_us) when it is set, so
 * timer tests are exact; there is no timer task, so timers run at the
 * poll points.
 */
#include "a4_internal.h"
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

struct a4_state a4_host_state;
uint64_t a4_test_clock_us;          /* 0: the real clock */
int a4_test_clock_step_us = 1000;   /* how far a delay moves the test clock */

void *a4_malloc(size_t n) { return malloc(n ? n : 1); }
void *a4_calloc(size_t n) { return calloc(1, n ? n : 1); }
void *a4_realloc(void *p, size_t oldn, size_t n) { (void)oldn; return realloc(p, n ? n : 1); }
void a4_free(void *p) { free(p); }

struct a4_file { FILE *fp; };

a4_file *a4_os_open(const char *name, int write)
{
    FILE *fp = fopen(name, write ? "wb" : "rb");
    a4_file *f;
    if (!fp) return NULL;
    f = (a4_file *)malloc(sizeof(*f));
    if (!f) { fclose(fp); return NULL; }
    f->fp = fp;
    return f;
}
long a4_os_read(a4_file *f, void *buf, long n) { return (long)fread(buf, 1, (size_t)n, f->fp); }
long a4_os_write(a4_file *f, const void *buf, long n) { return (long)fwrite(buf, 1, (size_t)n, f->fp); }
int a4_os_close(a4_file *f) { int r = fclose(f->fp); free(f); return r; }

int a4_os_stat(const char *name, int *isdir, long *size, long *mtime)
{
    struct stat st;
    if (stat(name, &st) != 0) return 0;
    if (isdir) *isdir = S_ISDIR(st.st_mode);
    if (size) *size = (long)st.st_size;
    if (mtime) *mtime = (long)st.st_mtime;
    return 1;
}
int a4_os_delete(const char *name) { return remove(name); }

struct host_dir { DIR *d; char path[512]; };
void *a4_os_opendir(const char *dir)
{
    struct host_dir *h = (struct host_dir *)calloc(1, sizeof(*h));
    if (!h) return NULL;
    ustrzcpy(h->path, (int)sizeof(h->path), dir && *dir ? dir : ".");
    h->d = opendir(h->path);
    if (!h->d) { free(h); return NULL; }
    return h;
}
int a4_os_readdir(void *d, char *name, int size, int *isdir, long *fsize, long *mtime)
{
    struct host_dir *h = (struct host_dir *)d;
    struct dirent *e;
    while ((e = readdir(h->d)) != NULL) {
        char full[1024];
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        snprintf(full, sizeof(full), "%s/%s", h->path, e->d_name);
        ustrzcpy(name, size, e->d_name);
        *isdir = 0; *fsize = 0; *mtime = 0;
        a4_os_stat(full, isdir, fsize, mtime);
        return 1;
    }
    return 0;
}
void a4_os_closedir(void *d) { struct host_dir *h = (struct host_dir *)d; closedir(h->d); free(h); }

uint64_t a4_os_micros(void)
{
    struct timespec ts;
    if (a4_test_clock_us) return a4_test_clock_us;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000u + (uint64_t)ts.tv_nsec / 1000u;
}
void a4_os_delay_ms(unsigned ms)
{
    if (a4_test_clock_us) { a4_test_clock_us += (uint64_t)(ms ? ms : 1) * (uint64_t)a4_test_clock_step_us; return; }
    usleep(ms * 1000u);
}
int a4_os_timer_start(void) { return -1; }
void a4_os_timer_stop(void) {}
int a4_os_timer_async(void) { return 0; }
void a4_os_lock(void) {}
void a4_os_unlock(void) {}
void a4_os_message(const char *text) { fputs(text, stderr); }
void a4_os_title(const char *text) { (void)text; }
