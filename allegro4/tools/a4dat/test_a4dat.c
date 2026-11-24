/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * test_a4dat.sh's helper, on the host build of allegro4 (build-host.sh):
 *   test_a4dat make DIR         the source files: a picture, a font grid, a WAV, a MIDI file, raw bytes
 *   test_a4dat check DIR FILE   reads FILE (dat's output) with allegro4's own reader and compares each
 *                               object with what its source file loads as
 */
#include <allegro.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int checks, failures;
#define CHECK(c) do { checks++; if (!(c)) { failures++; fprintf(stderr, "test_a4dat: CHECK(%s) failed (line %d)\n", #c, __LINE__); } } while (0)

static char path[4096];
static const char *in(const char *dir, const char *name) { snprintf(path, sizeof(path), "%s/%s", dir, name); return path; }

static void put16(FILE *f, int v) { fputc(v & 255, f); fputc((v >> 8) & 255, f); }
static void put32(FILE *f, long v) { put16(f, (int)(v & 0xFFFF)); put16(f, (int)((v >> 16) & 0xFFFF)); }
static void mput32(FILE *f, long v) { fputc((int)(v >> 24) & 255, f); fputc((int)(v >> 16) & 255, f); fputc((int)(v >> 8) & 255, f); fputc((int)v & 255, f); }

#define GW 5
#define GH 7
#define GLYPHS 3

static void make(const char *dir)
{
    PALETTE pal;
    BITMAP *b;
    FILE *f;
    int x, y, i;
    for (i = 0; i < 256; i++) { pal[i].r = (unsigned char)(i & 63); pal[i].g = (unsigned char)((i * 3) & 63); pal[i].b = (unsigned char)(63 - (i & 63)); pal[i].filler = 0; }
    /* a 13 x 5 picture, odd width */
    b = create_bitmap_ex(8, 13, 5);
    for (y = 0; y < 5; y++) for (x = 0; x < 13; x++) putpixel(b, x, y, (x * 7 + y * 31) & 255);
    save_pcx(in(dir, "pic.pcx"), b, pal);
    destroy_bitmap(b);
    /* a font grid: border 255, three 5 x 7 glyphs in colours 1 to 9, 0 the clear pixels */
    b = create_bitmap_ex(8, 1 + GLYPHS * (GW + 1), GH + 2);
    clear_to_color(b, 255);
    for (i = 0; i < GLYPHS; i++)
        for (y = 0; y < GH; y++)
            for (x = 0; x < GW; x++) putpixel(b, 1 + i * (GW + 1) + x, 1 + y, (x + y + i) % 3 ? 1 + (x * y + i) % 9 : 0);
    save_pcx(in(dir, "font.pcx"), b, pal);
    destroy_bitmap(b);
    /* an 8-bit mono WAV of 100 frames */
    f = fopen(in(dir, "beep.wav"), "wb");
    fwrite("RIFF", 1, 4, f); put32(f, 36 + 100); fwrite("WAVEfmt ", 1, 8, f);
    put32(f, 16); put16(f, 1); put16(f, 1); put32(f, 11025); put32(f, 11025); put16(f, 1); put16(f, 8);
    fwrite("data", 1, 4, f); put32(f, 100);
    for (i = 0; i < 100; i++) fputc((i * 13) & 255, f);
    fclose(f);
    /* a MIDI file: format 1, two tracks */
    f = fopen(in(dir, "tune.mid"), "wb");
    fwrite("MThd", 1, 4, f); mput32(f, 6); fputc(0, f); fputc(1, f); fputc(0, f); fputc(2, f); fputc(0, f); fputc(96, f);
    for (i = 0; i < 2; i++) {
        static const unsigned char ev[] = {0x00, 0x90, 0x3C, 0x40, 0x60, 0x80, 0x3C, 0x00, 0x00, 0xFF, 0x2F, 0x00};
        fwrite("MTrk", 1, 4, f); mput32(f, (long)sizeof(ev)); fwrite(ev, 1, sizeof(ev), f);
    }
    fclose(f);
    f = fopen(in(dir, "raw.bin"), "wb");
    for (i = 0; i < 300; i++) fputc((i * 5) & 255, f);
    fclose(f);
}

static DATAFILE *named(DATAFILE *d, const char *name)
{
    DATAFILE *o = find_datafile_object(d, name);
    CHECK(o != NULL);
    if (!o) fprintf(stderr, "test_a4dat: no %s\n", name);
    return o;
}

static void check_objects(DATAFILE *d, const char *dir)
{
    DATAFILE *o;
    PALETTE pal;
    BITMAP *src;
    long n;
    int x, y, i;
    src = load_pcx(in(dir, "pic.pcx"), pal);
    if ((o = named(d, "PIC_PCX"))) {
        BITMAP *b = (BITMAP *)o->dat;
        CHECK(o->type == DAT_BITMAP);
        CHECK(b->w == 13 && b->h == 5 && bitmap_color_depth(b) == 8);
        for (y = 0; y < 5; y++) CHECK(!memcmp(b->line[y], src->line[y], 13));
    }
    if ((o = named(d, "pal.pcx"))) {        /* -t pal of a copy of pic.pcx, its name kept by -k */
        RGB *p = (RGB *)o->dat;
        CHECK(o->type == DAT_PALETTE);
        for (i = 0; i < 256; i++) CHECK(p[i].r == pal[i].r && p[i].g == pal[i].g && p[i].b == pal[i].b);
    }
    destroy_bitmap(src);
    if ((o = named(d, "FONT_PCX"))) {
        FONT *f = (FONT *)o->dat;
        BITMAP *grid = load_pcx(in(dir, "font.pcx"), pal), *out = create_bitmap_ex(8, GW, GH);
        CHECK(o->type == DAT_FONT);
        CHECK(get_font_range_begin(f, 0) == 32 && get_font_range_end(f, 0) == 32 + GLYPHS - 1);
        CHECK(is_color_font(f) && text_height(f) == GH);
        for (i = 0; i < GLYPHS; i++) {
            char s[2] = {(char)(32 + i), 0};
            CHECK(text_length(f, s) == GW);
            clear_to_color(out, 0);
            textout_ex(out, f, s, 0, 0, -1, -1);
            for (y = 0; y < GH; y++) for (x = 0; x < GW; x++) CHECK(getpixel(out, x, y) == getpixel(grid, 1 + i * (GW + 1) + x, 1 + y));
        }
        destroy_bitmap(grid); destroy_bitmap(out);
    }
    if ((o = named(d, "BEEP_WAV"))) {
        SAMPLE *s = (SAMPLE *)o->dat, *w = load_wav(in(dir, "beep.wav"));
        CHECK(o->type == DAT_SAMPLE);
        CHECK(s->bits == 8 && !s->stereo && s->freq == 11025 && s->len == 100);
        CHECK(w && !memcmp(s->data, w->data, 100));
        destroy_sample(w);
    }
    if ((o = named(d, "TUNE_MID"))) {
        MIDI *m = (MIDI *)o->dat, *w = load_midi(in(dir, "tune.mid"));
        CHECK(o->type == DAT_MIDI);
        CHECK(w && m->divisions == w->divisions);
        for (i = 0; w && i < MIDI_TRACKS; i++) {
            CHECK((m->track[i].len > 0 ? m->track[i].len : 0) == (w->track[i].data ? w->track[i].len : 0));
            if (w->track[i].data && w->track[i].len > 0) CHECK(m->track[i].data && !memcmp(m->track[i].data, w->track[i].data, (size_t)w->track[i].len));
        }
        destroy_midi(w);
    }
    if ((o = named(d, "RAW_BIN"))) {
        CHECK(o->type == DAT_ID('R', 'A', 'W', ' ') && o->size == 300);
        for (n = 0; n < 300; n++) CHECK(((unsigned char *)o->dat)[n] == ((n * 5) & 255));
    }
    if ((o = named(d, "DATA_BIN"))) CHECK(o->type == DAT_DATA && o->size == 300);
}

int main(int argc, char **argv)
{
    DATAFILE *d, *o;
    if (install_allegro(SYSTEM_NONE, &errno, atexit) != 0) return 2;
    set_color_depth(8);
    set_color_conversion(COLORCONV_NONE);
    if (argc == 3 && !strcmp(argv[1], "make")) { make(argv[2]); return 0; }
    if (argc != 4 || strcmp(argv[1], "check")) { fprintf(stderr, "usage: test_a4dat make DIR | check DIR FILE.dat\n"); return 2; }
    d = load_datafile(argv[3]);
    CHECK(d != NULL);
    if (d) {
        int n = 0;
        check_objects(d, argv[2]);
        /* the nested datafile: the same objects, through find_datafile_object and "file.dat#SUB/OBJ" */
        if ((o = named(d, "SUB_DAT"))) {
            CHECK(o->type == DAT_FILE);
            check_objects((DATAFILE *)o->dat, argv[2]);
        }
        while (d[n].type != DAT_END) n++;
        CHECK(n == 9);                  /* 8 objects and the grabber's "info" */
        CHECK(d[n - 1].type == DAT_ID('i', 'n', 'f', 'o'));
        unload_datafile(d);
    }
    snprintf(path, sizeof(path), "%s", argv[3]);
    o = load_datafile_object(path, "SUB_DAT/TUNE_MID");
    CHECK(o && o->type == DAT_MIDI);
    unload_datafile_object(o);
    o = load_datafile_object(path, "FONT_PCX");
    CHECK(o && o->type == DAT_FONT);
    unload_datafile_object(o);
    printf("test_a4dat %s: %d checks, %d failed\n", argv[3], checks, failures);
    return failures ? 1 : 0;
}
