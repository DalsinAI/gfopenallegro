/* Made by tools/gen_lib.py from include/allegro.h: do not edit.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE). */
#include "allegro4_stubs.h"

int _getpixel(BITMAP *bmp, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -30(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void _putpixel(BITMAP *bmp, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -36(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void a4_flush_screen(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -42(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int a4_install(struct a4_public * pub, int system_id)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = system_id;
    register long _d1 __asm("d1") = 0;
    register struct a4_public * _a0 __asm("a0") = pub;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -48(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void a4_mix_s16stereo(int16_t *out, int frames, int rate)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = frames;
    register int _d1 __asm("d1") = rate;
    register int16_t * _a0 __asm("a0") = out;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -54(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void acquire_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -60(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void add_clip_rect(BITMAP *bitmap, int x1, int y1, int x2, int y2)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -66(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void adjust_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = vol;
    register int _d1 __asm("d1") = pan;
    register const SAMPLE * _a0 __asm("a0") = spl;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = freq;
    register int _d3 __asm("d3") = loop;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -72(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void al_findclose(struct al_ffblk *info)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register struct al_ffblk * _a0 __asm("a0") = info;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -78(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int al_findfirst(const char *pattern, struct al_ffblk *info, int attrib)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = attrib;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = pattern;
    register struct al_ffblk * _a1 __asm("a1") = info;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -84(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int al_findnext(struct al_ffblk *info)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register struct al_ffblk * _a0 __asm("a0") = info;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -90(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int alert(const char *s1, const char *s2, const char *s3, const char *b1, const char *b2, int c1, int c2)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register const char * _d0 __asm("d0") = b2;
    register int _d1 __asm("d1") = c1;
    register const char * _a0 __asm("a0") = s1;
    register const char * _a1 __asm("a1") = s2;
    register const char * _a2 __asm("a2") = s3;
    register const char * _a3 __asm("a3") = b1;
    register int _d2 __asm("d2") = c2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -96(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_d2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int alert3(const char *s1, const char *s2, const char *s3, const char *b1, const char *b2, const char *b3, int c1, int c2, int c3)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register const char * _d0 __asm("d0") = b2;
    register const char * _d1 __asm("d1") = b3;
    register const char * _a0 __asm("a0") = s1;
    register const char * _a1 __asm("a1") = s2;
    register const char * _a2 __asm("a2") = s3;
    register const char * _a3 __asm("a3") = b1;
    register int _d2 __asm("d2") = c1;
    register int _d3 __asm("d3") = c2;
    register int _d4 __asm("d4") = c3;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -102(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void allegro_exit(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -108(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int allocate_voice(const SAMPLE *spl)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const SAMPLE * _a0 __asm("a0") = spl;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -114(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

char * append_filename(char *dest, const char *path, const char *filename, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = path;
    register const char * _a2 __asm("a2") = filename;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -120(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

void arc(BITMAP *bmp, int x, int y, fixed ang1, fixed ang2, int r, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register fixed _d2 __asm("d2") = ang1;
    register fixed _d3 __asm("d3") = ang2;
    register int _d4 __asm("d4") = r;
    register int _d5 __asm("d5") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -126(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

int bestfit_color(const PALETTE pal, int r, int g, int b)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = r;
    register int _d1 __asm("d1") = g;
    register const RGB * _a0 __asm("a0") = pal;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = b;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -132(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int bitmap_color_depth(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -138(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int bitmap_mask_color(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -144(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = source_x;
    register int _d1 __asm("d1") = source_y;
    register BITMAP * _a0 __asm("a0") = source;
    register BITMAP * _a1 __asm("a1") = dest;
    register int _d2 __asm("d2") = dest_x;
    register int _d3 __asm("d3") = dest_y;
    register int _d4 __asm("d4") = width;
    register int _d5 __asm("d5") = height;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -150(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

unsigned long bmp_read_line(BITMAP *bmp, int line)
{
    struct Library *const _b = a4_base();
    if (!_b) return (unsigned long)0;
    register int _d0 __asm("d0") = line;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -156(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (unsigned long)_d0;
}

void bmp_unwrite_line(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -162(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

unsigned long bmp_write_line(BITMAP *bmp, int line)
{
    struct Library *const _b = a4_base();
    if (!_b) return (unsigned long)0;
    register int _d0 __asm("d0") = line;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -168(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (unsigned long)_d0;
}

int calibrate_joystick(int n)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = n;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -174(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

const char * calibrate_joystick_name(int n)
{
    struct Library *const _b = a4_base();
    if (!_b) return (const char *)0;
    register int _d0 __asm("d0") = n;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -180(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (const char *)_d0;
}

char * canonicalize_filename(char *dest, const char *filename, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = filename;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -186(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

void check_cpu(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -192(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void circle(BITMAP *bmp, int x, int y, int radius, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = radius;
    register int _d3 __asm("d3") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -198(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void circlefill(BITMAP *bmp, int x, int y, int radius, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = radius;
    register int _d3 __asm("d3") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -204(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void clear_bitmap(BITMAP *bitmap)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -210(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void clear_keybuf(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -216(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void clear_to_color(BITMAP *bitmap, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = color;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -222(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

BITMAP * create_bitmap(int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register int _d0 __asm("d0") = width;
    register int _d1 __asm("d1") = height;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -228(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

BITMAP * create_bitmap_ex(int color_depth, int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register int _d0 __asm("d0") = color_depth;
    register int _d1 __asm("d1") = width;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = height;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -234(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

void create_blender_table(COLOR_MAP *table, const PALETTE pal, void (*callback)(int pos))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register COLOR_MAP * _a0 __asm("a0") = table;
    register const RGB * _a1 __asm("a1") = pal;
    register void(*_a2)(int pos) __asm("a2") = callback;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -240(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
}

void create_color_table(COLOR_MAP *table, const PALETTE pal, void (*blend)(const PALETTE pal, int x, int y, RGB *rgb), void (*callback)(int pos))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register COLOR_MAP * _a0 __asm("a0") = table;
    register const RGB * _a1 __asm("a1") = pal;
    register void(*_a2)(const PALETTE pal, int x, int y, RGB *rgb) __asm("a2") = blend;
    register void(*_a3)(int pos) __asm("a3") = callback;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -246(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_a6) : "cc", "memory");
}

DATAFILE_INDEX * create_datafile_index(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (DATAFILE_INDEX *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -252(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (DATAFILE_INDEX *)_d0;
}

void create_light_table(COLOR_MAP *table, const PALETTE pal, int r, int g, int b, void (*callback)(int pos))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = r;
    register int _d1 __asm("d1") = g;
    register COLOR_MAP * _a0 __asm("a0") = table;
    register const RGB * _a1 __asm("a1") = pal;
    register int _d2 __asm("d2") = b;
    register void(*_a2)(int pos) __asm("a2") = callback;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -258(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a2), "r"(_a6) : "cc", "memory");
}

void create_rgb_table(RGB_MAP *table, const PALETTE pal, void (*callback)(int pos))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register RGB_MAP * _a0 __asm("a0") = table;
    register const RGB * _a1 __asm("a1") = pal;
    register void(*_a2)(int pos) __asm("a2") = callback;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -264(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
}

SAMPLE * create_sample(int bits, int stereo, int freq, int len)
{
    struct Library *const _b = a4_base();
    if (!_b) return (SAMPLE *)0;
    register int _d0 __asm("d0") = bits;
    register int _d1 __asm("d1") = stereo;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = freq;
    register int _d3 __asm("d3") = len;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -270(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (SAMPLE *)_d0;
}

BITMAP * create_sub_bitmap(BITMAP *parent, int x, int y, int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = parent;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = width;
    register int _d3 __asm("d3") = height;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -276(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

BITMAP * create_system_bitmap(int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register int _d0 __asm("d0") = width;
    register int _d1 __asm("d1") = height;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -282(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

void create_trans_table(COLOR_MAP *table, const PALETTE pal, int r, int g, int b, void (*callback)(int pos))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = r;
    register int _d1 __asm("d1") = g;
    register COLOR_MAP * _a0 __asm("a0") = table;
    register const RGB * _a1 __asm("a1") = pal;
    register int _d2 __asm("d2") = b;
    register void(*_a2)(int pos) __asm("a2") = callback;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -288(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a2), "r"(_a6) : "cc", "memory");
}

BITMAP * create_video_bitmap(int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register int _d0 __asm("d0") = width;
    register int _d1 __asm("d1") = height;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -294(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

void deallocate_voice(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -300(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int delete_file(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -306(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int desktop_color_depth(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -312(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void destroy_bitmap(BITMAP *bitmap)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -318(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void destroy_datafile_index(DATAFILE_INDEX *index)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register DATAFILE_INDEX * _a0 __asm("a0") = index;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -324(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void destroy_font(FONT *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -330(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void destroy_gfx_mode_list(GFX_MODE_LIST *gfx_mode_list)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register GFX_MODE_LIST * _a0 __asm("a0") = gfx_mode_list;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -336(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void destroy_midi(MIDI *midi)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register MIDI * _a0 __asm("a0") = midi;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -342(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void destroy_rle_sprite(RLE_SPRITE *sprite)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register RLE_SPRITE * _a0 __asm("a0") = sprite;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -348(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void destroy_sample(SAMPLE *spl)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register SAMPLE * _a0 __asm("a0") = spl;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -354(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int detect_digi_driver(int driver_id)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = driver_id;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -360(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int detect_midi_driver(int driver_id)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = driver_id;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -366(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void disable_hardware_cursor(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -372(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void do_arc(BITMAP *bmp, int x, int y, fixed ang1, fixed ang2, int r, int d, void (*proc)(BITMAP *, int, int, int))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register void(*_a1)(BITMAP *, int, int, int) __asm("a1") = proc;
    register fixed _d2 __asm("d2") = ang1;
    register fixed _d3 __asm("d3") = ang2;
    register int _d4 __asm("d4") = r;
    register int _d5 __asm("d5") = d;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -378(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

void do_circle(BITMAP *bmp, int x, int y, int radius, int d, void (*proc)(BITMAP *, int, int, int))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register void(*_a1)(BITMAP *, int, int, int) __asm("a1") = proc;
    register int _d2 __asm("d2") = radius;
    register int _d3 __asm("d3") = d;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -384(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void do_ellipse(BITMAP *bmp, int x, int y, int rx, int ry, int d, void (*proc)(BITMAP *, int, int, int))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register void(*_a1)(BITMAP *, int, int, int) __asm("a1") = proc;
    register int _d2 __asm("d2") = rx;
    register int _d3 __asm("d3") = ry;
    register int _d4 __asm("d4") = d;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -390(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void do_line(BITMAP *bmp, int x1, int y1, int x2, int y2, int d, void (*proc)(BITMAP *, int, int, int))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register void(*_a1)(BITMAP *, int, int, int) __asm("a1") = proc;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register int _d4 __asm("d4") = d;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -396(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void draw_character_ex(BITMAP *bmp, BITMAP *sprite, int x, int y, int color, int bg)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = color;
    register int _d3 __asm("d3") = bg;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -402(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void draw_lit_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const RLE_SPRITE * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -408(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void draw_lit_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -414(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void draw_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const RLE_SPRITE * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -420(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void draw_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -426(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void draw_sprite_ex(BITMAP *bmp, BITMAP *sprite, int x, int y, int mode, int flip)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = mode;
    register int _d3 __asm("d3") = flip;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -432(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void draw_sprite_h_flip(BITMAP *bmp, BITMAP *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -438(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void draw_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -444(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void draw_sprite_vh_flip(BITMAP *bmp, BITMAP *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -450(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void draw_trans_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const RLE_SPRITE * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -456(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void draw_trans_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -462(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void drawing_mode(int mode, BITMAP *pattern, int x_anchor, int y_anchor)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = mode;
    register int _d1 __asm("d1") = x_anchor;
    register BITMAP * _a0 __asm("a0") = pattern;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = y_anchor;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -468(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void ellipse(BITMAP *bmp, int x, int y, int rx, int ry, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = rx;
    register int _d3 __asm("d3") = ry;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -474(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void ellipsefill(BITMAP *bmp, int x, int y, int rx, int ry, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = rx;
    register int _d3 __asm("d3") = ry;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -480(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void enable_hardware_cursor(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -486(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int enable_triple_buffer(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -492(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int exists(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -498(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void fade_from(const PALETTE source, const PALETTE dest, int speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register const RGB * _a0 __asm("a0") = source;
    register const RGB * _a1 __asm("a1") = dest;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -504(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void fade_from_range(const PALETTE source, const PALETTE dest, int speed, int from, int to)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = speed;
    register int _d1 __asm("d1") = from;
    register const RGB * _a0 __asm("a0") = source;
    register const RGB * _a1 __asm("a1") = dest;
    register int _d2 __asm("d2") = to;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -510(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void fade_in(const PALETTE p, int speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register const RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -516(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void fade_in_range(const PALETTE p, int speed, int from, int to)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = speed;
    register int _d1 __asm("d1") = from;
    register const RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = to;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -522(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void fade_interpolate(const PALETTE source, const PALETTE dest, PALETTE output, int pos, int from, int to)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = pos;
    register int _d1 __asm("d1") = from;
    register const RGB * _a0 __asm("a0") = source;
    register const RGB * _a1 __asm("a1") = dest;
    register RGB * _a2 __asm("a2") = output;
    register int _d2 __asm("d2") = to;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -528(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
}

void fade_out(int speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -534(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void fade_out_range(int speed, int from, int to)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = speed;
    register int _d1 __asm("d1") = from;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = to;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -540(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void fastline(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -546(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

int file_exists(const char *filename, int attrib, int *aret)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = attrib;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register int * _a1 __asm("a1") = aret;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -552(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long file_size(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -558(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

time_t file_time(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (time_t)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -564(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (time_t)_d0;
}

int find_allegro_resource(char *dest, const char *resource, const char *ext, const char *datafile, const char *objectname, const char *envvar, const char *subdir, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register const char * _d0 __asm("d0") = objectname;
    register const char * _d1 __asm("d1") = envvar;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = resource;
    register const char * _a2 __asm("a2") = ext;
    register const char * _a3 __asm("a3") = datafile;
    register const char * _d2 __asm("d2") = subdir;
    register int _d3 __asm("d3") = size;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -570(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

DATAFILE * find_datafile_object(const DATAFILE *dat, const char *objectname)
{
    struct Library *const _b = a4_base();
    if (!_b) return (DATAFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const DATAFILE * _a0 __asm("a0") = dat;
    register const char * _a1 __asm("a1") = objectname;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -576(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (DATAFILE *)_d0;
}

char * fix_filename_case(char *path)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = path;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -582(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * fix_filename_path(char *dest, const char *path, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = path;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -588(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * fix_filename_slashes(char *path)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = path;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -594(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

fixed fixatan(fixed x)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = x;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -600(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

fixed fixatan2(fixed y, fixed x)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = y;
    register fixed _d1 __asm("d1") = x;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -606(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

fixed fixcos(fixed x)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = x;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -612(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

fixed fixhypot(fixed x, fixed y)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = x;
    register fixed _d1 __asm("d1") = y;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -618(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

fixed fixsin(fixed x)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = x;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -624(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

fixed fixsqrt(fixed x)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = x;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -630(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

fixed fixtan(fixed x)
{
    struct Library *const _b = a4_base();
    if (!_b) return (fixed)0;
    register fixed _d0 __asm("d0") = x;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -636(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (fixed)_d0;
}

void fixup_datafile(DATAFILE *data)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register DATAFILE * _a0 __asm("a0") = data;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -642(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void floodfill(BITMAP *bmp, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -648(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void flush_config_file(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -654(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int font_has_alpha(FONT *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -660(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int for_each_file_ex(const char *name, int in_attrib, int out_attrib, int (*callback)(const char *filename, int attrib, void *param), void *param)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = in_attrib;
    register int _d1 __asm("d1") = out_attrib;
    register const char * _a0 __asm("a0") = name;
    register int(*_a1)(const char *filename, int attrib, void *param) __asm("a1") = callback;
    register void * _a2 __asm("a2") = param;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -666(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void generate_332_palette(PALETTE pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register RGB * _a0 __asm("a0") = pal;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -672(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int generate_optimized_palette(struct BITMAP *image, PALETTE pal, const signed char rsvdcols[256])
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register struct BITMAP * _a0 __asm("a0") = image;
    register RGB * _a1 __asm("a1") = pal;
    register const signed char * _a2 __asm("a2") = rsvdcols;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -678(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void get_clip_rect(BITMAP *bitmap, int *x1, int *y1, int *x2, int *y2)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int * _d0 __asm("d0") = y2;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register int * _a1 __asm("a1") = x1;
    register int * _a2 __asm("a2") = y1;
    register int * _a3 __asm("a3") = x2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -684(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_a6) : "cc", "memory");
}

int get_clip_state(BITMAP *bitmap)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -690(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void get_color(int idx, RGB *p)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = idx;
    register long _d1 __asm("d1") = 0;
    register RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -696(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int get_color_conversion(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -702(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_color_depth(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -708(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_config_int(const char *section, const char *name, int def)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = def;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = section;
    register const char * _a1 __asm("a1") = name;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -714(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

const char * get_config_string(const char *section, const char *name, const char *def)
{
    struct Library *const _b = a4_base();
    if (!_b) return (const char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = section;
    register const char * _a1 __asm("a1") = name;
    register const char * _a2 __asm("a2") = def;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -720(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (const char *)_d0;
}

const char * get_datafile_property(const DATAFILE *dat, int type)
{
    struct Library *const _b = a4_base();
    if (!_b) return (const char *)0;
    register int _d0 __asm("d0") = type;
    register long _d1 __asm("d1") = 0;
    register const DATAFILE * _a0 __asm("a0") = dat;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -726(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (const char *)_d0;
}

int get_desktop_resolution(int *width, int *height)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register int * _a0 __asm("a0") = width;
    register int * _a1 __asm("a1") = height;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -732(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_display_switch_mode(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -738(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void get_executable_name(char *output, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = output;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -744(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

char * get_extension(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -750(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * get_filename(const char *path)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = path;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -756(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

int get_font_range_begin(FONT *f, int range)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = range;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -762(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_font_range_end(FONT *f, int range)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = range;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -768(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_font_ranges(FONT *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -774(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_gfx_mode(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -780(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

GFX_MODE_LIST * get_gfx_mode_list(int card)
{
    struct Library *const _b = a4_base();
    if (!_b) return (GFX_MODE_LIST *)0;
    register int _d0 __asm("d0") = card;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -786(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (GFX_MODE_LIST *)_d0;
}

int get_gfx_mode_type(int graphics_card)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = graphics_card;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -792(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int get_midi_length(MIDI *midi)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register MIDI * _a0 __asm("a0") = midi;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -798(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void get_mouse_mickeys(int *mickeyx, int *mickeyy)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register int * _a0 __asm("a0") = mickeyx;
    register int * _a1 __asm("a1") = mickeyy;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -804(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void get_palette(PALETTE p)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -810(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void get_palette_range(PALETTE p, int from, int to)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = from;
    register int _d1 __asm("d1") = to;
    register RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -816(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int get_refresh_rate(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -822(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

RLE_SPRITE * get_rle_sprite(BITMAP *bitmap)
{
    struct Library *const _b = a4_base();
    if (!_b) return (RLE_SPRITE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -828(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (RLE_SPRITE *)_d0;
}

int get_uformat(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -834(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void get_volume(int *digi_volume, int *midi_volume)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register int * _a0 __asm("a0") = digi_volume;
    register int * _a1 __asm("a1") = midi_volume;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -840(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int geta(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -846(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getb(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -852(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getb8(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -858(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getb_depth(int color_depth, int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = color_depth;
    register int _d1 __asm("d1") = c;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -864(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getg(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -870(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getg8(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -876(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getg_depth(int color_depth, int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = color_depth;
    register int _d1 __asm("d1") = c;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -882(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getpixel(BITMAP *bmp, int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -888(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getr(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -894(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getr8(int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -900(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int getr_depth(int color_depth, int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = color_depth;
    register int _d1 __asm("d1") = c;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -906(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void hline(BITMAP *bmp, int x1, int y, int x2, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -912(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

int initialise_joystick(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -918(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_int(void (*proc)(void), long speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = proc;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -924(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_int_ex(void (*proc)(void), long speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = proc;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -930(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_joystick(int type)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = type;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -936(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_keyboard(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -942(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void install_keyboard_hooks(int (*keypressed)(void), int (*readkey)(void))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register int(*_a0)(void) __asm("a0") = keypressed;
    register int(*_a1)(void) __asm("a1") = readkey;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -948(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int install_mouse(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -954(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_param_int(void (*proc)(void *param), void *param, long speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void *param) __asm("a0") = proc;
    register void * _a1 __asm("a1") = param;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -960(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_param_int_ex(void (*proc)(void *param), void *param, long speed)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = speed;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void *param) __asm("a0") = proc;
    register void * _a1 __asm("a1") = param;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -966(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_sound(int digi, int midi, const char *cfg_path)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = digi;
    register int _d1 __asm("d1") = midi;
    register const char * _a0 __asm("a0") = cfg_path;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -972(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int install_timer(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -978(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_color_font(FONT *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -984(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_inside_bitmap(BITMAP *bmp, int x, int y, int clip)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = clip;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -990(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_linear_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -996(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_memory_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1002(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_mono_font(FONT *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1008(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_planar_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1014(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_relative_filename(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1020(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_same_bitmap(BITMAP *bmp1, BITMAP *bmp2)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp1;
    register BITMAP * _a1 __asm("a1") = bmp2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1026(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_screen_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1032(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_sub_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1038(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_system_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1044(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int is_video_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1050(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int keyboard_needs_poll(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1056(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int keypressed(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1062(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void line(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1068(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

BITMAP * load_bitmap(const char *filename, RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register RGB * _a1 __asm("a1") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1074(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

BITMAP * load_bmp(const char *filename, RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register RGB * _a1 __asm("a1") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1080(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

BITMAP * load_bmp_pf(PACKFILE *f, RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register RGB * _a1 __asm("a1") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1086(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

DATAFILE * load_datafile(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (DATAFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1092(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (DATAFILE *)_d0;
}

DATAFILE * load_datafile_callback(const char *filename, void (*callback)(DATAFILE *))
{
    struct Library *const _b = a4_base();
    if (!_b) return (DATAFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register void(*_a1)(DATAFILE *) __asm("a1") = callback;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1098(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (DATAFILE *)_d0;
}

DATAFILE * load_datafile_object(const char *filename, const char *objectname)
{
    struct Library *const _b = a4_base();
    if (!_b) return (DATAFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register const char * _a1 __asm("a1") = objectname;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1104(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (DATAFILE *)_d0;
}

DATAFILE * load_datafile_object_indexed(const DATAFILE_INDEX *index, int item)
{
    struct Library *const _b = a4_base();
    if (!_b) return (DATAFILE *)0;
    register int _d0 __asm("d0") = item;
    register long _d1 __asm("d1") = 0;
    register const DATAFILE_INDEX * _a0 __asm("a0") = index;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1110(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (DATAFILE *)_d0;
}

FONT * load_font(const char *filename, RGB *pal, void *param)
{
    struct Library *const _b = a4_base();
    if (!_b) return (FONT *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register RGB * _a1 __asm("a1") = pal;
    register void * _a2 __asm("a2") = param;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1116(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (FONT *)_d0;
}

int load_joystick_data(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1122(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

MIDI * load_midi(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (MIDI *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1128(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (MIDI *)_d0;
}

BITMAP * load_pcx(const char *filename, RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register RGB * _a1 __asm("a1") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1134(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

BITMAP * load_pcx_pf(PACKFILE *f, RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register RGB * _a1 __asm("a1") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1140(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

SAMPLE * load_sample(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (SAMPLE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1146(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (SAMPLE *)_d0;
}

BITMAP * load_tga(const char *filename, RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (BITMAP *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register RGB * _a1 __asm("a1") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1152(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
}

SAMPLE * load_voc(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (SAMPLE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1158(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (SAMPLE *)_d0;
}

SAMPLE * load_wav(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (SAMPLE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1164(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (SAMPLE *)_d0;
}

SAMPLE * load_wav_pf(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (SAMPLE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1170(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (SAMPLE *)_d0;
}

void lock_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1176(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

char * make_absolute_filename(char *dest, const char *path, const char *filename, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = path;
    register const char * _a2 __asm("a2") = filename;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1182(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * make_relative_filename(char *dest, const char *path, const char *filename, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = path;
    register const char * _a2 __asm("a2") = filename;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1188(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

int makeacol(int r, int g, int b, int a)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = r;
    register int _d1 __asm("d1") = g;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = b;
    register int _d3 __asm("d3") = a;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1194(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int makeacol_depth(int color_depth, int r, int g, int b, int a)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = color_depth;
    register int _d1 __asm("d1") = r;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = g;
    register int _d3 __asm("d3") = b;
    register int _d4 __asm("d4") = a;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1200(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int makecol(int r, int g, int b)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = r;
    register int _d1 __asm("d1") = g;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = b;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1206(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int makecol8(int r, int g, int b)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = r;
    register int _d1 __asm("d1") = g;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = b;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1212(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int makecol_depth(int color_depth, int r, int g, int b)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = color_depth;
    register int _d1 __asm("d1") = r;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = g;
    register int _d3 __asm("d3") = b;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1218(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void masked_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = source_x;
    register int _d1 __asm("d1") = source_y;
    register BITMAP * _a0 __asm("a0") = source;
    register BITMAP * _a1 __asm("a1") = dest;
    register int _d2 __asm("d2") = dest_x;
    register int _d3 __asm("d3") = dest_y;
    register int _d4 __asm("d4") = width;
    register int _d5 __asm("d5") = height;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1224(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

void masked_stretch_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = source_x;
    register int _d1 __asm("d1") = source_y;
    register BITMAP * _a0 __asm("a0") = source;
    register BITMAP * _a1 __asm("a1") = dest;
    register int _d2 __asm("d2") = source_w;
    register int _d3 __asm("d3") = source_h;
    register int _d4 __asm("d4") = dest_x;
    register int _d5 __asm("d5") = dest_y;
    register int _d6 __asm("d6") = dest_w;
    register int _d7 __asm("d7") = dest_h;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1230(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_d6), "r"(_d7), "r"(_a6) : "cc", "memory");
}

void midi_pause(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1236(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void midi_resume(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1242(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int midi_seek(int target)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = target;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1248(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int mouse_needs_poll(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1254(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void override_config_file(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1260(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int pack_fclose(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1266(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

PACKFILE * pack_fclose_chunk(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (PACKFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1272(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (PACKFILE *)_d0;
}

int pack_feof(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1278(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int pack_ferror(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1284(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

char * pack_fgets(char *p, int max, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = max;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = p;
    register PACKFILE * _a1 __asm("a1") = f;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1290(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

PACKFILE * pack_fopen(const char *filename, const char *mode)
{
    struct Library *const _b = a4_base();
    if (!_b) return (PACKFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register const char * _a1 __asm("a1") = mode;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1296(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (PACKFILE *)_d0;
}

PACKFILE * pack_fopen_chunk(PACKFILE *f, int pack)
{
    struct Library *const _b = a4_base();
    if (!_b) return (PACKFILE *)0;
    register int _d0 __asm("d0") = pack;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1302(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (PACKFILE *)_d0;
}

PACKFILE * pack_fopen_vtable(const PACKFILE_VTABLE *vtable, void *userdata)
{
    struct Library *const _b = a4_base();
    if (!_b) return (PACKFILE *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const PACKFILE_VTABLE * _a0 __asm("a0") = vtable;
    register void * _a1 __asm("a1") = userdata;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1308(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (PACKFILE *)_d0;
}

int pack_fputs(const char *p, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = p;
    register PACKFILE * _a1 __asm("a1") = f;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1314(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long pack_fread(void *p, long n, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = n;
    register long _d1 __asm("d1") = 0;
    register void * _a0 __asm("a0") = p;
    register PACKFILE * _a1 __asm("a1") = f;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1320(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

int pack_fseek(PACKFILE *f, int offset)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = offset;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1326(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long pack_fwrite(const void *p, long n, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = n;
    register long _d1 __asm("d1") = 0;
    register const void * _a0 __asm("a0") = p;
    register PACKFILE * _a1 __asm("a1") = f;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1332(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

int pack_getc(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1338(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long pack_igetl(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1344(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

int pack_igetw(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1350(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long pack_iputl(long l, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = l;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1356(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

int pack_iputw(int w, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = w;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1362(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long pack_mgetl(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1368(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

int pack_mgetw(PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1374(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

long pack_mputl(long l, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (long)0;
    register long _d0 __asm("d0") = l;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1380(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
}

int pack_mputw(int w, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = w;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1386(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int pack_putc(int c, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1392(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int pack_ungetc(int c, PACKFILE *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = c;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1398(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void packfile_password(const char *password)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = password;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1404(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void pivot_scaled_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = cx;
    register int _d3 __asm("d3") = cy;
    register fixed _d4 __asm("d4") = angle;
    register fixed _d5 __asm("d5") = scale;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1410(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

void pivot_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = cx;
    register int _d3 __asm("d3") = cy;
    register fixed _d4 __asm("d4") = angle;
    register fixed _d5 __asm("d5") = scale;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1416(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

void pivot_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = cx;
    register int _d3 __asm("d3") = cy;
    register fixed _d4 __asm("d4") = angle;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1422(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void pivot_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = cx;
    register int _d3 __asm("d3") = cy;
    register fixed _d4 __asm("d4") = angle;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1428(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

int play_looped_midi(MIDI *midi, int loop_start, int loop_end)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = loop_start;
    register int _d1 __asm("d1") = loop_end;
    register MIDI * _a0 __asm("a0") = midi;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1434(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int play_midi(MIDI *midi, int loop)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = loop;
    register long _d1 __asm("d1") = 0;
    register MIDI * _a0 __asm("a0") = midi;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1440(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int play_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = vol;
    register int _d1 __asm("d1") = pan;
    register const SAMPLE * _a0 __asm("a0") = spl;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = freq;
    register int _d3 __asm("d3") = loop;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1446(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int poll_joystick(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1452(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int poll_keyboard(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1458(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int poll_mouse(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1464(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int poll_scroll(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1470(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void polygon(BITMAP *bmp, int vertices, const int *points, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = vertices;
    register int _d1 __asm("d1") = color;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const int * _a1 __asm("a1") = points;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1476(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void position_mouse(int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1482(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void position_mouse_z(int z)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = z;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1488(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void put_backslash(char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1494(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void putpixel(BITMAP *bmp, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1500(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

int readkey(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1506(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void reallocate_voice(int voice, const SAMPLE *spl)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register const SAMPLE * _a0 __asm("a0") = spl;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1512(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1518(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1524(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void register_bitmap_file_type(const char *ext, BITMAP *(*load)(const char *filename, RGB *pal), int (*save)(const char *filename, BITMAP *bmp, const RGB *pal))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = ext;
    register BITMAP *(*_a1)(const char *filename, RGB *pal) __asm("a1") = load;
    register int(*_a2)(const char *filename, BITMAP *bmp, const RGB *pal) __asm("a2") = save;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1530(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
}

void register_datafile_object(int id, void *(*load)(PACKFILE *f, long size), void (*destroy)(void *data))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = id;
    register long _d1 __asm("d1") = 0;
    register void *(*_a0)(PACKFILE *f, long size) __asm("a0") = load;
    register void(*_a1)(void *data) __asm("a1") = destroy;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1536(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void release_bitmap(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1542(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void release_voice(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1548(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_display_switch_callback(void (*cb)(void))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = cb;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1554(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_int(void (*proc)(void))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = proc;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1560(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_joystick(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1566(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_keyboard(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1572(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_mouse(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1578(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_param_int(void (*proc)(void *param), void *param)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void *param) __asm("a0") = proc;
    register void * _a1 __asm("a1") = param;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1584(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_sound(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1590(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void remove_timer(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1596(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

char * replace_extension(char *dest, const char *filename, const char *ext, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = filename;
    register const char * _a2 __asm("a2") = ext;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1602(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * replace_filename(char *dest, const char *path, const char *filename, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = path;
    register const char * _a2 __asm("a2") = filename;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1608(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

void request_refresh_rate(int rate)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = rate;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1614(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int request_scroll(int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1620(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int request_video_bitmap(BITMAP *bitmap)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1626(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void reserve_voices(int digi_voices, int midi_voices)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = digi_voices;
    register int _d1 __asm("d1") = midi_voices;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1632(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void rest(unsigned int time)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register unsigned int _d0 __asm("d0") = time;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1638(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void rest_callback(unsigned int time, void (*callback)(void))
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register unsigned int _d0 __asm("d0") = time;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = callback;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1644(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void rotate_scaled_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register fixed _d2 __asm("d2") = angle;
    register fixed _d3 __asm("d3") = scale;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1650(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void rotate_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register fixed _d2 __asm("d2") = angle;
    register fixed _d3 __asm("d3") = scale;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1656(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void rotate_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register fixed _d2 __asm("d2") = angle;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1662(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void rotate_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register fixed _d2 __asm("d2") = angle;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1668(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

int save_bitmap(const char *filename, BITMAP *bmp, const RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register BITMAP * _a1 __asm("a1") = bmp;
    register const RGB * _a2 __asm("a2") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1674(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int save_bmp(const char *filename, BITMAP *bmp, const RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register BITMAP * _a1 __asm("a1") = bmp;
    register const RGB * _a2 __asm("a2") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1680(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int save_bmp_pf(PACKFILE *f, BITMAP *bmp, const RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register BITMAP * _a1 __asm("a1") = bmp;
    register const RGB * _a2 __asm("a2") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1686(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int save_joystick_data(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1692(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int save_pcx(const char *filename, BITMAP *bmp, const RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register BITMAP * _a1 __asm("a1") = bmp;
    register const RGB * _a2 __asm("a2") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1698(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int save_pcx_pf(PACKFILE *f, BITMAP *bmp, const RGB *pal)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register PACKFILE * _a0 __asm("a0") = f;
    register BITMAP * _a1 __asm("a1") = bmp;
    register const RGB * _a2 __asm("a2") = pal;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1704(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int save_sample(const char *filename, SAMPLE *spl)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register SAMPLE * _a1 __asm("a1") = spl;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1710(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int scancode_to_ascii(int scancode)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = scancode;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1716(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

const char * scancode_to_name(int scancode)
{
    struct Library *const _b = a4_base();
    if (!_b) return (const char *)0;
    register int _d0 __asm("d0") = scancode;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1722(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (const char *)_d0;
}

void scare_mouse(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1728(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void scare_mouse_area(int x, int y, int w, int h)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = w;
    register int _d3 __asm("d3") = h;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1734(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

int scroll_screen(int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1740(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void select_mouse_cursor(int cursor)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = cursor;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1746(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void select_palette(const PALETTE p)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1752(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_clip_rect(BITMAP *bitmap, int x1, int y1, int x2, int y2)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1758(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void set_clip_state(BITMAP *bitmap, int state)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = state;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1764(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int set_close_button_callback(void (*proc)(void))
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = proc;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1770(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void set_color(int idx, const RGB *p)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = idx;
    register long _d1 __asm("d1") = 0;
    register const RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1776(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_color_conversion(int mode)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = mode;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1782(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_color_depth(int depth)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = depth;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1788(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_config_file(const char *filename)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = filename;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1794(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_config_int(const char *section, const char *name, int val)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = val;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = section;
    register const char * _a1 __asm("a1") = name;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1800(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_config_string(const char *section, const char *name, const char *val)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = section;
    register const char * _a1 __asm("a1") = name;
    register const char * _a2 __asm("a2") = val;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1806(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
}

int set_display_switch_callback(int dir, void (*cb)(void))
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = dir;
    register long _d1 __asm("d1") = 0;
    register void(*_a0)(void) __asm("a0") = cb;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1812(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int set_display_switch_mode(int mode)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = mode;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1818(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int set_gfx_mode(int card, int w, int h, int v_w, int v_h)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = card;
    register int _d1 __asm("d1") = w;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = h;
    register int _d3 __asm("d3") = v_w;
    register int _d4 __asm("d4") = v_h;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1824(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void set_hardware_volume(int digi_volume, int midi_volume)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = digi_volume;
    register int _d1 __asm("d1") = midi_volume;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1830(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_keyboard_rate(int delay, int repeat)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = delay;
    register int _d1 __asm("d1") = repeat;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1836(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_leds(int leds)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = leds;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1842(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_mouse_range(int x1, int y1, int x2, int y2)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1848(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void set_mouse_speed(int xspeed, int yspeed)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = xspeed;
    register int _d1 __asm("d1") = yspeed;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1854(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_mouse_sprite(BITMAP *sprite)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = sprite;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1860(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_mouse_sprite_focus(int x, int y)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1866(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_palette(const PALETTE p)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1872(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_palette_range(const PALETTE p, int from, int to, int retracesync)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = from;
    register int _d1 __asm("d1") = to;
    register const RGB * _a0 __asm("a0") = p;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = retracesync;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1878(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
}

void set_uformat(int type)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = type;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1884(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_volume(int digi_volume, int midi_volume)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = digi_volume;
    register int _d1 __asm("d1") = midi_volume;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1890(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_volume_per_voice(int scale)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = scale;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1896(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void set_window_title(const char *name)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = name;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1902(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void show_mouse(BITMAP *bmp)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1908(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int show_os_cursor(int cursor)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = cursor;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1914(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int show_video_bitmap(BITMAP *bitmap)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bitmap;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1920(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void simulate_keypress(int keycode)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = keycode;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1926(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void simulate_ukeypress(int keycode, int scancode)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = keycode;
    register int _d1 __asm("d1") = scancode;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1932(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void solid_mode(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1938(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void spline(BITMAP *bmp, const int points[8], int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = color;
    register long _d1 __asm("d1") = 0;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const int * _a1 __asm("a1") = points;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1944(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void stop_midi(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1950(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void stop_sample(const SAMPLE *spl)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const SAMPLE * _a0 __asm("a0") = spl;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1956(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void stretch_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int source_width, int source_height, int dest_x, int dest_y, int dest_width, int dest_height)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = source_x;
    register int _d1 __asm("d1") = source_y;
    register BITMAP * _a0 __asm("a0") = source;
    register BITMAP * _a1 __asm("a1") = dest;
    register int _d2 __asm("d2") = source_width;
    register int _d3 __asm("d3") = source_height;
    register int _d4 __asm("d4") = dest_x;
    register int _d5 __asm("d5") = dest_y;
    register int _d6 __asm("d6") = dest_width;
    register int _d7 __asm("d7") = dest_height;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1962(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_d6), "r"(_d7), "r"(_a6) : "cc", "memory");
}

void stretch_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int w, int h)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register BITMAP * _a1 __asm("a1") = sprite;
    register int _d2 __asm("d2") = w;
    register int _d3 __asm("d3") = h;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1968(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

int text_height(const FONT *f)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const FONT * _a0 __asm("a0") = f;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1974(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int text_length(const FONT *f, const char *str)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const FONT * _a0 __asm("a0") = f;
    register const char * _a1 __asm("a1") = str;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1980(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int text_mode(int mode)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = mode;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1986(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void textout(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1992(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
}

void textout_centre(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -1998(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
}

void textout_centre_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = color;
    register int _d3 __asm("d3") = bg;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2004(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void textout_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = color;
    register int _d3 __asm("d3") = bg;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2010(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

void textout_justify(BITMAP *bmp, const FONT *f, const char *s, int x1, int x2, int y, int diff, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = x2;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = y;
    register int _d3 __asm("d3") = diff;
    register int _d4 __asm("d4") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2016(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
}

void textout_justify_ex(BITMAP *bmp, const FONT *f, const char *s, int x1, int x2, int y, int diff, int color, int bg)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = x2;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = y;
    register int _d3 __asm("d3") = diff;
    register int _d4 __asm("d4") = color;
    register int _d5 __asm("d5") = bg;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2022(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
}

void textout_right(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2028(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
}

void textout_right_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y;
    register BITMAP * _a0 __asm("a0") = bmp;
    register const FONT * _a1 __asm("a1") = f;
    register const char * _a2 __asm("a2") = s;
    register int _d2 __asm("d2") = color;
    register int _d3 __asm("d3") = bg;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2034(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

int timer_can_simulate_retrace(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2040(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int timer_is_using_retrace(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2046(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void timer_simulate_retrace(int enable)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = enable;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2052(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void triangle(BITMAP *bmp, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x1;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = x2;
    register int _d3 __asm("d3") = y2;
    register int _d4 __asm("d4") = x3;
    register int _d5 __asm("d5") = y3;
    register int _d6 __asm("d6") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2058(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_d6), "r"(_a6) : "cc", "memory");
}

const char * uconvert(const char *s, int type, char *buf, int newtype, int size)
{
    struct Library *const _b = a4_base();
    if (!_b) return (const char *)0;
    register int _d0 __asm("d0") = type;
    register int _d1 __asm("d1") = newtype;
    register const char * _a0 __asm("a0") = s;
    register char * _a1 __asm("a1") = buf;
    register int _d2 __asm("d2") = size;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2064(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
    return (const char *)_d0;
}

int uinsert(char *s, int index, int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = index;
    register int _d1 __asm("d1") = c;
    register char * _a0 __asm("a0") = s;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2070(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void unload_datafile(DATAFILE *dat)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register DATAFILE * _a0 __asm("a0") = dat;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2076(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void unload_datafile_object(DATAFILE *dat)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register DATAFILE * _a0 __asm("a0") = dat;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2082(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void unscare_mouse(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2088(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void unselect_palette(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2094(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

int ureadkey(int *scancode)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register int * _a0 __asm("a0") = scancode;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2100(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int uremove(char *s, int index)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = index;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = s;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2106(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int usetat(char *s, int index, int c)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = index;
    register int _d1 __asm("d1") = c;
    register char * _a0 __asm("a0") = s;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2112(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int ustricmp(const char *s1, const char *s2)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = s1;
    register const char * _a1 __asm("a1") = s2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2118(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

char * ustrlwr(char *s)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = s;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2124(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

int ustrnicmp(const char *s1, const char *s2, int n)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = n;
    register long _d1 __asm("d1") = 0;
    register const char * _a0 __asm("a0") = s1;
    register const char * _a1 __asm("a1") = s2;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2130(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

char * ustrtok(char *s, const char *set)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = s;
    register const char * _a1 __asm("a1") = set;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2136(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * ustrtok_r(char *s, const char *set, char **last)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = s;
    register const char * _a1 __asm("a1") = set;
    register char ** _a2 __asm("a2") = last;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2142(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * ustrupr(char *s)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = s;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2148(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * ustrzcat(char *dest, int size, const char *src)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = src;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2154(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * ustrzcpy(char *dest, int size, const char *src)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register long _d1 __asm("d1") = 0;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = src;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2160(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

char * ustrzncpy(char *dest, int size, const char *src, int n)
{
    struct Library *const _b = a4_base();
    if (!_b) return (char *)0;
    register int _d0 __asm("d0") = size;
    register int _d1 __asm("d1") = n;
    register char * _a0 __asm("a0") = dest;
    register const char * _a1 __asm("a1") = src;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2166(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
}

void vline(BITMAP *bmp, int x, int y1, int y2, int color)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = x;
    register int _d1 __asm("d1") = y1;
    register BITMAP * _a0 __asm("a0") = bmp;
    register long _a1 __asm("a1") = 0;
    register int _d2 __asm("d2") = y2;
    register int _d3 __asm("d3") = color;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2172(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
}

SAMPLE * voice_check(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return (SAMPLE *)0;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2178(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (SAMPLE *)_d0;
}

int voice_get_frequency(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2184(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int voice_get_pan(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2190(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int voice_get_position(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2196(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

int voice_get_volume(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return (int)0;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2202(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
}

void voice_set_frequency(int voice, int frequency)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register int _d1 __asm("d1") = frequency;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2208(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_set_pan(int voice, int pan)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register int _d1 __asm("d1") = pan;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2214(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_set_playmode(int voice, int playmode)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register int _d1 __asm("d1") = playmode;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2220(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_set_position(int voice, int position)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register int _d1 __asm("d1") = position;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2226(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_set_priority(int voice, int priority)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register int _d1 __asm("d1") = priority;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2232(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_set_volume(int voice, int volume)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register int _d1 __asm("d1") = volume;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2238(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_start(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2244(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void voice_stop(int voice)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = voice;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2250(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void vsync(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2256(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void xor_mode(int on)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register int _d0 __asm("d0") = on;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2262(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void yield_timeslice(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2268(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void pop_config_state(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2274(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}

void push_config_state(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -2280(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}
