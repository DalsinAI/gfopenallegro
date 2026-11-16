/* Made by tools/gen_lib.py from include/allegro.h: do not edit.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE). */
#include "allegro4_stubs.h"

void a4_flush_screen(void)
{
    struct Library *const _b = a4_base();
    if (!_b) return;
    register long _d0 __asm("d0") = 0;
    register long _d1 __asm("d1") = 0;
    register long _a0 __asm("a0") = 0;
    register long _a1 __asm("a1") = 0;
    register struct Library *_a6 __asm("a6") = _b;
    __asm volatile ("jsr -30(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -36(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -42(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -48(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -54(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -60(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -66(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -72(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -78(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -84(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -90(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -96(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (unsigned long)_d0;
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
    __asm volatile ("jsr -102(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -108(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
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
    __asm volatile ("jsr -114(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -120(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -126(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -132(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (BITMAP *)_d0;
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
    __asm volatile ("jsr -138(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -144(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -150(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -156(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -162(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -168(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -174(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -180(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -186(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -192(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -198(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -204(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -210(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -216(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -222(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -228(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -234(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -240(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -246(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -252(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -258(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -264(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -270(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -276(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -282(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -288(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -294(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -300(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -306(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -312(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
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
    __asm volatile ("jsr -318(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -324(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -330(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -336(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -342(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -348(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -354(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -360(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -366(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -372(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -378(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -384(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -390(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (char *)_d0;
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
    __asm volatile ("jsr -396(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -402(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -408(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -414(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -420(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -426(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -432(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -438(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (RLE_SPRITE *)_d0;
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
    __asm volatile ("jsr -444(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -450(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -456(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -462(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -468(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -474(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -480(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -486(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -492(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -498(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -504(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -510(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -516(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -522(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -528(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -534(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -540(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -546(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -552(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -558(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -564(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -570(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -576(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (MIDI *)_d0;
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
    __asm volatile ("jsr -582(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -588(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -594(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -600(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -606(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -612(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -618(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -624(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -630(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_d6), "r"(_d7), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -636(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -642(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -648(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -654(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -660(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -666(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -672(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -678(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -684(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -690(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -696(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
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
    __asm volatile ("jsr -702(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
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
    __asm volatile ("jsr -708(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
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
    __asm volatile ("jsr -714(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (long)_d0;
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
    __asm volatile ("jsr -720(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -726(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_d5), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -732(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -738(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -744(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -750(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -756(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -762(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -768(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -774(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -780(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -786(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -792(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -798(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -804(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -810(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -816(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -822(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
    return (char *)_d0;
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
    __asm volatile ("jsr -828(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -834(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -840(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -846(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -852(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -858(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -864(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -870(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -876(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -882(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (const char *)_d0;
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
    __asm volatile ("jsr -888(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -894(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -900(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -906(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -912(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -918(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -924(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -930(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -936(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_d4), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -942(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -948(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -954(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -960(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -966(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -972(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -978(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -984(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -990(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -996(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1002(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1008(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1014(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1020(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1026(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1032(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1038(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1044(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1050(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1056(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1062(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1068(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1074(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -1080(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a2), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1086(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1092(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1098(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1104(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_d2), "r"(_d3), "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1110(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1116(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1122(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1128(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1134(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
    return (int)_d0;
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
    __asm volatile ("jsr -1140(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1146(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
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
    __asm volatile ("jsr -1152(%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_a6) : "cc", "memory");
}
