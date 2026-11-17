/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Allegro 4's configuration files: "name = value" lines in [sections]
 * (the lines before the first section are the global one), '#' comments.
 * Names and sections match without case. A file keeps its comments and
 * order when written back; it is written at flush_config_file, when
 * another file is set, at pop_config_state and at allegro_exit. An
 * override file is read first and never written.
 */
#include "a4_internal.h"

static char *dupn(const char *s, int n)
{
    char *d = (char *)a4_malloc((size_t)n + 1);
    if (!d) return NULL;
    memcpy(d, s, (size_t)n);
    d[n] = 0;
    return d;
}

static void drop_argv(void);

static void cfg_free(struct a4_cfg *c)
{
    int i;
    for (i = 0; i < c->n; i++) {
        a4_free(c->lines[i].sec);
        a4_free(c->lines[i].name);
        a4_free(c->lines[i].val);
        a4_free(c->lines[i].raw);
    }
    a4_free(c->lines);
    memset(c, 0, sizeof(*c));
}

static struct a4_cfg_line *new_line(struct a4_cfg *c, int at)
{
    if (c->n == c->cap) {
        int ncap = c->cap ? c->cap * 2 : 32;
        struct a4_cfg_line *nl = (struct a4_cfg_line *)a4_realloc(c->lines, sizeof(*nl) * (size_t)c->cap, sizeof(*nl) * (size_t)ncap);
        if (!nl) return NULL;
        c->lines = nl;
        c->cap = ncap;
    }
    if (at < c->n) memmove(&c->lines[at + 1], &c->lines[at], sizeof(c->lines[0]) * (size_t)(c->n - at));
    c->n++;
    memset(&c->lines[at], 0, sizeof(c->lines[0]));
    return &c->lines[at];
}

/* "[name]", "name" or NULL -> "name" ("" for the global section) */
static void sec_name(char *out, int size, const char *s)
{
    int n;
    if (!s) s = "";
    while (*s == ' ' || *s == '\t' || *s == '[') s++;
    ustrzcpy(out, size, s);
    n = (int)strlen(out);
    while (n > 0 && (out[n - 1] == ']' || out[n - 1] == ' ' || out[n - 1] == '\t')) out[--n] = 0;
}

static int is_space(int c) { return c == ' ' || c == '\t' || c == '\r'; }

/* numbers without the C library: [-+]digits, base 0 takes 0x as hex */
static long parse_num(const char *s, int base)
{
    long v = 0;
    int neg = 0, d;
    while (is_space(*s)) s++;
    if (*s == '-' || *s == '+') neg = *s++ == '-';
    if ((base == 0 || base == 16) && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) { s += 2; base = 16; }
    if (base == 0) base = 10;
    for (;; s++) {
        if (*s >= '0' && *s <= '9') d = *s - '0';
        else if (*s >= 'a' && *s <= 'f') d = *s - 'a' + 10;
        else if (*s >= 'A' && *s <= 'F') d = *s - 'A' + 10;
        else break;
        if (d >= base) break;
        v = v * base + d;
    }
    return neg ? -v : v;
}

static void fmt_num(char *b, unsigned long v, int neg, int base)
{
    char t[16];
    int n = 0, i = 0;
    do { int d = (int)(v % (unsigned)base); t[n++] = (char)(d < 10 ? '0' + d : 'A' + d - 10); v /= (unsigned)base; } while (v);
    if (neg) b[i++] = '-';
    while (n) b[i++] = t[--n];
    b[i] = 0;
}

static void cfg_parse(struct a4_cfg *c, const char *text, long len)
{
    char sec[128] = "";
    long p = 0;
    while (p < len) {
        long e = p, s, t;
        struct a4_cfg_line *l;
        while (e < len && text[e] != '\n') e++;
        s = p; t = e;
        while (s < t && is_space(text[s])) s++;
        while (t > s && is_space(text[t - 1])) t--;
        l = new_line(c, c->n);
        if (!l) return;
        if (s < t && text[s] == '[') {
            char tmp[128];
            int n = (int)(t - s) < 127 ? (int)(t - s) : 127;
            memcpy(tmp, text + s, (size_t)n);
            tmp[n] = 0;
            sec_name(sec, (int)sizeof(sec), tmp);
            l->sec = a4_strdup0(sec);
            l->raw = dupn(text + s, (int)(t - s));      /* a section's own line */
        } else if (s < t && text[s] != '#' && memchr(text + s, '=', (size_t)(t - s))) {
            long eq = s, ne, vs;
            while (text[eq] != '=') eq++;
            ne = eq;
            while (ne > s && is_space(text[ne - 1])) ne--;
            vs = eq + 1;
            while (vs < t && is_space(text[vs])) vs++;
            l->sec = a4_strdup0(sec);
            l->name = dupn(text + s, (int)(ne - s));
            l->val = dupn(text + vs, (int)(t - vs));
        } else {
            l->sec = a4_strdup0(sec);
            l->raw = dupn(text + p, (int)(e - p > 0 && text[e - 1] == '\r' ? e - p - 1 : e - p));
        }
        p = e + 1;
    }
}

static int cfg_load(struct a4_cfg *c, const char *filename)
{
    PACKFILE *f = pack_fopen(filename, F_READ);
    char *buf = NULL;
    long len = 0, cap = 0, got;
    if (!f) return -1;
    for (;;) {
        if (len + 1024 > cap) {
            char *nb = (char *)a4_realloc(buf, (size_t)cap, (size_t)(cap ? cap * 2 : 4096));
            if (!nb) break;
            buf = nb;
            cap = cap ? cap * 2 : 4096;
        }
        got = pack_fread(buf + len, 1024, f);
        if (got <= 0) break;
        len += got;
    }
    pack_fclose(f);
    if (buf) cfg_parse(c, buf, len);
    a4_free(buf);
    return 0;
}

static void cfg_write(struct a4_cfg *c)
{
    PACKFILE *f;
    int i;
    if (!c->dirty || !c->path[0]) return;
    f = pack_fopen(c->path, F_WRITE);
    if (!f) return;
    for (i = 0; i < c->n; i++) {
        const struct a4_cfg_line *l = &c->lines[i];
        if (l->name) {
            pack_fwrite(l->name, (long)strlen(l->name), f);
            pack_fwrite(" = ", 3, f);
            pack_fwrite(l->val, (long)strlen(l->val), f);
        } else if (l->raw) pack_fwrite(l->raw, (long)strlen(l->raw), f);
        if (i < c->n - 1 || l->name || (l->raw && l->raw[0])) pack_putc('\n', f);
    }
    pack_fclose(f);
    c->dirty = 0;
}

static int cfg_find(const struct a4_cfg *c, const char *sec, const char *name)
{
    int i;
    for (i = 0; i < c->n; i++)
        if (c->lines[i].name && ustricmp(c->lines[i].sec, sec) == 0 && ustricmp(c->lines[i].name, name) == 0) return i;
    return -1;
}

static void cfg_set(struct a4_cfg *c, const char *sec, const char *name, const char *val)
{
    int i = cfg_find(c, sec, name), at, hdr = -1, n;
    struct a4_cfg_line *l;
    if (i >= 0) {
        if (!val || !*val) {                    /* an empty value takes the entry out */
            a4_free(c->lines[i].sec); a4_free(c->lines[i].name); a4_free(c->lines[i].val);
            memmove(&c->lines[i], &c->lines[i + 1], sizeof(c->lines[0]) * (size_t)(c->n - i - 1));
            c->n--;
        } else {
            char *v = a4_strdup0(val);
            if (!v) return;
            a4_free(c->lines[i].val);
            c->lines[i].val = v;
        }
        c->dirty = 1;
        return;
    }
    if (!val || !*val) return;
    /* after the section's last entry; the global section's before the first header */
    at = -1;
    for (i = 0; i < c->n; i++) {
        if (ustricmp(c->lines[i].sec, sec) != 0) continue;
        if (!c->lines[i].name && c->lines[i].raw && c->lines[i].raw[0] == '[') hdr = i;
        if (c->lines[i].name || hdr == i) at = i + 1;
    }
    if (at < 0 && !sec[0]) {
        for (at = 0; at < c->n && c->lines[at].sec[0] == 0; at++) ;
    }
    if (at < 0) {
        char head[132];
        if (c->n > 0 && (c->lines[c->n - 1].name || (c->lines[c->n - 1].raw && c->lines[c->n - 1].raw[0]))) {
            l = new_line(c, c->n);
            if (!l) return;
            l->sec = a4_strdup0(c->n > 1 ? c->lines[c->n - 2].sec : "");
            l->raw = a4_strdup0("");
        }
        l = new_line(c, c->n);
        if (!l) return;
        head[0] = '[';
        ustrzcpy(head + 1, (int)sizeof(head) - 2, sec);
        n = (int)strlen(head);
        head[n] = ']';
        head[n + 1] = 0;
        l->sec = a4_strdup0(sec);
        l->raw = a4_strdup0(head);
        at = c->n;
    }
    l = new_line(c, at);
    if (!l) return;
    l->sec = a4_strdup0(sec);
    l->name = a4_strdup0(name);
    l->val = a4_strdup0(val);
    c->dirty = 1;
}

void set_config_file(const char *filename)
{
    cfg_write(&A4S->cfg);
    cfg_free(&A4S->cfg);
    if (!filename) return;
    ustrzcpy(A4S->cfg.path, (int)sizeof(A4S->cfg.path), filename);
    cfg_load(&A4S->cfg, filename);
}

void set_config_data(const char *data, int length)
{
    cfg_write(&A4S->cfg);
    cfg_free(&A4S->cfg);
    if (data && length > 0) cfg_parse(&A4S->cfg, data, length);
}

void override_config_file(const char *filename)
{
    cfg_free(&A4S->cfg_over);
    if (filename) cfg_load(&A4S->cfg_over, filename);
}

void override_config_data(const char *data, int length)
{
    cfg_free(&A4S->cfg_over);
    if (data && length > 0) cfg_parse(&A4S->cfg_over, data, length);
}

void flush_config_file(void) { cfg_write(&A4S->cfg); }

void push_config_state(void)
{
    if (A4S->cfg_sp < A4_CFG_STACK) A4S->cfg_stack[A4S->cfg_sp] = A4S->cfg;
    else cfg_free(&A4S->cfg_stack[A4_CFG_STACK - 1]);      /* too deep: the oldest goes */
    if (A4S->cfg_sp < A4_CFG_STACK) A4S->cfg_sp++;
    else A4S->cfg_stack[A4_CFG_STACK - 1] = A4S->cfg;
    memset(&A4S->cfg, 0, sizeof(A4S->cfg));
}

void pop_config_state(void)
{
    if (A4S->cfg_sp == 0) return;               /* nothing pushed: as Allegro, no change */
    cfg_write(&A4S->cfg);
    cfg_free(&A4S->cfg);
    if (A4S->cfg_sp > 0) {
        A4S->cfg = A4S->cfg_stack[--A4S->cfg_sp];
        memset(&A4S->cfg_stack[A4S->cfg_sp], 0, sizeof(A4S->cfg_stack[0]));
    }
}

void a4_config_shutdown(void)
{
    cfg_write(&A4S->cfg);
    cfg_free(&A4S->cfg);
    cfg_free(&A4S->cfg_over);
    while (A4S->cfg_sp > 0) cfg_free(&A4S->cfg_stack[--A4S->cfg_sp]);
    drop_argv();
}

const char *get_config_string(const char *section, const char *name, const char *def)
{
    char sec[128];
    int i;
    if (!name) return def;
    sec_name(sec, (int)sizeof(sec), section);
    if ((i = cfg_find(&A4S->cfg_over, sec, name)) >= 0) return A4S->cfg_over.lines[i].val;
    if ((i = cfg_find(&A4S->cfg, sec, name)) >= 0) return A4S->cfg.lines[i].val;
    return def;
}

int get_config_int(const char *section, const char *name, int def)
{
    const char *s = get_config_string(section, name, NULL);
    return (s && *s) ? (int)parse_num(s, 0) : def;
}

int get_config_hex(const char *section, const char *name, int def)
{
    const char *s = get_config_string(section, name, NULL);
    long v;
    if (!s || !*s) return def;
    v = parse_num(s, 16);
    return v > 0x7FFFFFFFL ? -1 : (int)v;
}

int get_config_id(const char *section, const char *name, int def)
{
    const char *s = get_config_string(section, name, NULL);
    int v = 0, i;
    if (!s || !*s) return def;
    for (i = 0; i < 4; i++) v = (v << 8) | (s[i] ? utoupper((unsigned char)s[i]) : ' ');
    return v;
}

void set_config_string(const char *section, const char *name, const char *val)
{
    char sec[128];
    if (!name || !*name) return;
    sec_name(sec, (int)sizeof(sec), section);
    cfg_set(&A4S->cfg, sec, name, val);
}

void set_config_int(const char *section, const char *name, int val)
{
    char b[16];
    fmt_num(b, val < 0 ? 0UL - (unsigned long)val : (unsigned long)val, val < 0, 10);
    set_config_string(section, name, b);
}

void set_config_hex(const char *section, const char *name, int val)
{
    char b[16];
    if (val >= 0) fmt_num(b, (unsigned long)val, 0, 16);
    else ustrzcpy(b, (int)sizeof(b), "-1");
    set_config_string(section, name, b);
}

void set_config_id(const char *section, const char *name, int val)
{
    char b[5];
    int i, n = 0;
    for (i = 3; i >= 0; i--) { int ch = (val >> (i * 8)) & 255; if (ch && ch != ' ') b[n++] = (char)ch; }
    b[n] = 0;
    set_config_string(section, name, b);
}

static void drop_argv(void)
{
    a4_free(A4S->cfg_argv_buf); a4_free(A4S->cfg_argv);
    A4S->cfg_argv_buf = NULL; A4S->cfg_argv = NULL;
}

/* the value cut at spaces; "quoted words" stay one; valid until the next call */
char **get_config_argv(const char *section, const char *name, int *argc)
{
    const char *v = get_config_string(section, name, NULL);
    long n;
    int count = 0;
    char *p;
    if (argc) *argc = 0;
    drop_argv();
    if (!v) return NULL;
    n = (long)strlen(v);
    A4S->cfg_argv_buf = dupn(v, (int)n);
    A4S->cfg_argv = (char **)a4_calloc(sizeof(char *) * (size_t)(n / 2 + 2));
    if (!A4S->cfg_argv_buf || !A4S->cfg_argv) { drop_argv(); return NULL; }
    p = A4S->cfg_argv_buf;
    for (;;) {
        while (*p && (is_space((unsigned char)*p) || *p == '\n')) p++;
        if (!*p) break;
        if (*p == '"') {
            p++;
            A4S->cfg_argv[count++] = p;
            while (*p && *p != '"') p++;
        } else {
            A4S->cfg_argv[count++] = p;
            while (*p && !is_space((unsigned char)*p) && *p != '\n') p++;
        }
        if (*p) *p++ = 0;
    }
    if (argc) *argc = count;
    return A4S->cfg_argv;
}
