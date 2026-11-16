/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * FLI and FLC animations, as Allegro 4 plays them: open_fli/open_memory_fli,
 * next_fli_frame into fli_bitmap and fli_palette (with the rows and colours
 * each frame changed), close_fli, and play_fli/play_memory_fli. Written from
 * the Autodesk Animator file format (8-bit frames; chunks COLOR_256,
 * COLOR_64, DELTA_FLC, DELTA_FLI, BLACK, BYTE_RUN, FLI_COPY; postage stamps
 * and unknown chunks skipped). Game-side, in liballeg.a: it decodes with the
 * game's own C library and draws through allegro4.library's calls.
 */
#include <allegro.h>

BITMAP *fli_bitmap;
PALETTE fli_palette;
int fli_bmp_dirty_from = INT_MAX, fli_bmp_dirty_to = INT_MIN;
int fli_pal_dirty_from = INT_MAX, fli_pal_dirty_to = INT_MIN;
int fli_frame;
volatile int fli_timer;

#define FLI_MAGIC 0xAF11
#define FLC_MAGIC 0xAF12
#define FRAME_MAGIC 0xF1FA

static struct {
    int open;
    unsigned char *data;        /* the whole file */
    long size;
    int own;                    /* data is ours to free (open_fli) */
    int frames, w, h, speed_ms;
    long first, second;         /* offsets of frames 1 and 2 */
    long pos;                   /* the next frame */
    int timer_on;
} f;

static unsigned rd16(const unsigned char *p) { return p[0] | (p[1] << 8); }
static unsigned long rd32(const unsigned char *p) { return (unsigned long)p[0] | ((unsigned long)p[1] << 8) | ((unsigned long)p[2] << 16) | ((unsigned long)p[3] << 24); }

static void tick(void) { fli_timer++; }

static void dirty_rows(int from, int to)
{
    if (from < fli_bmp_dirty_from) fli_bmp_dirty_from = from;
    if (to > fli_bmp_dirty_to) fli_bmp_dirty_to = to;
}

static void dirty_cols(int from, int to)
{
    if (from < fli_pal_dirty_from) fli_pal_dirty_from = from;
    if (to > fli_pal_dirty_to) fli_pal_dirty_to = to;
}

void reset_fli_variables(void)
{
    fli_bmp_dirty_from = INT_MAX; fli_bmp_dirty_to = INT_MIN;
    fli_pal_dirty_from = INT_MAX; fli_pal_dirty_to = INT_MIN;
}

static int start(void)
{
    const unsigned char *h = f.data;
    unsigned magic;
    if (f.size < 128) return FLI_ERROR;
    magic = rd16(h + 4);
    if (magic != FLI_MAGIC && magic != FLC_MAGIC) return FLI_ERROR;
    f.frames = rd16(h + 6);
    f.w = rd16(h + 8); f.h = rd16(h + 10);
    if (rd16(h + 12) != 8 && rd16(h + 12) != 0) return FLI_ERROR;
    if (f.w <= 0 || f.h <= 0 || f.w > 4096 || f.h > 4096) return FLI_ERROR;
    if (magic == FLI_MAGIC) {
        f.speed_ms = (int)(rd16(h + 16) * 1000L / 70);      /* jiffies of 1/70 s */
        f.first = 128;
        f.second = 0;
    } else {
        f.speed_ms = (int)rd32(h + 16);
        f.first = (long)rd32(h + 80);
        f.second = (long)rd32(h + 84);
        if (f.first <= 0) f.first = 128;
    }
    if (f.speed_ms <= 0) f.speed_ms = 1;
    fli_bitmap = create_bitmap(f.w, f.h);
    if (!fli_bitmap) return FLI_ERROR;
    clear_bitmap(fli_bitmap);
    memset(fli_palette, 0, sizeof(PALETTE));
    f.pos = f.first;
    fli_frame = 0;
    fli_timer = 0;
    reset_fli_variables();
    if (install_int_ex(tick, MSEC_TO_TIMER(f.speed_ms)) == 0) f.timer_on = 1;
    fli_timer = 1;                                          /* the first frame is due now */
    f.open = 1;
    return FLI_OK;
}

void close_fli(void)
{
    if (f.timer_on) { remove_int(tick); f.timer_on = 0; }
    if (fli_bitmap) { destroy_bitmap(fli_bitmap); fli_bitmap = NULL; }
    if (f.own && f.data) free(f.data);
    memset(&f, 0, sizeof(f));
    fli_timer = 0;
}

int open_memory_fli(void *fli_data)
{
    int r;
    if (f.open) close_fli();
    if (!fli_data) return FLI_ERROR;
    f.data = (unsigned char *)fli_data;
    f.size = (long)rd32(f.data);
    f.own = 0;
    r = start();
    if (r != FLI_OK) close_fli();
    return r;
}

int open_fli(const char *filename)
{
    PACKFILE *pf;
    long n;
    int r;
    if (f.open) close_fli();
    n = file_size_ex(filename);
    if (n < 128) return FLI_ERROR;
    pf = pack_fopen(filename, F_READ);
    if (!pf) return FLI_ERROR;
    f.data = (unsigned char *)malloc(n);
    if (!f.data) { pack_fclose(pf); return FLI_ERROR; }
    f.own = 1;
    f.size = pack_fread(f.data, n, pf);
    pack_fclose(pf);
    if (f.size != n) { close_fli(); return FLI_ERROR; }
    r = start();
    if (r != FLI_OK) close_fli();
    return r;
}

/* ---- the chunks ------------------------------------------------------------------------ */

static void do_color(const unsigned char *p, const unsigned char *end, int shift)
{
    int packets, idx = 0, i;
    if (p + 2 > end) return;
    packets = rd16(p); p += 2;
    while (packets-- > 0 && p + 2 <= end) {
        int count;
        idx += p[0];
        count = p[1] ? p[1] : 256;
        p += 2;
        for (i = 0; i < count && idx < 256 && p + 3 <= end; i++, idx++, p += 3) {
            fli_palette[idx].r = (unsigned char)((p[0] >> shift) & 63);
            fli_palette[idx].g = (unsigned char)((p[1] >> shift) & 63);
            fli_palette[idx].b = (unsigned char)((p[2] >> shift) & 63);
            dirty_cols(idx, idx);
        }
    }
}

static void do_brun(const unsigned char *p, const unsigned char *end)
{
    int y;
    for (y = 0; y < f.h; y++) {
        unsigned char *row = fli_bitmap->line[y];
        int x = 0;
        if (p >= end) break;
        p++;                                                /* the packet count: the width decides */
        while (x < f.w && p < end) {
            int c = (signed char)*p++;
            if (c > 0) {
                if (p >= end) break;
                while (c-- > 0 && x < f.w) row[x++] = *p;
                p++;
            } else if (c < 0) {
                c = -c;
                while (c-- > 0 && x < f.w && p < end) row[x++] = *p++;
            }
        }
    }
    dirty_rows(0, f.h - 1);
}

static void do_delta_fli(const unsigned char *p, const unsigned char *end)
{
    int y, lines;
    if (p + 4 > end) return;
    y = rd16(p); lines = rd16(p + 2); p += 4;
    for (; lines-- > 0 && y < f.h && p < end; y++) {
        unsigned char *row = fli_bitmap->line[y];
        int packets = *p++, x = 0;
        while (packets-- > 0 && p + 2 <= end) {
            int c;
            x += *p++;
            c = (signed char)*p++;
            if (c > 0) { while (c-- > 0 && p < end) { if (x < f.w) row[x] = *p; x++; p++; } }
            else if (c < 0) { c = -c; if (p >= end) break; while (c-- > 0) { if (x < f.w) row[x] = *p; x++; } p++; }
        }
        dirty_rows(y, y);
    }
}

static void do_delta_flc(const unsigned char *p, const unsigned char *end)
{
    int lines, y = 0;
    if (p + 2 > end) return;
    lines = rd16(p); p += 2;
    while (lines > 0 && y < f.h && p + 2 <= end) {
        unsigned w = rd16(p);
        p += 2;
        if ((w & 0xC000) == 0xC000) { y += 65536 - w; continue; }    /* skip lines */
        if ((w & 0xC000) == 0x8000) {                                /* the line's last pixel */
            if (f.w > 0) { fli_bitmap->line[y][f.w - 1] = (unsigned char)(w & 255); dirty_rows(y, y); }
            if (p + 2 > end) break;
            w = rd16(p); p += 2;
        }
        {
            int packets = (int)w, x = 0;
            unsigned char *row = fli_bitmap->line[y];
            while (packets-- > 0 && p + 2 <= end) {
                int c;
                x += *p++;
                c = (signed char)*p++;
                if (c > 0) {
                    while (c-- > 0 && p + 2 <= end) {
                        if (x < f.w) row[x] = p[0];
                        if (x + 1 < f.w) row[x + 1] = p[1];
                        x += 2; p += 2;
                    }
                } else if (c < 0) {
                    c = -c;
                    if (p + 2 > end) break;
                    while (c-- > 0) {
                        if (x < f.w) row[x] = p[0];
                        if (x + 1 < f.w) row[x + 1] = p[1];
                        x += 2;
                    }
                    p += 2;
                }
            }
            dirty_rows(y, y);
        }
        y++;
        lines--;
    }
}

static void do_copy(const unsigned char *p, const unsigned char *end)
{
    int y;
    for (y = 0; y < f.h && p + f.w <= end; y++, p += f.w) memcpy(fli_bitmap->line[y], p, f.w);
    dirty_rows(0, f.h - 1);
}

static int read_frame(void)
{
    const unsigned char *fr, *end, *p;
    unsigned long size;
    int chunks;
    for (;;) {
        if (f.pos + 16 > f.size) return FLI_ERROR;
        fr = f.data + f.pos;
        size = rd32(fr);
        if (size < 16 || f.pos + (long)size > f.size) return FLI_ERROR;
        if (rd16(fr + 4) == FRAME_MAGIC) break;
        f.pos += size;                                      /* a prefix chunk or other: skip */
    }
    end = fr + size;
    chunks = rd16(fr + 6);
    p = fr + 16;
    while (chunks-- > 0 && p + 6 <= end) {
        unsigned long cs = rd32(p);
        const unsigned char *cend;
        if (cs < 6 || p + cs > end) cs = (unsigned long)(end - p);
        cend = p + cs;
        switch (rd16(p + 4)) {
        case 4: do_color(p + 6, cend, 2); break;           /* COLOR_256: 8-bit values */
        case 11: do_color(p + 6, cend, 0); break;          /* COLOR_64 */
        case 7: do_delta_flc(p + 6, cend); break;
        case 12: do_delta_fli(p + 6, cend); break;
        case 13: clear_bitmap(fli_bitmap); dirty_rows(0, f.h - 1); break;
        case 15: do_brun(p + 6, cend); break;
        case 16: do_copy(p + 6, cend); break;
        default: break;                                     /* postage stamp and the rest */
        }
        p = cend;
    }
    f.pos += size;
    return FLI_OK;
}

int next_fli_frame(int loop)
{
    int r;
    if (!f.open) return FLI_NOT_OPEN;
    fli_timer--;
    if (fli_frame >= f.frames) {
        if (!loop) return FLI_EOF;
        /* the ring frame after the last one leads back to frame 2 */
        if (f.second > 0 && f.pos + 16 <= f.size && rd16(f.data + f.pos + 4) == FRAME_MAGIC) {
            r = read_frame();
            if (r != FLI_OK) return r;
            f.pos = f.second;
            fli_frame = 1;
            return FLI_OK;
        }
        f.pos = f.first;                                    /* no ring frame: from the start */
        fli_frame = 0;
    }
    r = read_frame();
    if (r != FLI_OK) return r;
    fli_frame++;
    if (fli_frame == 1 && !f.second) f.second = f.pos;
    return FLI_OK;
}

static int play(BITMAP *bmp, int loop, int (*callback)(void))
{
    int r = FLI_OK;
    while (r == FLI_OK) {
        r = next_fli_frame(loop);
        if (r != FLI_OK) break;
        if (fli_pal_dirty_from <= fli_pal_dirty_to) set_palette_range(fli_palette, fli_pal_dirty_from, fli_pal_dirty_to, TRUE);
        if (fli_bmp_dirty_from <= fli_bmp_dirty_to)
            blit(fli_bitmap, bmp, 0, fli_bmp_dirty_from, 0, fli_bmp_dirty_from, fli_bitmap->w, fli_bmp_dirty_to - fli_bmp_dirty_from + 1);
        reset_fli_variables();
        if (callback) { int c = callback(); if (c) { r = c; break; } }
        while (fli_timer <= 0) rest(1);
    }
    close_fli();
    return r == FLI_EOF ? FLI_OK : r;
}

int play_fli(const char *filename, BITMAP *bmp, int loop, int (*callback)(void))
{
    int r = open_fli(filename);
    if (r != FLI_OK) return r;
    return play(bmp, loop, callback);
}

int play_memory_fli(void *fli_data, BITMAP *bmp, int loop, int (*callback)(void))
{
    int r = open_memory_fli(fli_data);
    if (r != FLI_OK) return r;
    return play(bmp, loop, callback);
}
