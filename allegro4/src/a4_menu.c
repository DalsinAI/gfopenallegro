/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Allegro 4's menus: do_menu, init_menu/update_menu/shutdown_menu and the
 * d_menu_proc menu bar, written from the Allegro 4 documentation. Like the
 * dialog engine (a4_gui.c) this is the game's side (liballeg.a): the items'
 * procs are the game's, and it draws through allegro4.library's calls.
 *
 * A menu is a list of MENU items ending with a NULL text. "" is a separator,
 * "&x" marks the shortcut letter and "\t" starts text drawn on the right.
 * An item with a child opens that menu; any other item is chosen, its proc
 * is called (with active_menu pointing at it) and every menu closes.
 *
 * Also here: the hooks Allegro's internal header gives GUI code,
 * get_config_text and the screen mode selector.
 */
#include <allegro.h>
#include <ctype.h>

MENU *active_menu;
int gui_mouse_focus = TRUE;
int (*gui_shadow_box_proc)(int msg, DIALOG *d, int c) = d_shadow_box_proc;
int (*gui_ctext_proc)(int msg, DIALOG *d, int c) = d_ctext_proc;
int (*gui_button_proc)(int msg, DIALOG *d, int c) = d_button_proc;
int (*gui_edit_proc)(int msg, DIALOG *d, int c) = d_edit_proc;
int (*gui_list_proc)(int msg, DIALOG *d, int c) = d_list_proc;
int (*gui_text_list_proc)(int msg, DIALOG *d, int c) = d_text_list_proc;

const char *get_config_text(const char *msg) { return msg; }

/* ---- drawing ----------------------------------------------------------------------- */

static BITMAP *menu_screen(void) { return gui_get_screen(); }

static void def_draw_menu(int x, int y, int w, int h)
{
    BITMAP *s = menu_screen();
    rect(s, x, y, x + w - 2, y + h - 2, gui_fg_color);
    vline(s, x + w - 1, y + 1, y + h - 1, gui_fg_color);     /* the shadow */
    hline(s, x + 1, y + h - 1, x + w - 1, gui_fg_color);
}

static void def_draw_menu_item(MENU *m, int x, int y, int w, int h, int bar, int sel)
{
    BITMAP *s = menu_screen();
    int fg, bg, th = text_height(font), i;
    char left[256];
    const char *tab;

    if (m->flags & D_DISABLED) { fg = gui_mg_color; bg = gui_bg_color; if (sel) { fg = gui_bg_color; bg = gui_mg_color; } }
    else if (sel) { fg = gui_bg_color; bg = gui_fg_color; }
    else { fg = gui_fg_color; bg = gui_bg_color; }
    rectfill(s, x, y, x + w - 1, y + h - 1, bg);

    if (!m->text[0]) {                                      /* a separator */
        hline(s, x, y + h / 2, x + w - 1, gui_fg_color);
        return;
    }
    tab = strchr(m->text, '\t');
    i = tab ? (int)(tab - m->text) : (int)strlen(m->text);
    if (i > (int)sizeof(left) - 1) i = sizeof(left) - 1;
    memcpy(left, m->text, i); left[i] = 0;
    gui_textout_ex(s, left, x + 8, y + (h - th) / 2, fg, -1, FALSE);
    if (tab) gui_textout_ex(s, tab + 1, x + w - gui_strlen(tab + 1) - 8, y + (h - th) / 2, fg, -1, FALSE);
    if (m->child && !bar) {                                 /* an arrow to the child */
        int cy = y + h / 2, ax = x + w - 7, k;
        for (k = 0; k < 4; k++) vline(s, ax + k, cy - 3 + k, cy + 3 - k, fg);
    }
    if (m->flags & D_SELECTED) {                            /* a tick */
        int ty = y + h / 2;
        line(s, x + 1, ty, x + 3, ty + 2, fg);
        line(s, x + 3, ty + 2, x + 6, ty - 3, fg);
    }
}

void (*gui_menu_draw_menu)(int x, int y, int w, int h) = def_draw_menu;
void (*gui_menu_draw_menu_item)(MENU *m, int x, int y, int w, int h, int bar, int sel) = def_draw_menu_item;

/* ---- layout ------------------------------------------------------------------------- */

struct MENU_PLAYER {
    MENU *menu;
    int bar;                    /* a menu bar (items across) or a drop-down (items down) */
    int size;                   /* items */
    int x, y, w, h;             /* the whole menu, frame included */
    int sel;                    /* the highlighted item, -1 for none */
    BITMAP *under;              /* what the drop-down covers */
    int drawn;
    int mouse_b;                /* buttons at the last update */
    int pressed;                /* a button went down since the menu opened */
    int ret;                    /* the chosen item of this menu, -1 */
    int done;
    MENU *chosen;               /* the item chosen anywhere in the tree */
    struct MENU_PLAYER *parent, *child;
};

static int item_h(void) { return text_height(font) + 4; }

static int item_w(const MENU *m)
{
    const char *tab = strchr(m->text, '\t');
    char left[256];
    int i, w;
    if (!tab) return gui_strlen(m->text);
    i = (int)(tab - m->text);
    if (i > (int)sizeof(left) - 1) i = sizeof(left) - 1;
    memcpy(left, m->text, i); left[i] = 0;
    w = gui_strlen(left) + 16 + gui_strlen(tab + 1);
    return w;
}

static void layout(MENU_PLAYER *p)
{
    BITMAP *s = menu_screen();
    int i, w = 0;
    for (p->size = 0; p->menu[p->size].text; p->size++) ;
    if (p->bar) {
        for (i = 0; i < p->size; i++) w += item_w(&p->menu[i]) + 16;
        p->w = w + 2; p->h = item_h() + 2;
    } else {
        for (i = 0; i < p->size; i++) if (item_w(&p->menu[i]) > w) w = item_w(&p->menu[i]);
        p->w = w + 28; p->h = p->size * item_h() + 3;
        if (s) {                                            /* keep the drop-down on the screen */
            if (p->x + p->w > s->w) p->x = s->w - p->w;
            if (p->y + p->h > s->h) p->y = s->h - p->h;
            if (p->x < 0) p->x = 0;
            if (p->y < 0) p->y = 0;
        }
    }
}

/* the rectangle of item i */
static void item_rect(const MENU_PLAYER *p, int i, int *x, int *y, int *w, int *h)
{
    int k;
    if (p->bar) {
        *x = p->x + 1;
        for (k = 0; k < i; k++) *x += item_w(&p->menu[k]) + 16;
        *y = p->y + 1; *w = item_w(&p->menu[i]) + 16; *h = item_h();
    } else {
        *x = p->x + 1; *y = p->y + 1 + i * item_h(); *w = p->w - 3; *h = item_h();
    }
}

static int item_at(const MENU_PLAYER *p, int mx, int my)
{
    int i, x, y, w, h;
    for (i = 0; i < p->size; i++) {
        item_rect(p, i, &x, &y, &w, &h);
        if (mx >= x && mx < x + w && my >= y && my < y + h) return i;
    }
    return -1;
}

static int inside(const MENU_PLAYER *p, int mx, int my)
{
    return mx >= p->x && my >= p->y && mx < p->x + p->w && my < p->y + p->h;
}

static int is_sep(const MENU *m) { return !m->text[0]; }

static void draw_item(MENU_PLAYER *p, int i)
{
    int x, y, w, h;
    item_rect(p, i, &x, &y, &w, &h);
    gui_menu_draw_menu_item(&p->menu[i], x, y, w, h, p->bar, i == p->sel);
}

static void draw_menu(MENU_PLAYER *p)
{
    int i;
    BITMAP *s = menu_screen();
    if (!s) return;
    scare_mouse();
    if (p->bar) rectfill(s, p->x, p->y, p->x + p->w - 1, p->y + p->h - 1, gui_bg_color);
    else gui_menu_draw_menu(p->x, p->y, p->w, p->h);
    for (i = 0; i < p->size; i++) draw_item(p, i);
    unscare_mouse();
    p->drawn = 1;
}

static void set_sel(MENU_PLAYER *p, int sel)
{
    int old = p->sel;
    if (sel == old) return;
    p->sel = sel;
    scare_mouse();
    if (old >= 0) draw_item(p, old);
    if (sel >= 0) draw_item(p, sel);
    unscare_mouse();
}

/* ---- the players --------------------------------------------------------------------- */

static MENU_PLAYER *new_player(MENU *menu, int bar, int x, int y, MENU_PLAYER *parent)
{
    MENU_PLAYER *p = (MENU_PLAYER *)calloc(1, sizeof(*p));
    BITMAP *s = menu_screen();
    if (!p) return NULL;
    p->menu = menu; p->bar = bar; p->x = x; p->y = y; p->sel = -1; p->ret = -1;
    p->parent = parent;
    p->mouse_b = gui_mouse_b();
    layout(p);
    if (!bar && s) {
        p->under = create_bitmap(p->w, p->h);
        if (p->under) { scare_mouse(); blit(s, p->under, p->x, p->y, 0, 0, p->w, p->h); unscare_mouse(); }
    }
    return p;
}

static void close_player(MENU_PLAYER *p)
{
    BITMAP *s = menu_screen();
    if (!p) return;
    close_player(p->child);
    p->child = NULL;
    if (p->under && s) { scare_mouse(); blit(p->under, s, 0, 0, p->x, p->y, p->w, p->h); unscare_mouse(); }
    if (p->under) destroy_bitmap(p->under);
    if (p->parent && p->parent->child == p) p->parent->child = NULL;
    free(p);
}

static void open_child(MENU_PLAYER *p)
{
    int x, y, w, h;
    MENU *m;
    if (p->sel < 0 || p->child) return;
    m = &p->menu[p->sel];
    if (!m->child || (m->flags & D_DISABLED)) return;
    item_rect(p, p->sel, &x, &y, &w, &h);
    if (p->bar) p->child = new_player(m->child, FALSE, x, y + h, p);
    else p->child = new_player(m->child, FALSE, x + w, y - 1, p);
    if (p->child) {
        p->child->pressed = p->pressed;
        draw_menu(p->child);
    }
}

static MENU_PLAYER *root_of(MENU_PLAYER *p) { while (p->parent) p = p->parent; return p; }

/* an item is picked: a child opens, anything else ends the whole menu */
static void pick(MENU_PLAYER *p, int i)
{
    MENU_PLAYER *r;
    if (i < 0 || i >= p->size || is_sep(&p->menu[i])) return;
    set_sel(p, i);
    if (p->menu[i].child) {
        if (!p->child) open_child(p);
        if (p->child) {                                     /* the child's first item */
            int k;
            for (k = 0; k < p->child->size && is_sep(&p->child->menu[k]); k++) ;
            if (k < p->child->size) set_sel(p->child, k);
        }
        return;
    }
    if (p->menu[i].flags & D_DISABLED) return;
    p->ret = i;
    r = root_of(p);
    r->chosen = &p->menu[i];
    r->done = 1;
    if (r != p) r->ret = r->sel;                            /* the root returns its own open item */
}

static int step(const MENU_PLAYER *p, int from, int dir)
{
    int i = from, n;
    for (n = 0; n < p->size; n++) {
        i += dir;
        if (i < 0) i = p->size - 1;
        if (i >= p->size) i = 0;
        if (!is_sep(&p->menu[i])) return i;
    }
    return from;
}

static int shortcut(const MENU *m, int c)
{
    const char *t = m->text;
    for (; t && *t; t++) {
        if (*t == '&') {
            if (t[1] == '&') { t++; continue; }
            return t[1] && tolower((unsigned char)t[1]) == tolower(c);
        }
    }
    return 0;
}

/* the open menu that has the keyboard: the deepest one */
static MENU_PLAYER *deepest(MENU_PLAYER *p) { while (p->child) p = p->child; return p; }

static void key_event(MENU_PLAYER *root, int a, int sc)
{
    MENU_PLAYER *p = deepest(root);
    int across = p->bar, i;

    if (sc == KEY_ESC) {
        if (p->parent) { MENU_PLAYER *q = p->parent; close_player(p); if (q->bar) { set_sel(q, q->sel); } }
        else root->done = 1;
        return;
    }
    if ((across && (sc == KEY_LEFT || sc == KEY_RIGHT)) || (!across && (sc == KEY_UP || sc == KEY_DOWN))) {
        set_sel(p, step(p, p->sel < 0 ? (sc == KEY_LEFT || sc == KEY_UP ? 0 : -1) : p->sel,
                        (sc == KEY_LEFT || sc == KEY_UP) ? -1 : 1));
        return;
    }
    if (!across && sc == KEY_RIGHT) {
        if (p->sel >= 0 && p->menu[p->sel].child) { pick(p, p->sel); return; }
        if (p->parent && p->parent->bar) {                  /* the next menu along the bar */
            MENU_PLAYER *b = p->parent;
            close_player(p);
            pick(b, step(b, b->sel, 1));
        }
        return;
    }
    if (!across && sc == KEY_LEFT) {
        MENU_PLAYER *b = p->parent;
        if (!b) return;
        close_player(p);
        if (b->bar) pick(b, step(b, b->sel, -1));
        return;
    }
    if (across && sc == KEY_DOWN) { if (p->sel >= 0) pick(p, p->sel); return; }
    if (sc == KEY_ENTER || sc == KEY_ENTER_PAD || sc == KEY_SPACE) { if (p->sel >= 0) pick(p, p->sel); return; }
    if (a) for (i = 0; i < p->size; i++)
        if (!is_sep(&p->menu[i]) && shortcut(&p->menu[i], a)) { pick(p, i); return; }
}

static void mouse_event(MENU_PLAYER *root)
{
    int mx = gui_mouse_x(), my = gui_mouse_y(), b = gui_mouse_b();
    MENU_PLAYER *p, *over = NULL;
    int pressed_now = (b & ~root->mouse_b) != 0, released_now = (root->mouse_b & ~b) != 0;
    root->mouse_b = b;
    if (pressed_now) root->pressed = 1;

    for (p = root; p; p = p->child) if (inside(p, mx, my)) over = p;
    if (!over) {
        if (pressed_now) root->done = 1;                    /* a click outside every menu */
        return;
    }
    {
        int i = item_at(over, mx, my);
        if (over->child && i != over->sel && (over->bar ? root->pressed || over->child : 1)) close_player(over->child);
        if (i >= 0 && !is_sep(&over->menu[i])) {
            set_sel(over, i);
            if (over->menu[i].child && !over->child && (!over->bar || root->pressed || b)) open_child(over);
        }
        if (i >= 0 && !is_sep(&over->menu[i]) && !over->menu[i].child && released_now)
            pick(over, i);
    }
}

MENU_PLAYER *init_menu(MENU *menu, int x, int y)
{
    MENU_PLAYER *p;
    if (!menu) return NULL;
    p = new_player(menu, FALSE, x, y, NULL);
    if (p) draw_menu(p);
    return p;
}

static MENU_PLAYER *init_bar(MENU *menu, int x, int y, int sel)
{
    MENU_PLAYER *p = new_player(menu, TRUE, x, y, NULL);
    if (!p) return NULL;
    p->drawn = 1;                                           /* the dialog draws the bar */
    p->pressed = 1;
    if (sel >= 0) pick(p, sel);
    return p;
}

int update_menu(MENU_PLAYER *p)
{
    if (!p) return FALSE;
    if (!p->drawn) draw_menu(p);
    mouse_event(p);
    while (!p->done && keypressed()) {
        int sc, a = ureadkey(&sc);
        key_event(p, a, sc);
    }
    return !p->done;
}

int shutdown_menu(MENU_PLAYER *p)
{
    int ret;
    MENU *chosen;
    if (!p) return -1;
    ret = p->chosen ? p->ret : -1;
    chosen = p->chosen;
    close_player(p);
    if (chosen && chosen->proc) {
        active_menu = chosen;
        chosen->proc();
    }
    return ret;
}

int do_menu(MENU *menu, int x, int y)
{
    MENU_PLAYER *p = init_menu(menu, x, y);
    if (!p) return -1;
    while (update_menu(p)) rest(1);
    return shutdown_menu(p);
}

/* runs a bar's menu until it ends; the chosen item's proc result, or -1 */
static int run_bar(DIALOG *d, int sel, int *proc_ret)
{
    MENU_PLAYER *p = init_bar((MENU *)d->dp, d->x, d->y, sel);
    MENU *chosen;
    if (!p) return -1;
    while (update_menu(p)) rest(1);
    chosen = p->chosen;
    close_player(p);
    scare_mouse();
    object_message(d, MSG_DRAW, 0);                         /* the bar without a highlight */
    unscare_mouse();
    *proc_ret = D_O_K;
    if (chosen) {
        active_menu = chosen;
        if (chosen->proc) *proc_ret = chosen->proc();
        return 0;
    }
    return -1;
}

int d_menu_proc(int msg, DIALOG *d, int c)
{
    MENU *menu = (MENU *)d->dp;
    int r = D_O_K, i;
    if (!menu) return D_O_K;
    switch (msg) {
    case MSG_START: {
        MENU_PLAYER tmp;
        memset(&tmp, 0, sizeof(tmp));
        tmp.menu = menu; tmp.bar = TRUE; tmp.x = d->x; tmp.y = d->y;
        layout(&tmp);
        d->w = tmp.w; d->h = tmp.h;
        break;
    }
    case MSG_DRAW: {
        MENU_PLAYER tmp;
        memset(&tmp, 0, sizeof(tmp));
        tmp.menu = menu; tmp.bar = TRUE; tmp.x = d->x; tmp.y = d->y; tmp.sel = -1;
        layout(&tmp);
        draw_menu(&tmp);
        break;
    }
    case MSG_CLICK: {
        int mx = gui_mouse_x(), my = gui_mouse_y(), sel;
        MENU_PLAYER tmp;
        memset(&tmp, 0, sizeof(tmp));
        tmp.menu = menu; tmp.bar = TRUE; tmp.x = d->x; tmp.y = d->y;
        layout(&tmp);
        sel = item_at(&tmp, mx, my);
        if (sel >= 0 && !is_sep(&menu[sel])) { run_bar(d, sel, &r); r &= ~D_USED_CHAR; }
        break;
    }
    case MSG_XCHAR:                                         /* Alt+letter opens that menu */
        if (key_shifts & KB_ALT_FLAG) {
            int a = (c & 255) ? (c & 255) : scancode_to_ascii(c >> 8);
            for (i = 0; menu[i].text; i++)
                if (!is_sep(&menu[i]) && a && shortcut(&menu[i], a)) {
                    run_bar(d, i, &r);
                    r |= D_USED_CHAR;
                    break;
                }
        }
        break;
    case MSG_WANTFOCUS:
        return D_O_K;
    default:
        break;
    }
    return r;
}

/* ---- the screen mode selector ----------------------------------------------------------- */

static const struct { int w, h; } modes[] = {
    { 320, 200 }, { 320, 240 }, { 320, 256 }, { 640, 200 }, { 640, 256 }, { 640, 400 }, { 640, 480 }, { 800, 600 },
};
#define NMODES ((int)(sizeof(modes) / sizeof(modes[0])))

static char *mode_getter(int index, int *list_size)
{
    static char buf[24];
    if (index < 0) { if (list_size) *list_size = NMODES; return NULL; }
    if (index >= NMODES) return NULL;
    sprintf(buf, "%dx%d", modes[index].w, modes[index].h);
    return buf;
}

int gfx_mode_select_ex(int *card, int *w, int *h, int *color_depth)
{
    int th = text_height(font), bw = 200, bh = th * 6 + 60, sel = 0, i, r;
    DIALOG dlg[] = {
        { d_shadow_box_proc, 0, 0, bw, bh, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL },
        { d_ctext_proc, bw / 2, 6, 1, th, 0, 0, 0, 0, 0, 0, (void *)"Screen mode", NULL, NULL },
        { d_list_proc, 16, th + 14, bw - 32, th * 6 + 4, 0, 0, 0, D_EXIT, 0, 0, (void *)mode_getter, NULL, NULL },
        { d_button_proc, 16, bh - 26, 76, 18, 0, 0, 0, D_EXIT, 0, 0, (void *)"OK", NULL, NULL },
        { d_button_proc, bw - 92, bh - 26, 76, 18, 0, 0, 27, D_EXIT, 0, 0, (void *)"Cancel", NULL, NULL },
        { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL },
    };
    for (i = 0; i < NMODES; i++) if (w && h && modes[i].w == *w && modes[i].h == *h) sel = i;
    dlg[2].d1 = sel;
    for (i = 0; dlg[i].proc; i++) { dlg[i].fg = gui_fg_color; dlg[i].bg = gui_bg_color; }
    centre_dialog(dlg);
    r = popup_dialog(dlg, 2);
    if (r < 0 || r == 4) return FALSE;
    if (card) *card = GFX_AUTODETECT;
    if (w) *w = modes[dlg[2].d1].w;
    if (h) *h = modes[dlg[2].d1].h;
    if (color_depth) *color_depth = 8;
    return TRUE;
}

int gfx_mode_select(int *card, int *w, int *h) { return gfx_mode_select_ex(card, w, h, NULL); }
