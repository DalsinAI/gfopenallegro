/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library's inside: the state one game has (struct a4_state), and
 * the system calls the core uses (a4_os_*), which are AmigaOS's in the
 * library (library/a4_os_amiga.c) and the C library's in the host build
 * (src/a4_os_host.c, for the unit tests).
 *
 * In the library, every opener has its own a4_state; the library's entry
 * points put it in a4 (library/allegro4_state.h). The public variables
 * (key[], screen, mouse_x...) are the game's own, in the stubs it links;
 * the library reaches them through the addresses the stubs give it at
 * install_allegro (struct a4_public). So every file of the core includes
 * this header first.
 */
#ifndef A4_INTERNAL_H
#define A4_INTERNAL_H

#ifdef A4_LIBRARY
#include "../library/allegro4_state.h"
#endif

#include "allegro.h"
#include "acgame/platform.h"              /* before the macros below: its fields are named key */

/* ---- the public variables, by address ----------------------------------- */

struct a4_public {
    unsigned long size;                     /* sizeof(struct a4_public): grows at the end only */
    char *allegro_error;
    int **allegro_errno;
    BITMAP **screen;
    int *screen_w, *screen_h;
    FONT **font;
    volatile char *key;
    volatile int *key_shifts;
    volatile int *mouse_x, *mouse_y, *mouse_z, *mouse_w, *mouse_b, *mouse_pos;
    volatile int *retrace_count;
    JOYSTICK_INFO *joy;
    int *num_joysticks;
    RGB_MAP **rgb_map;
    COLOR_MAP **color_map;
    GFX_DRIVER **gfx_driver;
    DIGI_DRIVER **digi_driver;
    MIDI_DRIVER **midi_driver;
    volatile long *midi_pos;
    int *os_type;
    int (**keyboard_callback)(int key);
    int (**keyboard_ucallback)(int key, int *scancode);
    void (**keyboard_lowlevel_callback)(int scancode);
    void (**mouse_callback)(int flags);
    int *color_depth;
    RGB *default_palette;                   /* the game's copy: set at set_gfx_mode */
    RGB *desktop_palette;
};

#ifdef A4_LIBRARY
#define A4P (a4_state_ptr->pub)
#undef allegro_error
#define allegro_error (A4P->allegro_error)
#define allegro_errno (*A4P->allegro_errno)
#define screen (*A4P->screen)
#define _a4_screen_w (*A4P->screen_w)
#define _a4_screen_h (*A4P->screen_h)
#define font (*A4P->font)
#define key (A4P->key)
#define key_shifts (*A4P->key_shifts)
#define mouse_x (*A4P->mouse_x)
#define mouse_y (*A4P->mouse_y)
#define mouse_z (*A4P->mouse_z)
#define mouse_w (*A4P->mouse_w)
#define mouse_b (*A4P->mouse_b)
#define mouse_pos (*A4P->mouse_pos)
#define retrace_count (*A4P->retrace_count)
#define joy (A4P->joy)
#define num_joysticks (*A4P->num_joysticks)
#define rgb_map (*A4P->rgb_map)
#define color_map (*A4P->color_map)
#define gfx_driver (*A4P->gfx_driver)
#define digi_driver (*A4P->digi_driver)
#define midi_driver (*A4P->midi_driver)
#define midi_pos (*A4P->midi_pos)
#define os_type (*A4P->os_type)
#define keyboard_callback (*A4P->keyboard_callback)
#define keyboard_ucallback (*A4P->keyboard_ucallback)
#define keyboard_lowlevel_callback (*A4P->keyboard_lowlevel_callback)
#define mouse_callback (*A4P->mouse_callback)
#define _color_depth (*A4P->color_depth)
#define default_palette (A4P->default_palette)
#define desktop_palette (A4P->desktop_palette)
#endif

typedef struct a4_file a4_file;

/* ---- PACKFILE ------------------------------------------------------------- */

enum { SRC_FILE, SRC_PARENT, SRC_VTABLE };
#define LZ_N 4096
#define LZ_F 18

struct PACKFILE {
    int kind;
    int write;
    a4_file *fh;
    PACKFILE *parent;
    const PACKFILE_VTABLE *vt;
    void *userdata;
    long limit;                         /* bytes left to take from the source; -1: no limit */
    unsigned char buf[F_BUF_SIZE];      /* the source's bytes (SRC_FILE) */
    int buf_pos, buf_len;
    long fsize;                         /* a chunk's unpacked size */
    int unget;                          /* -1, or a byte pushed back */
    int eof, err;
    /* LZSS */
    int pack;
    unsigned char *ring;
    int r;
    unsigned flags;
    int copy_pos, copy_left;
    /* a chunk being written: its bytes, put in the parent on close */
    unsigned char *wbuf;
    long wlen, wcap;
};

/* ---- one game's state --------------------------------------------------- */

#define A4_MAX_TIMERS 16
#define A4_KEYBUF 64
#define A4_VOICES 16
#define A4_TEXT_MAX 1024

struct a4_timer {
    void (*proc)(void);
    void (*param_proc)(void *);
    void *param;
    uint32_t period_us;
    uint64_t due_us;
};

struct a4_voice {
    const SAMPLE *spl;
    int playing;
    int loop;                       /* PLAYMODE_LOOP etc. */
    int vol;                        /* 0-255 */
    int pan;                        /* 0 left, 128 centre, 255 right */
    int freq;                       /* Hz */
    uint32_t pos_fx;                /* position in frames, 16.16 */
    int dir;                        /* 1 forward, -1 backward (bidir) */
    int allocated;
    int autokill;                   /* play_sample's: freed when it ends */
};

struct a4_datatype {
    int id;
    void *(*load)(PACKFILE *f, long size);
    void (*destroy)(void *data);
};

struct a4_state {
    struct a4_public *pub;
    int installed;
    /* the screen */
    int gfx_on;
    int gfx_card;
    BITMAP *screen_bmp;
    GFX_DRIVER gfx_drv;
    unsigned char palette[PAL_SIZE][3];     /* 6-bit, what is shown */
    int palette_dirty;
    int screen_dirty;
    uint32_t last_present_ms;
    int refresh_rate;
    int requested_refresh;
    char window_title[64];
    /* drawing */
    int draw_mode;
    BITMAP *pattern;
    int pattern_x, pattern_y;
    int text_bg;                            /* text_mode()'s */
    /* keyboard */
    int kb_on;
    unsigned char raw_prev[128];
    int keybuf[A4_KEYBUF];
    int keybuf_scancode[A4_KEYBUF];
    int kb_head, kb_tail;
    int capslock;
    /* mouse */
    int mouse_on;
    int mouse_range[4];
    int mouse_pressed_prev;
    int mickey_x, mickey_y;
    /* joystick */
    int joy_on;
    /* timers */
    int timer_on;
    struct a4_timer timers[A4_MAX_TIMERS];
    uint64_t retrace_due_us;
    void *timer_task;                       /* a4_os's */
    /* sound */
    int sound_on;
    int digi_volume, midi_volume;
    struct a4_voice voices[A4_VOICES];
    uint32_t mix_last_ms;
    DIGI_DRIVER digi_drv;
    MIDI_DRIVER midi_drv;
    int audio_out_ok;                       /* acgame took audio */
    /* datafiles */
    struct a4_datatype types[32];
    int ntypes;
    long last_obj_type;                     /* the type of the last "file#OBJECT" opened */
    char password[64];
    /* fonts */
    FONT *builtin_font;
    /* misc */
    char text[A4_TEXT_MAX];                 /* scratch for formatted text */
    void *config;                           /* a4_config.c's */
    void (*close_button)(void);
    int color_conv;
    const RGB *selected_palette;
    RGB selected_copy[PAL_SIZE];
    int has_selected;
};

#ifdef A4_LIBRARY
#define A4S (a4_state_ptr)
#else
extern struct a4_state a4_host_state;
#define A4S (&a4_host_state)
#endif

/* ---- system calls ---------------------------------------------------------- */

void *a4_malloc(size_t n);
void *a4_calloc(size_t n);
void *a4_realloc(void *p, size_t oldn, size_t n);
void a4_free(void *p);
void a4_config_shutdown(void);
char *a4_strdup0(const char *s);

a4_file *a4_os_open(const char *name, int write);
long a4_os_read(a4_file *f, void *buf, long n);
long a4_os_write(a4_file *f, const void *buf, long n);
int a4_os_close(a4_file *f);
/* 0 when missing; *isdir, *size, *mtime filled when given */
int a4_os_stat(const char *name, int *isdir, long *size, long *mtime);
int a4_os_delete(const char *name);
void *a4_os_opendir(const char *dir);
int a4_os_readdir(void *d, char *name, int size, int *isdir, long *fsize, long *mtime);
void a4_os_closedir(void *d);
uint64_t a4_os_micros(void);                /* monotonic */
void a4_os_delay_ms(unsigned ms);
/* the timer task: calls a4_timer_dispatch() on its own; 0 when started */
int a4_os_timer_start(void);
void a4_os_timer_stop(void);
int a4_os_timer_async(void);                /* 1 when timers run by themselves */
void a4_os_lock(void);
void a4_os_unlock(void);
void a4_os_message(const char *text);
void a4_os_title(const char *text);

/* ---- inside calls ------------------------------------------------------------ */

void a4_timer_dispatch(void);               /* run what is due */
void a4_poll_point(void);                   /* input, timers (no task), sound, a dirty screen */
void a4_mark_screen(BITMAP *bmp);
void a4_present_if_dirty(void);
void a4_present(void);
void a4_audio_pump(void);
int a4_is_screen(BITMAP *bmp);
BITMAP *a4_bitmap_root(BITMAP *bmp);
FONT *a4_builtin_font(void);
void a4_font_free_builtin(void);
void a4_kb_poll(void);
void a4_set_error(const char *msg);

/* 6-bit palette in, 8-bit out */
static inline int a4_pal63to255(int c) { return (c << 2) | (c >> 4); }

#endif
