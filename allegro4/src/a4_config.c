/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Allegro 4's configuration: text in [sections] of "name = value" lines,
 * from a file (set_config_file, written back when changed), from memory
 * (set_config_data: games keep scripts in their datafiles), with an override
 * on top (override_config_file/_data), and push/pop of the whole state.
 * Lines starting with # are comments and are kept when a file is written.
 * Names and sections are matched without regard to case. Library side:
 * no C library here, so the numbers are read and written by hand.
 */
#include "a4_internal.h"

struct a4_cfg_line {
    char *name;                     /* NULL for a comment or blank line */
    char *data;                     /* the value, or the whole line when name is NULL */
    char *section;                  /* "" for the lines before the first [section] */
    struct a4_cfg_line *next;
};

struct a4_config {
    struct a4_cfg_line *head;
    char *filename;                 /* NULL for memory */
    int dirty;
};

#define CFG_STACK 4
struct a4_cfg_state {
    struct a4_config *main, *over;
    struct a4_config *stack_main[CFG_STACK], *stack_over[CFG_STACK];
    int depth;
    char *argv_buf;
    char **argv;
};

static struct a4_cfg_state *cs(void)
{
    if (!A4S->config) A4S->config = a4_calloc(sizeof(struct a4_cfg_state));
    return (struct a4_cfg_state *)A4S->config;
}

/* ---- text helpers --------------------------------------------------------------------- */

static int is_space(int c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }
static int lower(int c) { return c >= 'A' && c <= 'Z' ? c + 32 : c; }

static int same(const char *a, const char *b)
{
    for (; *a && *b; a++, b++) if (lower((unsigned char)*a) != lower((unsigned char)*b)) return 0;
    return *a == *b;
}

static char *dup_n(const char *s, long n)
{
    char *d = (char *)a4_malloc(n + 1);
    if (!d) return NULL;
    memcpy(d, s, n);
    d[n] = 0;
    return d;
}

static char *dup_s(const char *s) { return dup_n(s, (long)strlen(s)); }

/* "[sound]" or "sound" or NULL: the bare name, in buf */
static const char *sec_name(const char *s, char *buf, int size)
{
    int n = 0;
    if (!s) return "";
    while (is_space((unsigned char)*s)) s++;
    if (*s == '[') s++;
    while (*s && *s != ']' && n < size - 1) buf[n++] = *s++;
    while (n > 0 && is_space((unsigned char)buf[n - 1])) n--;
    buf[n] = 0;
    return buf;
}

/* ---- parsing and writing ------------------------------------------------------------- */

static void cfg_free(struct a4_config *c)
{
    struct a4_cfg_line *l, *n;
    if (!c) return;
    for (l = c->head; l; l = n) {
        n = l->next;
        a4_free(l->name); a4_free(l->data); a4_free(l->section); a4_free(l);
    }
    a4_free(c->filename);
    a4_free(c);
}

static struct a4_cfg_line *add_line(struct a4_config *c, struct a4_cfg_line **tail, char *name, char *data, const char *section)
{
    struct a4_cfg_line *l = (struct a4_cfg_line *)a4_calloc(sizeof(*l));
    if (!l) { a4_free(name); a4_free(data); return NULL; }
    l->name = name; l->data = data; l->section = dup_s(section);
    if (*tail) (*tail)->next = l; else c->head = l;
    *tail = l;
    return l;
}

static struct a4_config *cfg_parse(const char *text, long size)
{
    struct a4_config *c = (struct a4_config *)a4_calloc(sizeof(*c));
    struct a4_cfg_line *tail = NULL;
    char section[128];
    long i = 0;
    if (!c) return NULL;
    section[0] = 0;
    while (text && i < size) {
        long s = i, e, a, b;
        while (i < size && text[i] != '\n' && text[i] != 0) i++;
        e = i;
        if (i < size) i++;
        if (e > s && text[e - 1] == '\r') e--;
        a = s;
        while (a < e && is_space((unsigned char)text[a])) a++;
        if (a < e && text[a] == '[') {                      /* a section */
            int n = 0;
            a++;
            while (a < e && text[a] != ']' && n < (int)sizeof(section) - 1) section[n++] = text[a++];
            while (n > 0 && is_space((unsigned char)section[n - 1])) n--;
            section[n] = 0;
            add_line(c, &tail, NULL, dup_n(text + s, e - s), section);
            continue;
        }
        if (a >= e || text[a] == '#' || text[a] == ';') {   /* blank or comment */
            add_line(c, &tail, NULL, dup_n(text + s, e - s), section);
            continue;
        }
        b = a;
        while (b < e && text[b] != '=') b++;
        {
            long ne = b, vs = b + 1, ve = e;
            while (ne > a && is_space((unsigned char)text[ne - 1])) ne--;
            if (b >= e) { vs = ve = e; }                    /* a name alone: an empty value */
            while (vs < ve && is_space((unsigned char)text[vs])) vs++;
            while (ve > vs && is_space((unsigned char)text[ve - 1])) ve--;
            add_line(c, &tail, dup_n(text + a, ne - a), dup_n(text + vs, ve - vs), section);
        }
    }
    return c;
}

static struct a4_config *cfg_load(const char *filename)
{
    a4_file *f;
    char *buf = NULL;
    long size = 0, cap = 0, n;
    struct a4_config *c;
    f = a4_os_open(filename, 0);
    if (f) {
        for (;;) {
            if (size + 1024 > cap) {
                char *nb = (char *)a4_realloc(buf, cap, cap + 4096);
                if (!nb) break;
                buf = nb; cap += 4096;
            }
            n = a4_os_read(f, buf + size, 1024);
            if (n <= 0) break;
            size += n;
        }
        a4_os_close(f);
    }
    c = cfg_parse(buf, size);
    a4_free(buf);
    if (c) c->filename = dup_s(filename);
    return c;
}

static void put(a4_file *f, const char *s) { a4_os_write(f, s, (long)strlen(s)); }

static void cfg_save(struct a4_config *c)
{
    a4_file *f;
    struct a4_cfg_line *l;
    if (!c || !c->filename || !c->dirty) return;
    f = a4_os_open(c->filename, 1);
    if (!f) return;
    for (l = c->head; l; l = l->next) {
        if (l->name) { put(f, l->name); put(f, " = "); put(f, l->data ? l->data : ""); }
        else put(f, l->data ? l->data : "");
        put(f, "\n");
    }
    a4_os_close(f);
    c->dirty = 0;
}

static struct a4_cfg_line *find(struct a4_config *c, const char *section, const char *name)
{
    struct a4_cfg_line *l;
    if (!c) return NULL;
    for (l = c->head; l; l = l->next)
        if (l->name && same(l->section, section) && same(l->name, name)) return l;
    return NULL;
}

static void cfg_set(struct a4_config *c, const char *section, const char *name, const char *val)
{
    struct a4_cfg_line *l = find(c, section, name), *last = NULL, *prev = NULL, *p;
    if (l) {
        if (!val || !*val) {                                /* an empty value removes the line */
            for (p = c->head; p && p != l; p = p->next) prev = p;
            if (prev) prev->next = l->next; else c->head = l->next;
            a4_free(l->name); a4_free(l->data); a4_free(l->section); a4_free(l);
        } else {
            a4_free(l->data);
            l->data = dup_s(val);
        }
        c->dirty = 1;
        return;
    }
    if (!val || !*val) return;
    /* a new line: after the section's last line, or a new section at the end */
    for (p = c->head; p; p = p->next) {
        if (same(p->section, section)) last = p;
        prev = p;
    }
    l = (struct a4_cfg_line *)a4_calloc(sizeof(*l));
    if (!l) return;
    l->name = dup_s(name); l->data = dup_s(val); l->section = dup_s(section);
    if (last) { l->next = last->next; last->next = l; }
    else {
        struct a4_cfg_line *tail = prev;
        if (*section) {
            struct a4_cfg_line *h = (struct a4_cfg_line *)a4_calloc(sizeof(*h));
            if (h) {
                long n = (long)strlen(section);
                h->data = (char *)a4_malloc(n + 3);
                if (h->data) { h->data[0] = '['; memcpy(h->data + 1, section, n); h->data[n + 1] = ']'; h->data[n + 2] = 0; }
                h->section = dup_s(section);
                if (tail) tail->next = h; else c->head = h;
                tail = h;
            }
        }
        if (tail) tail->next = l; else c->head = l;
    }
    c->dirty = 1;
}

/* ---- the calls ------------------------------------------------------------------------- */

static void drop_argv(void)
{
    struct a4_cfg_state *s = cs();
    a4_free(s->argv_buf); a4_free(s->argv);
    s->argv_buf = NULL; s->argv = NULL;
}

void a4_config_shutdown(void)
{
    struct a4_cfg_state *s = (struct a4_cfg_state *)A4S->config;
    int i;
    if (!s) return;
    cfg_save(s->main);
    cfg_free(s->main); cfg_free(s->over);
    for (i = 0; i < s->depth; i++) { cfg_save(s->stack_main[i]); cfg_free(s->stack_main[i]); cfg_free(s->stack_over[i]); }
    drop_argv();
    a4_free(s);
    A4S->config = NULL;
}

void set_config_file(const char *filename)
{
    struct a4_cfg_state *s = cs();
    if (!s) return;
    cfg_save(s->main);
    cfg_free(s->main);
    s->main = filename ? cfg_load(filename) : NULL;
}

void set_config_data(const char *data, int length)
{
    struct a4_cfg_state *s = cs();
    if (!s) return;
    cfg_save(s->main);
    cfg_free(s->main);
    s->main = cfg_parse(data, data ? length : 0);
}

void override_config_file(const char *filename)
{
    struct a4_cfg_state *s = cs();
    if (!s) return;
    cfg_save(s->over);
    cfg_free(s->over);
    s->over = filename ? cfg_load(filename) : NULL;
}

void override_config_data(const char *data, int length)
{
    struct a4_cfg_state *s = cs();
    if (!s) return;
    cfg_free(s->over);
    s->over = data ? cfg_parse(data, length) : NULL;
}

void flush_config_file(void)
{
    struct a4_cfg_state *s = cs();
    if (s) cfg_save(s->main);
}

void push_config_state(void)
{
    struct a4_cfg_state *s = cs();
    if (!s) return;
    if (s->depth >= CFG_STACK) {                            /* full: the oldest goes */
        int i;
        cfg_save(s->stack_main[0]); cfg_free(s->stack_main[0]); cfg_free(s->stack_over[0]);
        for (i = 1; i < CFG_STACK; i++) { s->stack_main[i - 1] = s->stack_main[i]; s->stack_over[i - 1] = s->stack_over[i]; }
        s->depth--;
    }
    s->stack_main[s->depth] = s->main;
    s->stack_over[s->depth] = s->over;
    s->depth++;
    s->main = s->over = NULL;
}

void pop_config_state(void)
{
    struct a4_cfg_state *s = cs();
    if (!s || s->depth <= 0) return;
    cfg_save(s->main);
    cfg_free(s->main); cfg_free(s->over);
    s->depth--;
    s->main = s->stack_main[s->depth];
    s->over = s->stack_over[s->depth];
}

const char *get_config_string(const char *section, const char *name, const char *def)
{
    struct a4_cfg_state *s = cs();
    struct a4_cfg_line *l;
    char sec[128];
    const char *sn = sec_name(section, sec, sizeof(sec));
    if (!s || !name) return def;
    l = find(s->over, sn, name);
    if (!l) l = find(s->main, sn, name);
    return l && l->data ? l->data : def;
}

void set_config_string(const char *section, const char *name, const char *val)
{
    struct a4_cfg_state *s = cs();
    char sec[128];
    const char *sn = sec_name(section, sec, sizeof(sec));
    if (!s || !name) return;
    if (find(s->over, sn, name)) { cfg_set(s->over, sn, name, val); return; }
    if (!s->main) s->main = cfg_parse(NULL, 0);
    if (s->main) cfg_set(s->main, sn, name, val);
}

/* a number: decimal, or hex after 0x; leading spaces and a sign */
static int parse_int(const char *p, int base, int *ok)
{
    long v = 0;
    int neg = 0, any = 0;
    while (is_space((unsigned char)*p)) p++;
    if (*p == '-') { neg = 1; p++; } else if (*p == '+') p++;
    if ((base == 0 || base == 16) && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) { base = 16; p += 2; }
    else if (base == 0) base = 10;
    for (;; p++) {
        int c = lower((unsigned char)*p), d;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
        else break;
        if (d >= base) break;
        v = v * base + d;
        any = 1;
    }
    *ok = any;
    return (int)(neg ? -v : v);
}

static void fmt_int(char *buf, unsigned long v, int neg, int base)
{
    char t[16];
    int n = 0, i = 0;
    do { int d = (int)(v % base); t[n++] = (char)(d < 10 ? '0' + d : 'A' + d - 10); v /= base; } while (v && n < 15);
    if (neg) buf[i++] = '-';
    while (n) buf[i++] = t[--n];
    buf[i] = 0;
}

int get_config_int(const char *section, const char *name, int def)
{
    const char *v = get_config_string(section, name, NULL);
    int ok, r;
    if (!v) return def;
    r = parse_int(v, 0, &ok);
    return ok ? r : def;
}

void set_config_int(const char *section, const char *name, int val)
{
    char buf[16];
    fmt_int(buf, val < 0 ? 0UL - (unsigned long)val : (unsigned long)val, val < 0, 10);
    set_config_string(section, name, buf);
}

int get_config_hex(const char *section, const char *name, int def)
{
    const char *v = get_config_string(section, name, NULL);
    int ok, r;
    if (!v) return def;
    r = parse_int(v, 16, &ok);
    return ok ? r : def;
}

void set_config_hex(const char *section, const char *name, int val)
{
    char buf[16];
    if (val < 0) { set_config_string(section, name, "-1"); return; }
    fmt_int(buf, (unsigned long)val, 0, 16);
    set_config_string(section, name, buf);
}

/* four characters packed, as AL_ID makes them */
int get_config_id(const char *section, const char *name, int def)
{
    const char *v = get_config_string(section, name, NULL);
    unsigned char c[4] = { ' ', ' ', ' ', ' ' };
    int i;
    if (!v || !*v) return def;
    if (same(v, "0")) return 0;
    for (i = 0; i < 4 && v[i]; i++) c[i] = (unsigned char)(v[i] >= 'a' && v[i] <= 'z' ? v[i] - 32 : v[i]);
    return (int)(((unsigned)c[0] << 24) | ((unsigned)c[1] << 16) | ((unsigned)c[2] << 8) | c[3]);
}

void set_config_id(const char *section, const char *name, int val)
{
    char buf[5];
    int i, n = 4;
    if (val == 0) { set_config_string(section, name, "0"); return; }
    for (i = 0; i < 4; i++) buf[i] = (char)((val >> (24 - 8 * i)) & 255);
    while (n > 0 && (buf[n - 1] == ' ' || buf[n - 1] == 0)) n--;
    buf[n] = 0;
    set_config_string(section, name, buf);
}

/* the value cut at spaces; "quoted words" stay one */
char **get_config_argv(const char *section, const char *name, int *argc)
{
    struct a4_cfg_state *s = cs();
    const char *v = get_config_string(section, name, NULL);
    long n;
    int count = 0, i;
    char *p;
    if (argc) *argc = 0;
    if (!s || !v) return NULL;
    drop_argv();
    n = (long)strlen(v);
    s->argv_buf = dup_n(v, n);
    s->argv = (char **)a4_calloc(sizeof(char *) * (n / 2 + 2));
    if (!s->argv_buf || !s->argv) { drop_argv(); return NULL; }
    p = s->argv_buf;
    for (;;) {
        while (*p && is_space((unsigned char)*p)) p++;
        if (!*p) break;
        if (*p == '"') {
            p++;
            s->argv[count++] = p;
            while (*p && *p != '"') p++;
        } else {
            s->argv[count++] = p;
            while (*p && !is_space((unsigned char)*p)) p++;
        }
        if (*p) *p++ = 0;
    }
    for (i = count; i < n / 2 + 2; i++) s->argv[i] = NULL;
    if (argc) *argc = count;
    return s->argv;
}
