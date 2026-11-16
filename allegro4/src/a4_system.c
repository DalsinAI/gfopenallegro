/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Start and end, configuration (defaults only), strings, file names and
 * directory searches.
 */
#include "a4_internal.h"
#include "acgame/platform.h"

void a4_gfx_shutdown(void);

void a4_set_error(const char *msg) { ustrzcpy(allegro_error, ALLEGRO_ERROR_SIZE, msg); }

char *a4_strdup0(const char *s)
{
    size_t n;
    char *d;
    if (!s) s = "";
    n = strlen(s) + 1;
    d = (char *)a4_malloc(n);
    if (d) memcpy(d, s, n);
    return d;
}

/* the stubs pass the game's variables; the host build passes its own */
int a4_install(struct a4_public *pub, int system_id)
{
    (void)system_id;
    if (A4S->installed) return 0;
    memset(A4S, 0, sizeof(*A4S));
    A4S->pub = pub;
    A4S->installed = 1;
    A4S->text_bg = 0;
    A4S->digi_volume = A4S->midi_volume = 255;
    A4S->color_conv = COLORCONV_TOTAL;
    A4S->blend_kind = A4_BLEND_TRANS;
    A4S->blend_a = 255;
    A4S->mixer_quality = 2;
    os_type = OSTYPE_AMIGA;
    if (_color_depth == 0) _color_depth = 8;
    font = a4_builtin_font();
    screen = NULL;
    _a4_screen_w = _a4_screen_h = 0;
    allegro_error[0] = 0;
    {
        int i;
        for (i = 0; i < 256; i++) {
            A4S->palette[i][0] = default_palette[i].r;
            A4S->palette[i][1] = default_palette[i].g;
            A4S->palette[i][2] = default_palette[i].b;
        }
    }
    return 0;
}

void allegro_exit(void)
{
    a4_config_shutdown();                   /* writes the config file back */
    if (!A4S->installed) return;
    remove_sound();
    remove_timer();
    remove_keyboard();
    remove_mouse();
    remove_joystick();
    a4_gfx_shutdown();
    a4_font_free_builtin();
    font = NULL;
    A4S->installed = 0;
}

void set_window_title(const char *name)
{
    ustrzcpy(A4S->window_title, (int)sizeof(A4S->window_title), name ? name : "");
    a4_os_title(A4S->window_title);
}
int set_close_button_callback(void (*proc)(void)) { A4S->close_button = proc; return 0; }
int desktop_color_depth(void) { return 8; }
int get_desktop_resolution(int *w, int *h)
{
    acgame_platform_info info;
    if (A4S->gfx_on && acgame_platform_get_info(&info) == 0) { *w = (int)info.screen_width; *h = (int)info.screen_height; }
    else { *w = 640; *h = 480; }
    return 0;
}
void check_cpu(void) {}
void yield_timeslice(void) { a4_os_delay_ms(1); }
int set_display_switch_mode(int mode) { return mode == SWITCH_NONE || mode == SWITCH_PAUSE || mode == SWITCH_BACKGROUND ? 0 : -1; }
int set_display_switch_callback(int dir, void (*cb)(void)) { (void)dir; (void)cb; return 0; }
void remove_display_switch_callback(void (*cb)(void)) { (void)cb; }
int get_display_switch_mode(void) { return SWITCH_PAUSE; }


/* a message box on the screen: lines and buttons; returns the button picked
 * (1-3) by its first letter, Return (1) or Esc (last) */
int alert3(const char *s1, const char *s2, const char *s3, const char *b1, const char *b2, const char *b3,
           int c1, int c2, int c3)
{
    const char *lines[3];
    int i, y, w = 0, h, x0, y0, nb = b3 ? 3 : b2 ? 2 : 1, white, black;
    BITMAP *scr = A4S->screen_bmp;
    FONT *f = font;
    lines[0] = s1; lines[1] = s2; lines[2] = s3;
    if (!scr || !f) {
        char msg[512];
        msg[0] = 0;
        for (i = 0; i < 3; i++) if (lines[i]) { ustrzcat(msg, 512, lines[i]); ustrzcat(msg, 512, "\n"); }
        a4_os_message(msg);
        return 1;
    }
    for (i = 0; i < 3; i++) if (lines[i] && text_length(f, lines[i]) > w) w = text_length(f, lines[i]);
    w += 32;
    if (w < 200) w = 200;
    h = text_height(f) * 6 + 16;
    x0 = (scr->w - w) / 2;
    y0 = (scr->h - h) / 2;
    white = makecol(255, 255, 255);
    black = makecol(0, 0, 0);
    rectfill(scr, x0, y0, x0 + w - 1, y0 + h - 1, white);
    rect(scr, x0, y0, x0 + w - 1, y0 + h - 1, black);
    y = y0 + 8;
    for (i = 0; i < 3; i++) { if (lines[i]) textout_centre_ex(scr, f, lines[i], x0 + w / 2, y, black, -1); y += text_height(f); }
    y += text_height(f);
    {
        const char *bs[3];
        bs[0] = b1; bs[1] = b2; bs[2] = b3;
        for (i = 0; i < nb; i++) {
            int bx = x0 + (w * (2 * i + 1)) / (2 * nb);
            textout_centre_ex(scr, f, bs[i] ? bs[i] : "", bx, y, black, -1);
        }
    }
    a4_present();
    if (!A4S->kb_on) install_keyboard();
    clear_keybuf();
    for (;;) {
        int k = readkey(), a = utolower(k & 255), sc = k >> 8;
        if (sc == KEY_ENTER || sc == KEY_ENTER_PAD || sc == KEY_SPACE) return 1;
        if (sc == KEY_ESC) return nb;
        if (c1 && a == utolower(c1)) return 1;
        if (c2 && a == utolower(c2)) return 2;
        if (c3 && a == utolower(c3)) return 3;
    }
}

int alert(const char *s1, const char *s2, const char *s3, const char *b1, const char *b2, int c1, int c2)
{
    int r = alert3(s1, s2, s3, b1, b2, NULL, c1, c2, 0);
    return r > 2 ? 2 : r;
}

/* ---- strings ------------------------------------------------------------------- */

void set_uformat(int type) { (void)type; }
int get_uformat(void) { return U_ASCII; }
const char *uconvert(const char *s, int type, char *buf, int newtype, int size)
{
    (void)type; (void)newtype;
    if (!buf) return s;
    ustrzcpy(buf, size, s);
    return buf;
}

char *ustrzcpy(char *d, int size, const char *s)
{
    int i = 0;
    if (size <= 0) return d;
    while (i < size - 1 && s[i]) { d[i] = s[i]; i++; }
    d[i] = 0;
    return d;
}

char *ustrzcat(char *d, int size, const char *s)
{
    int n = (int)strlen(d);
    if (n < size) ustrzcpy(d + n, size - n, s);
    return d;
}

char *ustrzncpy(char *d, int size, const char *s, int n)
{
    int i = 0;
    if (size <= 0) return d;
    while (i < size - 1 && i < n && s[i]) { d[i] = s[i]; i++; }
    d[i] = 0;
    return d;
}

int ustricmp(const char *a, const char *b)
{
    for (;; a++, b++) {
        int x = utolower((unsigned char)*a), y = utolower((unsigned char)*b);
        if (x != y || !x) return x - y;
    }
}

int ustrnicmp(const char *a, const char *b, int n)
{
    for (; n > 0; n--, a++, b++) {
        int x = utolower((unsigned char)*a), y = utolower((unsigned char)*b);
        if (x != y || !x) return x - y;
    }
    return 0;
}

char *ustrlwr(char *s) { char *p; for (p = s; *p; p++) *p = (char)utolower((unsigned char)*p); return s; }
char *ustrupr(char *s) { char *p; for (p = s; *p; p++) *p = (char)utoupper((unsigned char)*p); return s; }

char *ustrtok_r(char *s, const char *set, char **last)
{
    char *tok;
    if (!s) s = *last;
    if (!s) return NULL;
    while (*s && strchr(set, *s)) s++;
    if (!*s) { *last = NULL; return NULL; }
    tok = s;
    while (*s && !strchr(set, *s)) s++;
    if (*s) { *s = 0; *last = s + 1; } else *last = NULL;
    return tok;
}
char *ustrtok(char *s, const char *set) { static char *last; return ustrtok_r(s, set, &last); }

int usetat(char *s, int index, int c) { s[index] = (char)c; return 0; }
int uinsert(char *s, int index, int c)
{
    int n = (int)strlen(s);
    memmove(s + index + 1, s + index, (size_t)(n - index + 1));
    s[index] = (char)c;
    return 1;
}
int uremove(char *s, int index)
{
    int n = (int)strlen(s);
    if (index >= n) return 0;
    memmove(s + index, s + index + 1, (size_t)(n - index));
    return -1;
}

/* ---- file names ------------------------------------------------------------------ */

char *get_filename(const char *path)
{
    const char *p = path, *last = path;
    for (; *p; p++) if (*p == '/' || *p == '\\' || *p == ':') last = p + 1;
    return (char *)last;
}

char *get_extension(const char *filename)
{
    const char *name = get_filename(filename), *dot = NULL, *p;
    for (p = name; *p; p++) if (*p == '.') dot = p;
    return (char *)(dot ? dot + 1 : p);
}

void put_backslash(char *filename)
{
    int n = (int)strlen(filename);
    if (n && filename[n - 1] != '/' && filename[n - 1] != ':' && filename[n - 1] != '\\') { filename[n] = '/'; filename[n + 1] = 0; }
}

char *fix_filename_case(char *path) { return path; }
char *fix_filename_slashes(char *path) { char *p; for (p = path; *p; p++) if (*p == '\\') *p = '/'; return path; }
char *fix_filename_path(char *dest, const char *path, int size) { ustrzcpy(dest, size, path); return fix_filename_slashes(dest); }
char *canonicalize_filename(char *dest, const char *filename, int size) { return fix_filename_path(dest, filename, size); }
int is_relative_filename(const char *f) { return !strchr(f, ':') && f[0] != '/'; }
char *make_absolute_filename(char *dest, const char *path, const char *filename, int size)
{
    if (!is_relative_filename(filename)) return ustrzcpy(dest, size, filename);
    return append_filename(dest, path, filename, size);
}
char *make_relative_filename(char *dest, const char *path, const char *filename, int size)
{
    int n = (int)strlen(path);
    if (ustrnicmp(path, filename, n) == 0) return ustrzcpy(dest, size, filename + n + (filename[n] == '/'));
    return NULL;
}

char *replace_filename(char *dest, const char *path, const char *filename, int size)
{
    char tmp[1024];
    int n = (int)(get_filename(path) - path);
    if (n >= (int)sizeof(tmp)) n = (int)sizeof(tmp) - 1;
    memcpy(tmp, path, (size_t)n);
    tmp[n] = 0;
    ustrzcat(tmp, (int)sizeof(tmp), filename);
    return ustrzcpy(dest, size, tmp);
}

char *replace_extension(char *dest, const char *filename, const char *ext, int size)
{
    char tmp[1024];
    const char *e = get_extension(filename);
    int n = (int)(e - filename);
    if (n > 0 && filename[n - 1] == '.') n--;
    if (n >= (int)sizeof(tmp) - 1) n = (int)sizeof(tmp) - 2;
    memcpy(tmp, filename, (size_t)n);
    tmp[n] = '.';
    tmp[n + 1] = 0;
    ustrzcat(tmp, (int)sizeof(tmp), ext);
    return ustrzcpy(dest, size, tmp);
}

char *append_filename(char *dest, const char *path, const char *filename, int size)
{
    char tmp[1024];
    ustrzcpy(tmp, (int)sizeof(tmp) - 2, path);
    if (tmp[0]) put_backslash(tmp);
    ustrzcat(tmp, (int)sizeof(tmp), filename);
    return ustrzcpy(dest, size, tmp);
}

void get_executable_name(char *output, int size) { ustrzcpy(output, size, "PROGDIR:game"); }

int find_allegro_resource(char *dest, const char *resource, const char *ext, const char *datafile,
                          const char *objectname, const char *envvar, const char *subdir, int size)
{
    (void)ext; (void)datafile; (void)objectname; (void)envvar; (void)subdir;
    if (exists(resource)) { ustrzcpy(dest, size, resource); return 0; }
    return -1;
}

int file_exists(const char *filename, int attrib, int *aret)
{
    int isdir = 0;
    if (!a4_os_stat(filename, &isdir, NULL, NULL)) return FALSE;
    if (aret) *aret = isdir ? FA_DIREC : FA_ARCH;
    if (isdir && !(attrib & FA_DIREC)) return FALSE;
    return TRUE;
}
int exists(const char *filename) { return file_exists(filename, FA_ARCH | FA_RDONLY, NULL); }
long file_size(const char *filename) { long s = 0; if (!a4_os_stat(filename, NULL, &s, NULL)) return 0; return s; }
time_t file_time(const char *filename) { long t = 0; a4_os_stat(filename, NULL, NULL, &t); return (time_t)t; }
int delete_file(const char *filename) { return a4_os_delete(filename) == 0 ? 0 : -1; }

/* ---- directory searches ------------------------------------------------------------ */

static int wild_match(const char *p, const char *s)
{
    for (; *p; p++, s++) {
        if (*p == '*') {
            while (p[1] == '*') p++;
            if (!p[1]) return 1;
            for (; *s; s++) if (wild_match(p + 1, s)) return 1;
            return 0;
        }
        if (!*s) return 0;
        if (*p != '?' && utolower((unsigned char)*p) != utolower((unsigned char)*s)) return 0;
    }
    return !*s;
}

struct ff_state {
    void *dir;
    char dirpath[512];
    char pattern[256];
    int attrib;
};

int al_findnext(struct al_ffblk *info)
{
    struct ff_state *st = (struct ff_state *)info->ff_data;
    char name[512];
    int isdir;
    long size, mtime;
    if (!st || !st->dir) return -1;
    while (a4_os_readdir(st->dir, name, (int)sizeof(name), &isdir, &size, &mtime)) {
        int a = isdir ? FA_DIREC : FA_ARCH;
        if (!wild_match(st->pattern, name)) continue;
        if (isdir && !(st->attrib & FA_DIREC)) continue;
        info->attrib = a;
        info->size = size;
        info->time = (time_t)mtime;
        ustrzcpy(info->name, (int)sizeof(info->name), name);
        return 0;
    }
    *allegro_errno = ENOENT;
    return -1;
}

int al_findfirst(const char *pattern, struct al_ffblk *info, int attrib)
{
    struct ff_state *st = (struct ff_state *)a4_calloc(sizeof(struct ff_state));
    const char *name = get_filename(pattern);
    int n = (int)(name - pattern);
    if (!st) return -1;
    if (n > 0 && n < (int)sizeof(st->dirpath)) {
        memcpy(st->dirpath, pattern, (size_t)n);
        st->dirpath[n] = 0;
        if (n > 1 && st->dirpath[n - 1] == '/') st->dirpath[n - 1] = 0;
    }
    ustrzcpy(st->pattern, (int)sizeof(st->pattern), name);
    if (!strcmp(st->pattern, "*.*")) ustrzcpy(st->pattern, (int)sizeof(st->pattern), "*");
    st->attrib = attrib;
    st->dir = a4_os_opendir(st->dirpath);
    info->ff_data = st;
    if (!st->dir) { a4_free(st); info->ff_data = NULL; *allegro_errno = ENOENT; return -1; }
    if (al_findnext(info) != 0) { al_findclose(info); return -1; }
    return 0;
}

void al_findclose(struct al_ffblk *info)
{
    struct ff_state *st = (struct ff_state *)info->ff_data;
    if (!st) return;
    if (st->dir) a4_os_closedir(st->dir);
    a4_free(st);
    info->ff_data = NULL;
}

int for_each_file_ex(const char *name, int in_attrib, int out_attrib,
                     int (*callback)(const char *filename, int attrib, void *param), void *param)
{
    struct al_ffblk info;
    char path[1024];
    int n = 0;
    (void)out_attrib;
    if (al_findfirst(name, &info, in_attrib | FA_ALL) != 0) return 0;
    do {
        replace_filename(path, name, info.name, (int)sizeof(path));
        n++;
        if (callback(path, info.attrib, param) != 0) break;
    } while (al_findnext(&info) == 0);
    al_findclose(&info);
    return n;
}
