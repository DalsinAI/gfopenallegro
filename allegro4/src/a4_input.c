/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Keyboard, mouse and joystick from ACGame's poll. ACGame's window belongs
 * to the game's own task, so input is read at the poll points (the input
 * calls, vsync, rest, blits to the screen); keyboard_needs_poll() and
 * mouse_needs_poll() say so, as Allegro 4 does on systems like this.
 */
#include "a4_internal.h"
#include "acgame/platform.h"

/* Amiga raw key code to Allegro 4 scancode */
static const unsigned char raw_to_a4[128] = {
    /* 0x00 */ KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
    /* 0x08 */ KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUALS, KEY_BACKSLASH, 0, KEY_0_PAD,
    /* 0x10 */ KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I,
    /* 0x18 */ KEY_O, KEY_P, KEY_OPENBRACE, KEY_CLOSEBRACE, 0, KEY_1_PAD, KEY_2_PAD, KEY_3_PAD,
    /* 0x20 */ KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K,
    /* 0x28 */ KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_BACKSLASH2, 0, KEY_4_PAD, KEY_5_PAD, KEY_6_PAD,
    /* 0x30 */ KEY_BACKSLASH2, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
    /* 0x38 */ KEY_COMMA, KEY_STOP, KEY_SLASH, 0, KEY_DEL_PAD, KEY_7_PAD, KEY_8_PAD, KEY_9_PAD,
    /* 0x40 */ KEY_SPACE, KEY_BACKSPACE, KEY_TAB, KEY_ENTER_PAD, KEY_ENTER, KEY_ESC, KEY_DEL, KEY_INSERT,
    /* 0x48 */ KEY_PGUP, KEY_PGDN, KEY_MINUS_PAD, KEY_F11, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT,
    /* 0x50 */ KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
    /* 0x58 */ KEY_F9, KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_SLASH_PAD, KEY_ASTERISK, KEY_PLUS_PAD, KEY_MENU,
    /* 0x60 */ KEY_LSHIFT, KEY_RSHIFT, KEY_CAPSLOCK, KEY_LCONTROL, KEY_ALT, KEY_ALTGR, KEY_LWIN, KEY_RWIN,
    /* 0x68 */ 0, 0, 0, KEY_MENU, 0, KEY_PRTSCR, KEY_PAUSE, KEY_F12,
    /* 0x70 */ KEY_HOME, KEY_END, 0, 0, 0, 0, 0, 0,
    /* 0x78 */ 0, 0, 0, 0, 0, 0, 0, 0,
};

/* scancode to ASCII: plain and shifted (US layout, which is what the
 * Allegro 4 games expect of their keys) */
static const char ascii_plain[KEY_MAX] = {
    0, 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    '0','1','2','3','4','5','6','7','8','9',
    '0','1','2','3','4','5','6','7','8','9',
    0,0,0,0,0,0,0,0,0,0,0,0,
    27, '`', '-', '=', 8, 9, '[', ']', 13, ';', '\'', '\\', '\\', ',', '.', '/', ' ',
    0, 127, 0, 0, 0, 0, 0, 0, 0, 0,
    '/', '*', '-', '+', 127, 13, 0, 0,
};
static const char ascii_shift[KEY_MAX] = {
    0, 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    ')','!','@','#','$','%','^','&','*','(',
    '0','1','2','3','4','5','6','7','8','9',
    0,0,0,0,0,0,0,0,0,0,0,0,
    27, '~', '_', '+', 8, 9, '{', '}', 13, ':', '"', '|', '|', '<', '>', '?', ' ',
    0, 127, 0, 0, 0, 0, 0, 0, 0, 0,
    '/', '*', '-', '+', 127, 13, 0, 0,
};

static const char *const key_names[KEY_MAX] = {
    "(none)", "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
    "0","1","2","3","4","5","6","7","8","9",
    "0 PAD","1 PAD","2 PAD","3 PAD","4 PAD","5 PAD","6 PAD","7 PAD","8 PAD","9 PAD",
    "F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",
    "ESC","TILDE","MINUS","EQUALS","BACKSPACE","TAB","OPENBRACE","CLOSEBRACE","ENTER","COLON","QUOTE",
    "BACKSLASH","BACKSLASH2","COMMA","STOP","SLASH","SPACE","INSERT","DEL","HOME","END","PGUP","PGDN",
    "LEFT","RIGHT","UP","DOWN","SLASH_PAD","ASTERISK","MINUS_PAD","PLUS_PAD","DEL_PAD","ENTER_PAD",
    "PRTSCR","PAUSE","ABNT_C1","YEN","KANA","CONVERT","NOCONVERT","AT","CIRCUMFLEX","COLON2","KANJI",
    "EQUALS_PAD","BACKQUOTE","SEMICOLON","COMMAND","UNKNOWN1","UNKNOWN2","UNKNOWN3","UNKNOWN4",
    "UNKNOWN5","UNKNOWN6","UNKNOWN7","UNKNOWN8",
    "LSHIFT","RSHIFT","LCONTROL","RCONTROL","ALT","ALTGR","LWIN","RWIN","MENU","SCRLOCK","NUMLOCK","CAPSLOCK",
};

int scancode_to_ascii(int sc)
{
    if (sc <= 0 || sc >= KEY_MAX) return 0;
    return (unsigned char)ascii_plain[sc];
}

const char *scancode_to_name(int sc)
{
    if (sc < 0 || sc >= KEY_MAX) return "(none)";
    return key_names[sc] ? key_names[sc] : "(none)";
}

static void push_key(int ascii, int sc)
{
    int next = (A4S->kb_tail + 1) % A4_KEYBUF;
    if (keyboard_ucallback) { ascii = keyboard_ucallback(ascii, &sc); if (!ascii && !sc) return; }
    else if (keyboard_callback) {
        int k = keyboard_callback((sc << 8) | (ascii & 255));
        if (!k) return;
        ascii = k & 255; sc = k >> 8;
    }
    if (next == A4S->kb_head) return;           /* full: drop it, as Allegro does */
    A4S->keybuf[A4S->kb_tail] = ascii;
    A4S->keybuf_scancode[A4S->kb_tail] = sc;
    A4S->kb_tail = next;
}

/* the key matrix from ACGame's raw keys, presses into the buffer */
void a4_kb_poll(void)
{
    const uint8_t *raw = acgame_platform_rawkeys();
    int i, shifts = 0;
    if (!raw) return;
    for (i = 0; i < 128; i++) {
        int sc = raw_to_a4[i];
        int down = raw[i] != 0;
        if (!sc) continue;
        if (down != (A4S->raw_prev[i] != 0)) {
            A4S->raw_prev[i] = (unsigned char)down;
            if (keyboard_lowlevel_callback) keyboard_lowlevel_callback(down ? sc : (sc | 0x80));
            key[sc] = down ? (char)-1 : 0;
            if (down) {
                if (sc == KEY_CAPSLOCK) A4S->capslock = !A4S->capslock;
                if (sc < KEY_MODIFIERS) {
                    int shift = raw[0x60] || raw[0x61];
                    int ascii = shift ? ascii_shift[sc] : ascii_plain[sc];
                    if (A4S->capslock && sc >= KEY_A && sc <= KEY_Z) ascii = shift ? ascii_plain[sc] : ascii_shift[sc];
                    if ((raw[0x63]) && sc >= KEY_A && sc <= KEY_Z) ascii = sc;    /* ctrl+letter */
                    push_key((unsigned char)ascii, sc);
                }
            }
        }
    }
    if (key[KEY_LSHIFT] || key[KEY_RSHIFT]) shifts |= KB_SHIFT_FLAG;
    if (key[KEY_LCONTROL] || key[KEY_RCONTROL]) shifts |= KB_CTRL_FLAG;
    if (key[KEY_ALT] || key[KEY_ALTGR]) shifts |= KB_ALT_FLAG;
    if (key[KEY_LWIN]) shifts |= KB_LWIN_FLAG;
    if (key[KEY_RWIN]) shifts |= KB_RWIN_FLAG;
    if (A4S->capslock) shifts |= KB_CAPSLOCK_FLAG;
    key_shifts = shifts;
}

static void mouse_poll_from(const acgame_input_state *st)
{
    int x = 0, y = 0, b = 0, flags = 0;
    if (!A4S->mouse_on) return;
    {
        int px, py;
        if (acgame_platform_pointer(&px, &py) == 0) { x = px; y = py; }
        else { x = mouse_x + st->mouse_dx; y = mouse_y + st->mouse_dy; }
    }
    A4S->mickey_x += st->mouse_dx;
    A4S->mickey_y += st->mouse_dy;
    x = MID(A4S->mouse_range[0], x, A4S->mouse_range[2]);
    y = MID(A4S->mouse_range[1], y, A4S->mouse_range[3]);
    /* ACGame's buttons: bit 0 left, bit 1 right, bit 2 middle (Allegro's order) */
    b = st->mouse_buttons & 7;
    if (x != mouse_x || y != mouse_y) flags |= MOUSE_FLAG_MOVE;
    if ((b & 1) && !(mouse_b & 1)) flags |= MOUSE_FLAG_LEFT_DOWN;
    if (!(b & 1) && (mouse_b & 1)) flags |= MOUSE_FLAG_LEFT_UP;
    if ((b & 2) && !(mouse_b & 2)) flags |= MOUSE_FLAG_RIGHT_DOWN;
    if (!(b & 2) && (mouse_b & 2)) flags |= MOUSE_FLAG_RIGHT_UP;
    if ((b & 4) && !(mouse_b & 4)) flags |= MOUSE_FLAG_MIDDLE_DOWN;
    if (!(b & 4) && (mouse_b & 4)) flags |= MOUSE_FLAG_MIDDLE_UP;
    mouse_x = x;
    mouse_y = y;
    mouse_b = b;
    mouse_pos = (x << 16) | (y & 0xFFFF);
    if (flags && mouse_callback) mouse_callback(flags);
}

/* st->key is ACGame's key array; in the library "key" is the game's key[] */
#pragma push_macro("key")
#undef key
static void joy_from(const acgame_input_state *st, JOYSTICK_INFO *j)
{
    int i;
    /* the d-pad and stick as stick 0 (digital and analogue), the buttons in
     * ACGame's (SDL's) order */
    {
        int lx = st->pad.axes[ACGAME_PAD_LEFTX], ly = st->pad.axes[ACGAME_PAD_LEFTY];
        int left = st->key[ACGAME_KEY_LEFT] || lx < -16384, right = st->key[ACGAME_KEY_RIGHT] || lx > 16384;
        int up = st->key[ACGAME_KEY_UP] || ly < -16384, down = st->key[ACGAME_KEY_DOWN] || ly > 16384;
        j->stick[0].axis[0].pos = left ? -128 : right ? 128 : lx / 256;
        j->stick[0].axis[0].d1 = left;
        j->stick[0].axis[0].d2 = right;
        j->stick[0].axis[1].pos = up ? -128 : down ? 128 : ly / 256;
        j->stick[0].axis[1].d1 = up;
        j->stick[0].axis[1].d2 = down;
    }
    for (i = 0; i < j->num_buttons && i < ACGAME_PAD_BUTTON_COUNT; i++)
        j->button[i].b = (st->pad.buttons >> i) & 1;
    /* fire keys count as the first buttons too (a CD32 pad or the keyboard) */
    if (st->key[ACGAME_KEY_FIRE1]) j->button[0].b = 1;
    if (st->key[ACGAME_KEY_FIRE2] && j->num_buttons > 1) j->button[1].b = 1;
}

/* one ACGame poll feeds keys, mouse and joystick */
static void input_poll(void)
{
    acgame_input_state st;
    if (!A4S->gfx_on) return;
    acgame_platform_poll(&st);
    if (A4S->kb_on) a4_kb_poll();
    mouse_poll_from(&st);
    if (A4S->joy_on) joy_from(&st, &joy[0]);
}

void a4_poll_point(void)
{
    input_poll();
    if (!a4_os_timer_async()) a4_timer_dispatch();
    a4_audio_pump();
    /* a game that draws on the screen and never blits a whole frame: show
     * it at most every 20 ms from the poll points */
    if (A4S->screen_dirty && A4S->gfx_on) {
        uint32_t now = acgame_platform_ticks_ms();
        if ((uint32_t)(now - A4S->last_present_ms) >= 20u) a4_present();
    }
}

/* ---- keyboard calls ------------------------------------------------------------- */

int install_keyboard(void)
{
    if (A4S->kb_on) return 0;
    memset((void *)key, 0, KEY_MAX);
    memset(A4S->raw_prev, 0, sizeof(A4S->raw_prev));
    A4S->kb_head = A4S->kb_tail = 0;
    A4S->kb_on = 1;
    return 0;
}
void remove_keyboard(void) { A4S->kb_on = 0; memset((void *)key, 0, KEY_MAX); key_shifts = 0; }
int poll_keyboard(void) { if (!A4S->kb_on) return -1; a4_poll_point(); return 0; }
int keyboard_needs_poll(void) { return TRUE; }

int keypressed(void)
{
    a4_poll_point();
    a4_present_if_dirty();
    return A4S->kb_head != A4S->kb_tail;
}

int ureadkey(int *scancode)
{
    int a;
    while (!keypressed()) a4_os_delay_ms(5);
    a = A4S->keybuf[A4S->kb_head];
    if (scancode) *scancode = A4S->keybuf_scancode[A4S->kb_head];
    A4S->kb_head = (A4S->kb_head + 1) % A4_KEYBUF;
    return a;
}

int readkey(void)
{
    int sc, a = ureadkey(&sc);
    return (sc << 8) | (a & 255);
}

void simulate_keypress(int keycode) { push_key(keycode & 255, keycode >> 8); }
void simulate_ukeypress(int keycode, int scancode) { push_key(keycode, scancode); }
void clear_keybuf(void) { a4_poll_point(); A4S->kb_head = A4S->kb_tail = 0; }
void set_leds(int leds) { (void)leds; }
void set_keyboard_rate(int delay, int repeat) { (void)delay; (void)repeat; }
void install_keyboard_hooks(int (*kp)(void), int (*rk)(void)) { (void)kp; (void)rk; }

/* ---- mouse calls ------------------------------------------------------------------ */

int install_mouse(void)
{
    if (A4S->mouse_on) return 3;
    A4S->mouse_on = 1;
    A4S->mouse_range[0] = 0;
    A4S->mouse_range[1] = 0;
    A4S->mouse_range[2] = (A4S->gfx_on ? _a4_screen_w : 320) - 1;
    A4S->mouse_range[3] = (A4S->gfx_on ? _a4_screen_h : 200) - 1;
    mouse_x = mouse_y = mouse_z = mouse_w = mouse_b = 0;
    return 3;                                   /* buttons */
}
void remove_mouse(void) { A4S->mouse_on = 0; }
int poll_mouse(void) { if (!A4S->mouse_on) return -1; a4_poll_point(); return 0; }
int mouse_needs_poll(void) { return TRUE; }
void enable_hardware_cursor(void) {}
void disable_hardware_cursor(void) {}
void select_mouse_cursor(int cursor) { if (A4S->gfx_on) acgame_platform_show_pointer(cursor != MOUSE_CURSOR_NONE); }
/* the system's pointer stands for Allegro's: shown when a game shows it */
void show_mouse(BITMAP *bmp) { if (A4S->gfx_on) acgame_platform_show_pointer(bmp != NULL); }
int show_os_cursor(int cursor) { if (!A4S->gfx_on) return -1; acgame_platform_show_pointer(cursor != MOUSE_CURSOR_NONE); return 0; }
void scare_mouse(void) {}
void scare_mouse_area(int x, int y, int w, int h) { (void)x; (void)y; (void)w; (void)h; }
void unscare_mouse(void) {}
void position_mouse(int x, int y) { mouse_x = x; mouse_y = y; mouse_pos = (x << 16) | (y & 0xFFFF); }
void position_mouse_z(int z) { mouse_z = z; }
void set_mouse_range(int x1, int y1, int x2, int y2)
{
    A4S->mouse_range[0] = x1; A4S->mouse_range[1] = y1; A4S->mouse_range[2] = x2; A4S->mouse_range[3] = y2;
}
void set_mouse_speed(int xs, int ys) { (void)xs; (void)ys; }
void set_mouse_sprite(BITMAP *s) { (void)s; }
void set_mouse_sprite_focus(int x, int y) { (void)x; (void)y; }
void get_mouse_mickeys(int *mx, int *my)
{
    if (mx) *mx = A4S->mickey_x;
    if (my) *my = A4S->mickey_y;
    A4S->mickey_x = A4S->mickey_y = 0;
}

/* ---- joystick calls ------------------------------------------------------------- */

static const char *const button_names[] = { "A", "B", "X", "Y", "Back", "Guide", "Start", "LStick", "RStick", "L", "R" };

int install_joystick(int type)
{
    JOYSTICK_INFO *j;
    int i;
    (void)type;
    if (A4S->joy_on) return 0;
    memset(joy, 0, sizeof(JOYSTICK_INFO) * MAX_JOYSTICKS);
    j = &joy[0];
    j->flags = JOYFLAG_DIGITAL | JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    j->num_sticks = 1;
    j->stick[0].flags = JOYFLAG_DIGITAL | JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    j->stick[0].num_axis = 2;
    j->stick[0].name = "Stick";
    j->stick[0].axis[0].name = "X";
    j->stick[0].axis[1].name = "Y";
    j->num_buttons = 11;
    for (i = 0; i < 11; i++) j->button[i].name = button_names[i];
    num_joysticks = 1;
    A4S->joy_on = 1;
    return 0;
}
void remove_joystick(void) { A4S->joy_on = 0; num_joysticks = 0; }
int poll_joystick(void) { if (!A4S->joy_on) return -1; a4_poll_point(); return 0; }
int calibrate_joystick(int n) { (void)n; return 0; }
const char *calibrate_joystick_name(int n) { (void)n; return NULL; }
int save_joystick_data(const char *f) { (void)f; return 0; }
int load_joystick_data(const char *f) { (void)f; return 0; }
int initialise_joystick(void) { return install_joystick(JOY_TYPE_AUTODETECT); }
