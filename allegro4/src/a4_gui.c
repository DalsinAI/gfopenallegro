/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Allegro 4's dialog engine and standard dialog objects (a4_gui.h). This
 * runs in the game's own code (liballeg.a): the objects are the game's, and
 * they draw and read the keys and mouse through allegro4.library's calls.
 * Only the public API is used here, so the host tests run it as it is.
 */
#include <allegro.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int gui_fg_color = 255, gui_mg_color = 8, gui_bg_color = 0;
int gui_font_baseline = 0;
DIALOG *active_dialog;
DIALOG_PLAYER *active_dialog_player;

static int def_mouse_x(void) { return mouse_x; }
static int def_mouse_y(void) { return mouse_y; }
static int def_mouse_z(void) { return mouse_z; }
static int def_mouse_b(void) { poll_mouse(); return mouse_b; }

int (*gui_mouse_x)(void) = def_mouse_x;
int (*gui_mouse_y)(void) = def_mouse_y;
int (*gui_mouse_z)(void) = def_mouse_z;
int (*gui_mouse_b)(void) = def_mouse_b;

static BITMAP *gui_screen;
static int window_close_button = 1;
static void (*window_close_hook)(void);

void gui_set_screen(BITMAP *bmp) { gui_screen = bmp; }
BITMAP *gui_get_screen(void) { return gui_screen ? gui_screen : screen; }

int set_window_close_button(int enable) { window_close_button = enable; return 0; }
void set_window_close_hook(void (*proc)(void)) { window_close_hook = proc; set_close_button_callback(proc); }

static long msec(void)
{
    clock_t t = clock();
    return CLOCKS_PER_SEC >= 1000 ? (long)(t / (CLOCKS_PER_SEC / 1000)) : (long)t * (1000 / CLOCKS_PER_SEC);
}
#define DCLICK_MS 300

/* ---- text with & shortcuts ----------------------------------------------------------- */

/* "&File" draws File with F underlined; "&&" draws one & */
int gui_textout_ex(BITMAP *bmp, const char *s, int x, int y, int color, int bg, int centre)
{
    char buf[512];
    int under[256], nu = 0, n = 0, i, len;
    if (!s) return 0;
    for (; *s && n < (int)sizeof(buf) - 1; s++) {
        if (*s == '&') {
            if (s[1] == '&') { buf[n++] = '&'; s++; }
            else if (s[1] && nu < 256) under[nu++] = n;
            continue;
        }
        buf[n++] = *s;
    }
    buf[n] = 0;
    len = text_length(font, buf);
    if (centre) x -= len / 2;
    if (bmp) {
        textout_ex(bmp, font, buf, x, y, color, bg);
        for (i = 0; i < nu; i++) {
            char c1[2] = { buf[under[i]], 0 };
            int ux, uw, uy = y + text_height(font) - gui_font_baseline;
            buf[under[i]] = 0;
            ux = x + text_length(font, buf);
            buf[under[i]] = c1[0];
            uw = text_length(font, c1);
            if (uw > 0) hline(bmp, ux, uy, ux + uw - 1, color);
        }
    }
    return len;
}

int gui_textout(BITMAP *bmp, const char *s, int x, int y, int color, int centre)
{
    return gui_textout_ex(bmp, s, x, y, color, -1, centre);
}

int gui_strlen(const char *s) { return gui_textout_ex(NULL, s, 0, 0, 0, -1, FALSE); }

/* ---- dialogs ----------------------------------------------------------------------------- */

static int count_objects(const DIALOG *d) { int n = 0; while (d[n].proc) n++; return n; }

void position_dialog(DIALOG *dialog, int x, int y)
{
    int i, n = count_objects(dialog), minx = INT_MAX, miny = INT_MAX;
    for (i = 0; i < n; i++) { if (dialog[i].x < minx) minx = dialog[i].x; if (dialog[i].y < miny) miny = dialog[i].y; }
    for (i = 0; i < n; i++) { dialog[i].x += x - minx; dialog[i].y += y - miny; }
}

void centre_dialog(DIALOG *dialog)
{
    int i, n = count_objects(dialog), minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
    if (!n) return;
    for (i = 0; i < n; i++) {
        if (dialog[i].x < minx) minx = dialog[i].x;
        if (dialog[i].y < miny) miny = dialog[i].y;
        if (dialog[i].x + dialog[i].w > maxx) maxx = dialog[i].x + dialog[i].w;
        if (dialog[i].y + dialog[i].h > maxy) maxy = dialog[i].y + dialog[i].h;
    }
    position_dialog(dialog, (SCREEN_W - (maxx - minx)) / 2, (SCREEN_H - (maxy - miny)) / 2);
}

void set_dialog_color(DIALOG *dialog, int fg, int bg)
{
    int i;
    for (i = 0; dialog[i].proc; i++) { dialog[i].fg = fg; dialog[i].bg = bg; }
}

int find_dialog_focus(DIALOG *dialog)
{
    int i;
    for (i = 0; dialog[i].proc; i++)
        if (dialog[i].flags & D_GOTFOCUS) return i;
    return -1;
}

int object_message(DIALOG *d, int msg, int c)
{
    int r;
    if (msg == MSG_DRAW && (d->flags & D_HIDDEN)) return D_O_K;
    r = d->proc(msg, d, c);
    if (msg == MSG_DRAW) d->flags &= ~D_DIRTY;
    if (r & D_REDRAWME) { d->flags |= D_DIRTY; r &= ~D_REDRAWME; }
    return r;
}

int dialog_message(DIALOG *dialog, int msg, int c, int *obj)
{
    int i, r, res = D_O_K;
    if (msg == MSG_DRAW) acquire_screen();
    for (i = 0; dialog[i].proc; i++) {
        if (msg == MSG_START || msg == MSG_END || !(dialog[i].flags & D_HIDDEN)) {
            r = object_message(&dialog[i], msg, c);
            if (r != D_O_K) { res |= r; if (obj) *obj = i; }
        }
        if (msg == MSG_IDLE && (dialog[i].flags & (D_DIRTY | D_HIDDEN)) == D_DIRTY)
            object_message(&dialog[i], MSG_DRAW, 0);
    }
    if (msg == MSG_DRAW) release_screen();
    return res;
}

int broadcast_dialog_message(int msg, int c)
{
    int nowhere;
    return active_dialog ? dialog_message(active_dialog, msg, c, &nowhere) : D_O_K;
}

int offer_focus(DIALOG *dialog, int obj, int *focus_obj, int force)
{
    int res = D_O_K;
    if (obj == *focus_obj || (obj >= 0 && (dialog[obj].flags & (D_HIDDEN | D_DISABLED)))) return D_O_K;
    if (obj >= 0) {
        res = object_message(&dialog[obj], MSG_WANTFOCUS, 0);
        if (res & D_WANTFOCUS) res &= ~D_WANTFOCUS;
        else obj = -1;
    }
    if (obj >= 0 || force) {
        if (*focus_obj >= 0) {
            res |= object_message(&dialog[*focus_obj], MSG_LOSTFOCUS, 0);
            if (res & D_WANTFOCUS) {        /* the old one keeps it */
                res &= ~D_WANTFOCUS;
                if (obj < 0) return res;
            }
            dialog[*focus_obj].flags &= ~D_GOTFOCUS;
            dialog[*focus_obj].flags |= D_DIRTY;
        }
        *focus_obj = obj;
        if (obj >= 0) {
            dialog[obj].flags |= D_GOTFOCUS | D_DIRTY;
            res |= object_message(&dialog[obj], MSG_GOTFOCUS, 0);
        }
    }
    return res;
}

static int find_mouse_object(DIALOG *d)
{
    int i, res = -1, mx = gui_mouse_x(), my = gui_mouse_y();
    for (i = 0; d[i].proc; i++)
        if (mx >= d[i].x && my >= d[i].y && mx < d[i].x + d[i].w && my < d[i].y + d[i].h &&
            !(d[i].flags & (D_HIDDEN | D_DISABLED)))
            res = i;
    return res;
}

DIALOG_PLAYER *init_dialog(DIALOG *dialog, int focus_obj)
{
    DIALOG_PLAYER *p = (DIALOG_PLAYER *)calloc(1, sizeof(*p));
    int i;
    if (!p) return NULL;
    p->dialog = dialog;
    p->prev_active = active_dialog;
    p->obj = -1;
    p->res = D_REDRAW;
    p->focus_obj = -1;
    p->mouse_obj = -1;
    p->last_click_obj = -1;
    active_dialog = dialog;
    active_dialog_player = p;
    for (i = 0; dialog[i].proc; i++) dialog[i].flags &= ~(D_GOTMOUSE | D_GOTFOCUS);
    if (focus_obj >= 0 && dialog[focus_obj].proc) {
        p->focus_obj = focus_obj;
        dialog[focus_obj].flags |= D_GOTFOCUS;
    }
    dialog_message(dialog, MSG_START, 0, NULL);
    p->mouse_ox = gui_mouse_x();
    p->mouse_oy = gui_mouse_y();
    p->mouse_oz = gui_mouse_z();
    p->mouse_b = gui_mouse_b();
    p->mouse_obj = find_mouse_object(dialog);
    if (p->mouse_obj >= 0) dialog[p->mouse_obj].flags |= D_GOTMOUSE;
    return p;
}

/* the object a key moves the focus to: Tab and the arrows go to the next or
 * previous object that takes the focus */
static int next_focus(DIALOG *d, int from, int dir)
{
    int n = count_objects(d), i, o;
    if (!n) return -1;
    for (i = 1; i <= n; i++) {
        o = ((from < 0 ? (dir > 0 ? -1 : 0) : from) + dir * i + n * 2) % n;
        if (d[o].flags & (D_HIDDEN | D_DISABLED)) continue;
        if (object_message(&d[o], MSG_WANTFOCUS, 0) & D_WANTFOCUS) return o;
    }
    return from;
}

static int do_close(DIALOG_PLAYER *p, int res, int obj)
{
    p->res = res;
    p->obj = obj;
    return FALSE;
}

int update_dialog(DIALOG_PLAYER *p)
{
    DIALOG *d = p->dialog;
    int r, obj = -1, b, z, mo;

    if (p->res & (D_REDRAW | D_REDRAW_ALL)) {
        p->res &= ~(D_REDRAW | D_REDRAW_ALL);
        dialog_message(d, MSG_DRAW, 0, NULL);
    }
    p->res = D_O_K;

    /* the mouse: who has it */
    b = gui_mouse_b();
    mo = find_mouse_object(d);
    if (mo != p->mouse_obj) {
        if (p->mouse_obj >= 0) {
            d[p->mouse_obj].flags &= ~D_GOTMOUSE;
            p->res |= object_message(&d[p->mouse_obj], MSG_LOSTMOUSE, 0);
        }
        p->mouse_obj = mo;
        if (mo >= 0) {
            d[mo].flags |= D_GOTMOUSE;
            p->res |= object_message(&d[mo], MSG_GOTMOUSE, 0);
        }
    }

    /* a press: focus and click (the object follows the button itself) */
    if ((b & ~p->mouse_b) && p->mouse_obj >= 0) {
        long now = msec();
        int o = p->mouse_obj;
        p->res |= offer_focus(d, o, &p->focus_obj, FALSE);
        /* a click; a second one soon after on the same object is also a double click */
        r = object_message(&d[o], MSG_CLICK, b);
        if (!(r & D_CLOSE) && o == p->last_click_obj && now - p->last_click_ms < DCLICK_MS) {
            r |= object_message(&d[o], MSG_DCLICK, b);
            p->last_click_obj = -1;
        } else {
            p->last_click_obj = o;
            p->last_click_ms = now;
        }
        if (r & D_CLOSE) return do_close(p, r, o);
        p->res |= r;
        b = gui_mouse_b();
    }
    p->mouse_b = b;

    /* the wheel */
    z = gui_mouse_z();
    if (z != p->mouse_oz) {
        int t = p->focus_obj >= 0 ? p->focus_obj : p->mouse_obj;
        if (t >= 0) {
            r = object_message(&d[t], MSG_WHEEL, z - p->mouse_oz);
            if (r & D_CLOSE) { p->mouse_oz = z; return do_close(p, r, t); }
            p->res |= r;
        }
        p->mouse_oz = z;
    }

    /* the keyboard */
    while (keypressed()) {
        int sc, a = ureadkey(&sc), c = (sc << 8) | (a & 255), used = 0, i;
        if (p->focus_obj >= 0) {
            r = object_message(&d[p->focus_obj], MSG_CHAR, c);
            if (r & D_USED_CHAR) used = 1;
            else if (a) {
                r = object_message(&d[p->focus_obj], MSG_UCHAR, a);
                if (r & D_USED_CHAR) used = 1;
            }
            r &= ~D_USED_CHAR;
            if (r & D_CLOSE) return do_close(p, r, p->focus_obj);
            p->res |= r;
        }
        /* a shortcut key */
        if (!used && a)
            for (i = 0; d[i].proc; i++)
                if (d[i].key && tolower(d[i].key) == tolower(a) && !(d[i].flags & (D_HIDDEN | D_DISABLED))) {
                    p->res |= offer_focus(d, i, &p->focus_obj, FALSE);
                    r = object_message(&d[i], MSG_KEY, a);
                    used = 1;
                    if (r & D_CLOSE) return do_close(p, r, i);
                    p->res |= r;
                    break;
                }
        /* offered to everyone (d_keyboard_proc) */
        if (!used) {
            obj = -1;
            r = dialog_message(d, MSG_XCHAR, c, &obj);
            if (r & D_USED_CHAR) used = 1;
            r &= ~D_USED_CHAR;
            if (r & D_CLOSE) return do_close(p, r, obj);
            p->res |= r;
        }
        if (!used) {
            if (sc == KEY_ESC) return do_close(p, D_CLOSE, -1);
            if (sc == KEY_TAB || sc == KEY_DOWN || sc == KEY_RIGHT || sc == KEY_UP || sc == KEY_LEFT) {
                int dir = (sc == KEY_UP || sc == KEY_LEFT || (sc == KEY_TAB && (key_shifts & KB_SHIFT_FLAG))) ? -1 : 1;
                p->res |= offer_focus(d, next_focus(d, p->focus_obj, dir), &p->focus_obj, FALSE);
            } else if ((sc == KEY_ENTER || sc == KEY_ENTER_PAD || sc == KEY_SPACE) && p->focus_obj >= 0) {
                r = object_message(&d[p->focus_obj], MSG_KEY, a);
                if (r & D_CLOSE) return do_close(p, r, p->focus_obj);
                p->res |= r;
            }
        }
    }

    /* idle, and what wants drawing */
    obj = -1;
    r = dialog_message(d, MSG_IDLE, 0, &obj);
    if (r & D_CLOSE) return do_close(p, r, obj);
    p->res |= r;
    return TRUE;
}

int shutdown_dialog(DIALOG_PLAYER *p)
{
    int obj;
    if (!p) return -1;
    dialog_message(p->dialog, MSG_END, 0, NULL);
    obj = p->obj;
    active_dialog = p->prev_active;
    if (active_dialog_player == p) active_dialog_player = NULL;
    free(p);
    return obj;
}

int do_dialog(DIALOG *dialog, int focus_obj)
{
    DIALOG_PLAYER *p;
    BITMAP *mouse_screen = screen;
    show_mouse(mouse_screen);
    p = init_dialog(dialog, focus_obj);
    if (!p) return -1;
    while (update_dialog(p)) rest(1);
    return shutdown_dialog(p);
}

int popup_dialog(DIALOG *dialog, int focus_obj)
{
    int i, x0 = INT_MAX, y0 = INT_MAX, x1 = INT_MIN, y1 = INT_MIN, r;
    BITMAP *under = NULL, *s = gui_get_screen();
    for (i = 0; dialog[i].proc; i++) {
        if (dialog[i].x < x0) x0 = dialog[i].x;
        if (dialog[i].y < y0) y0 = dialog[i].y;
        if (dialog[i].x + dialog[i].w > x1) x1 = dialog[i].x + dialog[i].w;
        if (dialog[i].y + dialog[i].h > y1) y1 = dialog[i].y + dialog[i].h;
    }
    if (s && x1 > x0 && y1 > y0) {
        under = create_bitmap(x1 - x0, y1 - y0);
        if (under) blit(s, under, x0, y0, 0, 0, x1 - x0, y1 - y0);
    }
    r = do_dialog(dialog, focus_obj);
    if (under) { blit(under, s, 0, 0, x0, y0, x1 - x0, y1 - y0); destroy_bitmap(under); }
    return r;
}

/* ---- drawing helpers ----------------------------------------------------------------- */

static int fg_of(const DIALOG *d) { return (d->flags & D_DISABLED) ? gui_mg_color : d->fg; }

static void dotted_rect(BITMAP *b, int x1, int y1, int x2, int y2, int c)
{
    int x, y;
    for (x = x1; x <= x2; x += 2) { putpixel(b, x, y1, c); putpixel(b, x, y2, c); }
    for (y = y1; y <= y2; y += 2) { putpixel(b, x1, y, c); putpixel(b, x2, y, c); }
}

static int inside(const DIALOG *d, int x, int y) { return x >= d->x && y >= d->y && x < d->x + d->w && y < d->y + d->h; }

/* a vertical scroll bar at the right of an object: the part shown, out of total */
static void draw_scrollbar(BITMAP *b, const DIALOG *d, int total, int shown, int offset, int fg, int bg)
{
    int x = d->x + d->w - 12, y = d->y + 1, h = d->h - 2, len, pos;
    rectfill(b, x, y, x + 10, y + h - 1, bg);
    vline(b, x - 1, d->y, d->y + d->h - 1, fg);
    if (total <= 0 || shown >= total) return;
    len = h * shown / total;
    if (len < 6) len = 6;
    pos = (h - len) * offset / (total - shown);
    rectfill(b, x + 2, y + pos + 1, x + 8, y + pos + len - 2, fg);
}

void _draw_scrollable_frame(DIALOG *d, int listsize, int offset, int height, int fg_color, int bg)
{
    BITMAP *b = gui_get_screen();
    rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg_color);
    if (listsize > height) draw_scrollbar(b, d, listsize, height, offset, fg_color, bg);
}

/* ---- the standard objects ------------------------------------------------------------ */

int d_yield_proc(int msg, DIALOG *d, int c)
{
    (void)d; (void)c;
    if (msg == MSG_IDLE) rest(1);
    return D_O_K;
}

int d_clear_proc(int msg, DIALOG *d, int c)
{
    (void)c;
    if (msg == MSG_DRAW) clear_to_color(gui_get_screen(), d->bg);
    return D_O_K;
}

int d_box_proc(int msg, DIALOG *d, int c)
{
    (void)c;
    if (msg == MSG_DRAW) {
        BITMAP *b = gui_get_screen();
        rectfill(b, d->x + 1, d->y + 1, d->x + d->w - 2, d->y + d->h - 2, d->bg);
        rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg_of(d));
    }
    return D_O_K;
}

int d_shadow_box_proc(int msg, DIALOG *d, int c)
{
    (void)c;
    if (msg == MSG_DRAW) {
        BITMAP *b = gui_get_screen();
        int fg = fg_of(d);
        rectfill(b, d->x + 1, d->y + 1, d->x + d->w - 3, d->y + d->h - 3, d->bg);
        rect(b, d->x, d->y, d->x + d->w - 2, d->y + d->h - 2, fg);
        vline(b, d->x + d->w - 1, d->y + 1, d->y + d->h - 1, fg);
        hline(b, d->x + 1, d->y + d->h - 1, d->x + d->w - 1, fg);
    }
    return D_O_K;
}

int d_bitmap_proc(int msg, DIALOG *d, int c)
{
    (void)c;
    if (msg == MSG_DRAW && d->dp)
        blit((BITMAP *)d->dp, gui_get_screen(), 0, 0, d->x, d->y, d->w, d->h);
    return D_O_K;
}

static int text_proc(int msg, DIALOG *d, int where)
{
    if (msg == MSG_DRAW && d->dp) {
        FONT *old = font;
        int x = where == 0 ? d->x : where == 1 ? d->x + d->w / 2 : d->x + d->w - gui_strlen((const char *)d->dp);
        if (d->dp2) font = (FONT *)d->dp2;
        gui_textout_ex(gui_get_screen(), (const char *)d->dp, x, d->y, fg_of(d), d->bg, where == 1);
        font = old;
    }
    return D_O_K;
}

int d_text_proc(int msg, DIALOG *d, int c) { (void)c; return text_proc(msg, d, 0); }
int d_ctext_proc(int msg, DIALOG *d, int c) { (void)c; return text_proc(msg, d, 1); }
int d_rtext_proc(int msg, DIALOG *d, int c) { (void)c; return text_proc(msg, d, 2); }

/* follow the button while it is held: the object shows pressed while the
 * pointer is over it; selected (or not) as the button goes up over it */
static int track_button(DIALOG *d)
{
    int state1 = d->flags & D_SELECTED, swap = (d->flags & D_EXIT) ? 0 : state1, state2;
    while (gui_mouse_b()) {
        state2 = inside(d, gui_mouse_x(), gui_mouse_y());
        if (swap) state2 = !state2;
        if ((state1 && !state2) || (state2 && !state1)) {
            d->flags ^= D_SELECTED;
            state1 = d->flags & D_SELECTED;
            object_message(d, MSG_DRAW, 0);
        }
        broadcast_dialog_message(MSG_IDLE, 0);
        rest(1);
    }
    if ((d->flags & D_SELECTED) && (d->flags & D_EXIT)) { d->flags ^= D_SELECTED; return D_CLOSE; }
    return D_O_K;
}

int d_button_proc(int msg, DIALOG *d, int c)
{
    BITMAP *b = gui_get_screen();
    (void)c;
    switch (msg) {
    case MSG_DRAW: {
        int fg = fg_of(d), bg = d->bg, off = 0;
        if (d->flags & D_SELECTED) { int t = fg; fg = bg; bg = t; off = 1; }
        rectfill(b, d->x + 1 + off, d->y + 1 + off, d->x + d->w - 3 + off, d->y + d->h - 3 + off, bg);
        rect(b, d->x + off, d->y + off, d->x + d->w - 2 + off, d->y + d->h - 2 + off, fg);
        if (!(d->flags & D_SELECTED)) {
            vline(b, d->x + d->w - 1, d->y + 1, d->y + d->h - 1, fg_of(d));
            hline(b, d->x + 1, d->y + d->h - 1, d->x + d->w - 1, fg_of(d));
        }
        if (d->dp)
            gui_textout_ex(b, (const char *)d->dp, d->x + d->w / 2 + off, d->y + d->h / 2 - text_height(font) / 2 + off,
                           fg, -1, TRUE);
        if ((d->flags & D_GOTFOCUS) && d->w > 8 && d->h > 8)
            dotted_rect(b, d->x + 2 + off, d->y + 2 + off, d->x + d->w - 5 + off, d->y + d->h - 5 + off, fg);
        break;
    }
    case MSG_WANTFOCUS:
        return D_WANTFOCUS;
    case MSG_KEY:
        if (d->flags & D_EXIT) return D_CLOSE;
        d->flags ^= D_SELECTED;
        object_message(d, MSG_DRAW, 0);
        break;
    case MSG_CLICK:
        return track_button(d);
    }
    return D_O_K;
}

int d_check_proc(int msg, DIALOG *d, int c)
{
    if (msg == MSG_DRAW) {
        BITMAP *b = gui_get_screen();
        int fg = fg_of(d), th = text_height(font), box = d->h, x = d->x, bx, by = d->y;
        rectfill(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, d->bg);
        if (d->d1) { bx = x; x += box + box / 2; }
        else bx = d->x + (d->dp ? gui_strlen((const char *)d->dp) + box / 2 : 0);
        if (d->dp) gui_textout_ex(b, (const char *)d->dp, x, d->y + (d->h - th) / 2, fg, d->bg, FALSE);
        rect(b, bx, by, bx + box - 1, by + box - 1, fg);
        if (d->flags & D_SELECTED) {
            line(b, bx, by, bx + box - 1, by + box - 1, fg);
            line(b, bx, by + box - 1, bx + box - 1, by, fg);
        }
        if (d->flags & D_GOTFOCUS) dotted_rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg);
        return D_O_K;
    }
    return d_button_proc(msg, d, c);
}

int d_radio_proc(int msg, DIALOG *d, int c)
{
    BITMAP *b = gui_get_screen();
    switch (msg) {
    case MSG_DRAW: {
        int fg = fg_of(d), th = text_height(font), r = d->h / 2;
        rectfill(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, d->bg);
        if (d->dp) gui_textout_ex(b, (const char *)d->dp, d->x + d->h + r, d->y + (d->h - th) / 2, fg, d->bg, FALSE);
        if (d->d2 == 1) {
            rect(b, d->x, d->y, d->x + d->h - 1, d->y + d->h - 1, fg);
            if (d->flags & D_SELECTED) rectfill(b, d->x + 2, d->y + 2, d->x + d->h - 3, d->y + d->h - 3, fg);
        } else {
            circle(b, d->x + r, d->y + r, r > 0 ? r - 1 : 0, fg);
            if ((d->flags & D_SELECTED) && r > 2) circlefill(b, d->x + r, d->y + r, r - 3, fg);
        }
        if (d->flags & D_GOTFOCUS) dotted_rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg);
        break;
    }
    case MSG_RADIO:
        if (c == d->d1 && (d->flags & D_SELECTED)) { d->flags &= ~D_SELECTED; object_message(d, MSG_DRAW, 0); }
        break;
    case MSG_CLICK:
        while (gui_mouse_b()) { broadcast_dialog_message(MSG_IDLE, 0); rest(1); }
        if (!inside(d, gui_mouse_x(), gui_mouse_y())) break;
        /* fall through */
    case MSG_KEY:
        if (d->flags & D_SELECTED) return (d->flags & D_EXIT) ? D_CLOSE : D_O_K;
        broadcast_dialog_message(MSG_RADIO, d->d1);
        d->flags |= D_SELECTED;
        object_message(d, MSG_DRAW, 0);
        return (d->flags & D_EXIT) ? D_CLOSE : D_O_K;
    case MSG_WANTFOCUS:
        return D_WANTFOCUS;
    }
    return D_O_K;
}

int d_icon_proc(int msg, DIALOG *d, int c)
{
    if (msg == MSG_DRAW) {
        BITMAP *b = gui_get_screen(), *img = (BITMAP *)d->dp;
        int off = (d->flags & D_SELECTED) ? 1 : 0;
        if ((d->flags & D_SELECTED) && d->dp2) { img = (BITMAP *)d->dp2; off = 0; }
        if ((d->flags & D_DISABLED) && d->dp3) img = (BITMAP *)d->dp3;
        rectfill(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, d->bg);
        if (img) stretch_sprite(b, img, d->x + off, d->y + off, d->w - off, d->h - off);
        if (d->flags & D_GOTFOCUS) dotted_rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, d->fg);
        return D_O_K;
    }
    return d_button_proc(msg, d, c);
}

int d_keyboard_proc(int msg, DIALOG *d, int c)
{
    int r = D_O_K;
    switch (msg) {
    case MSG_START:
        d->w = d->h = 0;
        break;
    case MSG_XCHAR:
        if ((c >> 8) != d->d1 && (c >> 8) != d->d2) break;
        r |= D_USED_CHAR;
        /* fall through */
    case MSG_KEY:
        if (d->dp) r |= ((int (*)(void))d->dp)();
        break;
    }
    return r;
}

/* ---- d_edit_proc: dp the text, d1 its most characters, d2 the cursor ------------------ */

int d_edit_proc(int msg, DIALOG *d, int c)
{
    char *s = (char *)d->dp;
    int len = s ? (int)strlen(s) : 0;
    if (!s) return D_O_K;
    if (d->d2 > len) d->d2 = len;
    if (d->d2 < 0) d->d2 = 0;
    switch (msg) {
    case MSG_START:
        d->d2 = len;
        break;
    case MSG_DRAW: {
        BITMAP *b = gui_get_screen();
        int fg = fg_of(d), first = 0, x = d->x, i;
        char one[2] = { 0, 0 };
        /* scroll so the cursor shows */
        for (;;) {
            int w = 0;
            for (i = first; i < d->d2; i++) { one[0] = s[i]; w += text_length(font, one); }
            one[0] = ' ';
            if (w + text_length(font, one) <= d->w || first >= d->d2) break;
            first++;
        }
        rectfill(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, d->bg);
        for (i = first; i <= len; i++) {
            int cw, cursor = i == d->d2 && (d->flags & D_GOTFOCUS);
            one[0] = i < len ? s[i] : ' ';
            cw = text_length(font, one);
            if (x + cw > d->x + d->w) break;
            textout_ex(b, font, one, x, d->y, cursor ? d->bg : fg, cursor ? fg : d->bg);
            x += cw;
        }
        break;
    }
    case MSG_CLICK: {
        int x = d->x, i, mx = gui_mouse_x();
        char one[2] = { 0, 0 };
        for (i = 0; i < len; i++) {
            one[0] = s[i];
            x += text_length(font, one);
            if (x > mx) break;
        }
        d->d2 = i;
        object_message(d, MSG_DRAW, 0);
        while (gui_mouse_b()) { broadcast_dialog_message(MSG_IDLE, 0); rest(1); }
        break;
    }
    case MSG_WANTFOCUS:
    case MSG_LOSTFOCUS:
    case MSG_KEY:
        return D_WANTFOCUS;
    case MSG_GOTFOCUS:
        return D_REDRAWME;
    case MSG_CHAR: {
        int sc = c >> 8;
        switch (sc) {
        case KEY_LEFT: if (d->d2 > 0) d->d2--; break;
        case KEY_RIGHT: if (d->d2 < len) d->d2++; break;
        case KEY_HOME: d->d2 = 0; break;
        case KEY_END: d->d2 = len; break;
        case KEY_DEL: if (d->d2 < len) memmove(s + d->d2, s + d->d2 + 1, (size_t)(len - d->d2)); break;
        case KEY_BACKSPACE:
            if (d->d2 > 0) { memmove(s + d->d2 - 1, s + d->d2, (size_t)(len - d->d2 + 1)); d->d2--; }
            break;
        case KEY_ENTER: case KEY_ENTER_PAD:
            if (d->flags & D_EXIT) { object_message(d, MSG_DRAW, 0); return D_CLOSE; }
            return D_O_K;
        case KEY_TAB:
            return D_O_K;
        default:
            return D_O_K;               /* a character: MSG_UCHAR */
        }
        object_message(d, MSG_DRAW, 0);
        return D_USED_CHAR;
    }
    case MSG_UCHAR:
        if ((c & 255) >= 32 && c < 256 && c != 127) {
            if (len < d->d1) {
                memmove(s + d->d2 + 1, s + d->d2, (size_t)(len - d->d2 + 1));
                s[d->d2++] = (char)c;
                object_message(d, MSG_DRAW, 0);
            }
            return D_USED_CHAR;
        }
        break;
    }
    return D_O_K;
}

/* ---- d_list_proc: dp a getter (char *(*)(int index, int *size)), d1 the
 *      selection, d2 the first row shown, dp2 an optional char[] of marks --------------- */

typedef char *(*a4_list_getter)(int index, int *list_size);

static int list_size(DIALOG *d) { int n = 0; if (d->dp) ((a4_list_getter)d->dp)(-1, &n); return n; }
static int list_rows(DIALOG *d) { int th = text_height(font); return th > 0 ? (d->h - 4) / th : 1; }

static void list_fix(DIALOG *d, int n)
{
    int rows = list_rows(d);
    if (d->d1 >= n) d->d1 = n - 1;
    if (d->d1 < 0) d->d1 = 0;
    if (d->d1 < d->d2) d->d2 = d->d1;
    if (d->d1 >= d->d2 + rows) d->d2 = d->d1 - rows + 1;
    if (d->d2 > n - rows) d->d2 = n - rows;
    if (d->d2 < 0) d->d2 = 0;
}

static void list_draw(DIALOG *d)
{
    BITMAP *b = gui_get_screen();
    int n = list_size(d), rows = list_rows(d), th = text_height(font), fg = fg_of(d), i;
    int bar = n > rows, wx = d->x + d->w - (bar ? 13 : 1);
    char *marks = (char *)d->dp2;
    int cl, ct, cr, cb;
    get_clip_rect(b, &cl, &ct, &cr, &cb);
    rectfill(b, d->x + 1, d->y + 1, wx - 1, d->y + d->h - 2, d->bg);
    rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg);
    set_clip_rect(b, d->x + 1, d->y + 1, wx - 1, d->y + d->h - 2);
    for (i = 0; i < rows && d->d2 + i < n; i++) {
        int idx = d->d2 + i, sel = idx == d->d1 || (marks && marks[idx]);
        int y = d->y + 2 + i * th;
        const char *text = ((a4_list_getter)d->dp)(idx, NULL);
        if (sel) rectfill(b, d->x + 1, y, wx - 1, y + th - 1, fg);
        if (text) textout_ex(b, font, text, d->x + 3, y, sel ? d->bg : fg, -1);
        if (idx == d->d1 && (d->flags & D_GOTFOCUS)) dotted_rect(b, d->x + 1, y, wx - 1, y + th - 1, sel ? d->bg : fg);
    }
    set_clip_rect(b, cl, ct, cr, cb);
    if (bar) draw_scrollbar(b, d, n, rows, d->d2, fg, d->bg);
}

int d_list_proc(int msg, DIALOG *d, int c)
{
    int n = list_size(d), rows;
    switch (msg) {
    case MSG_START:
        list_fix(d, n);
        break;
    case MSG_DRAW:
        list_draw(d);
        break;
    case MSG_CLICK: {
        int th = text_height(font), last = -1;
        rows = list_rows(d);
        if (n > rows && gui_mouse_x() >= d->x + d->w - 13) {
            /* the scroll bar: page towards the pointer */
            int mid = d->y + d->h * (d->d2 + rows / 2) / (n ? n : 1);
            d->d2 += gui_mouse_y() < mid ? -rows : rows;
            if (d->d1 < d->d2) d->d1 = d->d2;
            if (d->d1 >= d->d2 + rows) d->d1 = d->d2 + rows - 1;
            list_fix(d, n);
            object_message(d, MSG_DRAW, 0);
            while (gui_mouse_b()) { broadcast_dialog_message(MSG_IDLE, 0); rest(1); }
            break;
        }
        do {
            int row = (gui_mouse_y() - d->y - 2) / (th > 0 ? th : 1);
            int idx = d->d2 + (row < 0 ? -1 : row);
            if (row >= rows) idx = d->d2 + rows;
            if (idx < 0) idx = 0;
            if (idx >= n) idx = n - 1;
            if (idx != last && n > 0) {
                d->d1 = idx;
                if (d->dp2 && (key_shifts & KB_CTRL_FLAG) && last < 0) ((char *)d->dp2)[idx] ^= 1;
                list_fix(d, n);
                object_message(d, MSG_DRAW, 0);
                last = idx;
            }
            broadcast_dialog_message(MSG_IDLE, 0);
            rest(1);
        } while (gui_mouse_b());
        break;
    }
    case MSG_DCLICK:
        if (d->flags & D_EXIT) {
            int th = text_height(font), row = (gui_mouse_y() - d->y - 2) / (th > 0 ? th : 1);
            if (d->d2 + row == d->d1) return D_CLOSE;
        }
        break;
    case MSG_WHEEL:
        d->d2 -= c;
        rows = list_rows(d);
        if (d->d2 > n - rows) d->d2 = n - rows;
        if (d->d2 < 0) d->d2 = 0;
        if (d->d1 < d->d2) d->d1 = d->d2;
        if (d->d1 >= d->d2 + rows) d->d1 = d->d2 + rows - 1;
        object_message(d, MSG_DRAW, 0);
        break;
    case MSG_KEY:
        if (d->flags & D_EXIT) return D_CLOSE;
        break;
    case MSG_WANTFOCUS:
        return D_WANTFOCUS;
    case MSG_GOTFOCUS:
    case MSG_LOSTFOCUS:
        return D_REDRAWME;
    case MSG_CHAR: {
        int sc = c >> 8;
        rows = list_rows(d);
        switch (sc) {
        case KEY_UP: d->d1--; break;
        case KEY_DOWN: d->d1++; break;
        case KEY_HOME: d->d1 = 0; break;
        case KEY_END: d->d1 = n - 1; break;
        case KEY_PGUP: d->d1 -= rows - 1; break;
        case KEY_PGDN: d->d1 += rows - 1; break;
        case KEY_ENTER: case KEY_ENTER_PAD:
            return (d->flags & D_EXIT) ? (D_CLOSE | D_USED_CHAR) : D_O_K;
        default:
            return D_O_K;
        }
        list_fix(d, n);
        object_message(d, MSG_DRAW, 0);
        return D_USED_CHAR;
    }
    }
    return D_O_K;
}

/* like d_list_proc; a typed letter jumps to the next item starting with it */
int d_text_list_proc(int msg, DIALOG *d, int c)
{
    if (msg == MSG_UCHAR && c > 32 && c < 256) {
        int n = list_size(d), i;
        for (i = 1; i <= n; i++) {
            int idx = (d->d1 + i) % n;
            const char *t = ((a4_list_getter)d->dp)(idx, NULL);
            if (t && tolower((unsigned char)t[0]) == tolower(c)) {
                d->d1 = idx;
                list_fix(d, n);
                object_message(d, MSG_DRAW, 0);
                return D_USED_CHAR;
            }
        }
        return D_USED_CHAR;
    }
    return d_list_proc(msg, d, c);
}

/* ---- d_textbox_proc: dp the text (wrapped), d1 its lines, d2 the first shown -------- */

/* the line breaks of dp for a width: calls emit(start, len) for each line;
 * returns the number of lines */
static int wrap_text(const char *s, int width, void (*emit)(void *, const char *, int, int), void *ctx)
{
    int lines = 0;
    char one[2] = { 0, 0 };
    while (s && *s) {
        int w = 0, n = 0, brk = -1;
        while (s[n] && s[n] != '\n') {
            one[0] = s[n];
            w += text_length(font, one);
            if (w > width && n > 0) break;
            if (s[n] == ' ') brk = n;
            n++;
        }
        if (s[n] && s[n] != '\n' && brk > 0) n = brk;
        if (emit) emit(ctx, s, n, lines);
        lines++;
        s += n;
        if (*s == '\n' || *s == ' ') s++;
    }
    return lines;
}

struct tb_ctx { BITMAP *b; DIALOG *d; int fg, rows; };

static void tb_emit(void *p, const char *s, int n, int line)
{
    struct tb_ctx *t = (struct tb_ctx *)p;
    char buf[256];
    int row = line - t->d->d2;
    if (row < 0 || row >= t->rows) return;
    if (n > (int)sizeof(buf) - 1) n = (int)sizeof(buf) - 1;
    memcpy(buf, s, (size_t)n);
    buf[n] = 0;
    textout_ex(t->b, font, buf, t->d->x + 3, t->d->y + 2 + row * text_height(font), t->fg, -1);
}

int d_textbox_proc(int msg, DIALOG *d, int c)
{
    int rows = list_rows(d);
    switch (msg) {
    case MSG_START:
        d->d1 = wrap_text((const char *)d->dp, d->w - 18, NULL, NULL);
        if (d->d2 > d->d1 - rows) d->d2 = d->d1 - rows;
        if (d->d2 < 0) d->d2 = 0;
        break;
    case MSG_DRAW: {
        BITMAP *b = gui_get_screen();
        struct tb_ctx t;
        int bar;
        d->d1 = wrap_text((const char *)d->dp, d->w - 18, NULL, NULL);
        bar = d->d1 > rows;
        rectfill(b, d->x + 1, d->y + 1, d->x + d->w - 2, d->y + d->h - 2, d->bg);
        rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg_of(d));
        t.b = b; t.d = d; t.fg = fg_of(d); t.rows = rows;
        wrap_text((const char *)d->dp, d->w - 18, tb_emit, &t);
        if (bar) draw_scrollbar(b, d, d->d1, rows, d->d2, fg_of(d), d->bg);
        break;
    }
    case MSG_WHEEL:
        c = -c;
        /* fall through */
    case MSG_CHAR: {
        int old = d->d2, sc = msg == MSG_CHAR ? c >> 8 : 0;
        if (msg == MSG_WHEEL) d->d2 += c;
        else if (sc == KEY_UP) d->d2--;
        else if (sc == KEY_DOWN) d->d2++;
        else if (sc == KEY_PGUP) d->d2 -= rows - 1;
        else if (sc == KEY_PGDN) d->d2 += rows - 1;
        else if (sc == KEY_HOME) d->d2 = 0;
        else if (sc == KEY_END) d->d2 = d->d1;
        else return D_O_K;
        if (d->d2 > d->d1 - rows) d->d2 = d->d1 - rows;
        if (d->d2 < 0) d->d2 = 0;
        if (d->d2 != old) object_message(d, MSG_DRAW, 0);
        return msg == MSG_CHAR ? D_USED_CHAR : D_O_K;
    }
    case MSG_WANTFOCUS:
        return d->d1 > rows ? D_WANTFOCUS : D_O_K;
    }
    return D_O_K;
}

/* ---- d_slider_proc: d1 the most, d2 the value, dp a handle bitmap, dp2 a
 *      callback int (*)(void *dp3, int d2) called as the value changes ------------------ */

static int slider_set(DIALOG *d, int v)
{
    int r = D_O_K;
    if (v < 0) v = 0;
    if (v > d->d1) v = d->d1;
    if (v == d->d2) return D_O_K;
    d->d2 = v;
    if (d->dp2) r = ((int (*)(void *, int))d->dp2)(d->dp3, d->d2);
    object_message(d, MSG_DRAW, 0);
    return r;
}

int d_slider_proc(int msg, DIALOG *d, int c)
{
    int vert = d->h > d->w;
    switch (msg) {
    case MSG_DRAW: {
        BITMAP *b = gui_get_screen(), *hb = (BITMAP *)d->dp;
        int fg = fg_of(d), hs = hb ? (vert ? hb->h : hb->w) : 8, span = (vert ? d->h : d->w) - hs;
        int pos = d->d1 > 0 ? span * d->d2 / d->d1 : 0;
        rectfill(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, d->bg);
        if (vert) {
            int hy = d->y + d->h - hs - pos;
            vline(b, d->x + d->w / 2, d->y, d->y + d->h - 1, fg);
            if (hb) draw_sprite(b, hb, d->x + (d->w - hb->w) / 2, hy);
            else rectfill(b, d->x, hy, d->x + d->w - 1, hy + hs - 1, fg);
        } else {
            int hx = d->x + pos;
            hline(b, d->x, d->y + d->h / 2, d->x + d->w - 1, fg);
            if (hb) draw_sprite(b, hb, hx, d->y + (d->h - hb->h) / 2);
            else rectfill(b, hx, d->y, hx + hs - 1, d->y + d->h - 1, fg);
        }
        if (d->flags & D_GOTFOCUS) dotted_rect(b, d->x, d->y, d->x + d->w - 1, d->y + d->h - 1, fg);
        break;
    }
    case MSG_WANTFOCUS:
        return D_WANTFOCUS;
    case MSG_GOTFOCUS:
    case MSG_LOSTFOCUS:
        return D_REDRAWME;
    case MSG_CLICK: {
        int r = D_O_K;
        do {
            int span = vert ? d->h : d->w, p = vert ? d->y + d->h - 1 - gui_mouse_y() : gui_mouse_x() - d->x;
            r |= slider_set(d, span > 1 ? (p * d->d1 + (span - 1) / 2) / (span - 1) : 0);
            broadcast_dialog_message(MSG_IDLE, 0);
            rest(1);
        } while (gui_mouse_b());
        return r;
    }
    case MSG_WHEEL:
        return slider_set(d, d->d2 + c);
    case MSG_CHAR: {
        int sc = c >> 8, step = d->d1 >= 10 ? d->d1 / 10 : 1, v = d->d2, r;
        if (sc == KEY_LEFT || sc == KEY_DOWN) v--;
        else if (sc == KEY_RIGHT || sc == KEY_UP) v++;
        else if (sc == KEY_PGDN) v -= step;
        else if (sc == KEY_PGUP) v += step;
        else if (sc == KEY_HOME) v = 0;
        else if (sc == KEY_END) v = d->d1;
        else return D_O_K;
        r = slider_set(d, v);
        return r | D_USED_CHAR;
    }
    }
    return D_O_K;
}
