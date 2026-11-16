/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * The game's side of Allegro 4: the public variables (key[], screen,
 * mouse_x...), the palettes, install_allegro, and the calls that take a
 * format string (they format here, with the game's C library, and draw
 * through textout). This file is part of the stubs a game links
 * (liballeg.a); install_allegro hands the variables' addresses to
 * allegro4.library. The host build links it with the core directly.
 */
#include "a4_internal.h"
#include <stdio.h>

int a4_install(struct a4_public *pub, int system_id);

char allegro_error[ALLEGRO_ERROR_SIZE];
static int a4_errno_store;
int *allegro_errno = &a4_errno_store;
int os_type = OSTYPE_AMIGA, os_version = 3, os_revision = 2, os_multitasking = TRUE;
int cpu_family = 4, cpu_model = 0, cpu_capabilities = 0;
char cpu_vendor[32] = "Motorola";
BITMAP *screen;
int _a4_screen_w, _a4_screen_h;
FONT *font;
int allegro_404_char = '^';
volatile char key[KEY_MAX];
volatile int key_shifts;
int three_finger_flag = TRUE, key_led_flag = TRUE;
int (*keyboard_callback)(int key);
int (*keyboard_ucallback)(int key, int *scancode);
void (*keyboard_lowlevel_callback)(int scancode);
volatile int mouse_x, mouse_y, mouse_z, mouse_w, mouse_b, mouse_pos;
BITMAP *mouse_sprite;
int mouse_x_focus, mouse_y_focus;
int freeze_mouse_flag;
void (*mouse_callback)(int flags);
JOYSTICK_INFO joy[MAX_JOYSTICKS];
int num_joysticks;
volatile int retrace_count;
void (*retrace_proc)(void);
RGB_MAP *rgb_map;
COLOR_MAP *color_map;
int _color_depth = 8;
GFX_DRIVER *gfx_driver;
int gfx_capabilities;
DIGI_DRIVER *digi_driver;
MIDI_DRIVER *midi_driver;
volatile long midi_pos = -1;
volatile long midi_time;
long midi_loop_start = -1, midi_loop_end = -1;

PALETTE black_palette;
PALETTE desktop_palette;
PALETTE default_palette;

/* Allegro's default palette layout: the 16 PC colours, then a 6x6x6 colour
 * cube, then a grey ramp; made at install time */
static void make_default_palette(RGB *p)
{
    static const unsigned char pc16[16][3] = {
        { 0, 0, 0 }, { 0, 0, 42 }, { 0, 42, 0 }, { 0, 42, 42 }, { 42, 0, 0 }, { 42, 0, 42 }, { 42, 21, 0 }, { 42, 42, 42 },
        { 21, 21, 21 }, { 21, 21, 63 }, { 21, 63, 21 }, { 21, 63, 63 }, { 63, 21, 21 }, { 63, 21, 63 }, { 63, 63, 21 }, { 63, 63, 63 },
    };
    int i, r, g, b;
    for (i = 0; i < 16; i++) { p[i].r = pc16[i][0]; p[i].g = pc16[i][1]; p[i].b = pc16[i][2]; p[i].filler = 0; }
    i = 16;
    for (r = 0; r < 6; r++)
        for (g = 0; g < 6; g++)
            for (b = 0; b < 6; b++, i++) {
                p[i].r = (unsigned char)(r * 63 / 5); p[i].g = (unsigned char)(g * 63 / 5); p[i].b = (unsigned char)(b * 63 / 5); p[i].filler = 0;
            }
    for (; i < 256; i++) {
        int v = (i - 232) * 63 / 23;
        p[i].r = p[i].g = p[i].b = (unsigned char)v; p[i].filler = 0;
    }
}

static struct a4_public pub;
static int exit_registered;

int install_allegro(int system_id, int *errno_ptr, int (*atexit_ptr)(void (*)(void)))
{
    if (errno_ptr) allegro_errno = errno_ptr;
    make_default_palette(default_palette);
    memcpy(desktop_palette, default_palette, sizeof(PALETTE));
    memset(black_palette, 0, sizeof(PALETTE));
    pub.size = sizeof(pub);
    pub.allegro_error = allegro_error;
    pub.allegro_errno = &allegro_errno;
    pub.screen = &screen;
    pub.screen_w = &_a4_screen_w;
    pub.screen_h = &_a4_screen_h;
    pub.font = &font;
    pub.key = key;
    pub.key_shifts = &key_shifts;
    pub.mouse_x = &mouse_x; pub.mouse_y = &mouse_y; pub.mouse_z = &mouse_z;
    pub.mouse_w = &mouse_w; pub.mouse_b = &mouse_b; pub.mouse_pos = &mouse_pos;
    pub.retrace_count = &retrace_count;
    pub.joy = joy;
    pub.num_joysticks = &num_joysticks;
    pub.rgb_map = &rgb_map;
    pub.color_map = &color_map;
    pub.gfx_driver = &gfx_driver;
    pub.digi_driver = &digi_driver;
    pub.midi_driver = &midi_driver;
    pub.midi_pos = &midi_pos;
    pub.os_type = &os_type;
    pub.keyboard_callback = &keyboard_callback;
    pub.keyboard_ucallback = &keyboard_ucallback;
    pub.keyboard_lowlevel_callback = &keyboard_lowlevel_callback;
    pub.mouse_callback = &mouse_callback;
    pub.color_depth = &_color_depth;
    pub.default_palette = default_palette;
    pub.desktop_palette = desktop_palette;
    if (a4_install(&pub, system_id) != 0) return -1;
    if (atexit_ptr && !exit_registered) { exit_registered = 1; atexit_ptr(allegro_exit); }
    return 0;
}

/* ---- calls with a format ---------------------------------------------------------- */

int uvszprintf(char *buf, int size, const char *format, va_list args) { return vsnprintf(buf, (size_t)size, format, args); }
int uszprintf(char *buf, int size, const char *format, ...)
{
    va_list ap; int r;
    va_start(ap, format); r = vsnprintf(buf, (size_t)size, format, ap); va_end(ap);
    return r;
}
int usprintf(char *buf, const char *format, ...)
{
    va_list ap; int r;
    va_start(ap, format); r = vsprintf(buf, format, ap); va_end(ap);
    return r;
}

void allegro_message(const char *msg, ...)
{
    char buf[1024];
    va_list ap;
    va_start(ap, msg); vsnprintf(buf, sizeof(buf), msg, ap); va_end(ap);
    fputs(buf, stderr);
}

#define FORMAT(buf) char buf[1024]; va_list ap; va_start(ap, format); vsnprintf(buf, sizeof(buf), format, ap); va_end(ap)

void textprintf_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *format, ...)
{ FORMAT(b); textout_ex(bmp, f, b, x, y, color, bg); }
void textprintf_centre_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *format, ...)
{ FORMAT(b); textout_centre_ex(bmp, f, b, x, y, color, bg); }
void textprintf_right_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *format, ...)
{ FORMAT(b); textout_right_ex(bmp, f, b, x, y, color, bg); }
void textprintf_justify_ex(BITMAP *bmp, const FONT *f, int x1, int x2, int y, int diff, int color, int bg, const char *format, ...)
{ FORMAT(b); textout_justify_ex(bmp, f, b, x1, x2, y, diff, color, bg); }
void textprintf(BITMAP *bmp, const FONT *f, int x, int y, int color, const char *format, ...)
{ FORMAT(b); textout(bmp, f, b, x, y, color); }
void textprintf_centre(BITMAP *bmp, const FONT *f, int x, int y, int color, const char *format, ...)
{ FORMAT(b); textout_centre(bmp, f, b, x, y, color); }
void textprintf_right(BITMAP *bmp, const FONT *f, int x, int y, int color, const char *format, ...)
{ FORMAT(b); textout_right(bmp, f, b, x, y, color); }
void textprintf_justify(BITMAP *bmp, const FONT *f, int x1, int x2, int y, int diff, int color, const char *format, ...)
{ FORMAT(b); textout_justify(bmp, f, b, x1, x2, y, diff, color); }
