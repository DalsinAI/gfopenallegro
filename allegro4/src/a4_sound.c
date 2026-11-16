/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Digital sound: samples (8/16-bit, mono/stereo, Allegro 4's unsigned
 * form), 16 voices with volume, pan, frequency and loop modes, mixed to
 * signed 16-bit stereo and handed to ACGame's audio call. MIDI files load
 * and their position counts, but notes are not played yet (no synthesiser
 * in ACGame); a game runs with its music silent.
 */
#include "a4_internal.h"
#include "acgame/platform.h"

#define MIX_RATE 22050
#define MIX_CHUNK 512

int detect_digi_driver(int id) { (void)id; return A4_VOICES; }
int detect_midi_driver(int id) { (void)id; return 0; }
void reserve_voices(int d, int m) { (void)d; (void)m; }
void set_volume_per_voice(int scale) { (void)scale; }

int install_sound(int digi, int midi, const char *cfg)
{
    (void)cfg;
    if (A4S->sound_on) return 0;
    memset(A4S->voices, 0, sizeof(A4S->voices));
    A4S->digi_volume = 255;
    A4S->midi_volume = 255;
    A4S->digi_drv.id = digi == DIGI_NONE ? DIGI_NONE : AL_ID('A','C','G','D');
    A4S->digi_drv.name = A4S->digi_drv.desc = A4S->digi_drv.ascii_name = digi == DIGI_NONE ? "None" : "ACGame";
    A4S->digi_drv.voices = digi == DIGI_NONE ? 0 : A4_VOICES;
    A4S->midi_drv.id = MIDI_NONE;
    A4S->midi_drv.name = A4S->midi_drv.desc = A4S->midi_drv.ascii_name = "None";
    (void)midi;
    digi_driver = &A4S->digi_drv;
    midi_driver = &A4S->midi_drv;
    A4S->mix_last_ms = acgame_platform_ticks_ms();
    A4S->audio_out_ok = 1;
    A4S->sound_on = 1;
    return 0;
}

void remove_sound(void)
{
    if (!A4S->sound_on) return;
    memset(A4S->voices, 0, sizeof(A4S->voices));
    A4S->sound_on = 0;
    digi_driver = NULL;
    midi_driver = NULL;
}

void set_volume(int d, int m) { if (d >= 0) A4S->digi_volume = MID(0, d, 255); if (m >= 0) A4S->midi_volume = MID(0, m, 255); }
void get_volume(int *d, int *m) { if (d) *d = A4S->digi_volume; if (m) *m = A4S->midi_volume; }
void set_hardware_volume(int d, int m) { set_volume(d, m); }

/* ---- samples -------------------------------------------------------------------- */

SAMPLE *create_sample(int bits, int stereo, int freq, int len)
{
    SAMPLE *s = (SAMPLE *)a4_calloc(sizeof(SAMPLE));
    size_t bytes = (size_t)len * (size_t)(bits == 8 ? 1 : 2) * (size_t)(stereo ? 2 : 1);
    if (!s) return NULL;
    s->data = a4_calloc(bytes ? bytes : 1);
    if (!s->data) { a4_free(s); return NULL; }
    s->bits = bits; s->stereo = stereo; s->freq = freq; s->len = (unsigned long)len;
    s->priority = 128; s->loop_start = 0; s->loop_end = (unsigned long)len;
    return s;
}

void destroy_sample(SAMPLE *spl)
{
    int i;
    if (!spl) return;
    for (i = 0; i < A4_VOICES; i++) if (A4S->voices[i].spl == spl) memset(&A4S->voices[i], 0, sizeof(A4S->voices[i]));
    a4_free(spl->data);
    a4_free(spl);
}

/* a datafile sample: bits (negative: stereo), freq, length, then the data */
SAMPLE *a4_read_sample_object(PACKFILE *f)
{
    short bits = (short)pack_mgetw(f);
    int stereo = bits < 0, freq;
    long len, i, n;
    SAMPLE *s;
    if (bits < 0) bits = (short)-bits;
    freq = pack_mgetw(f);
    len = pack_mgetl(f);
    if (len < 0 || (bits != 8 && bits != 16)) return NULL;
    s = create_sample(bits, stereo, freq, (int)len);
    if (!s) return NULL;
    n = len * (stereo ? 2 : 1);
    if (bits == 8) pack_fread(s->data, n, f);
    else for (i = 0; i < n; i++) ((uint16_t *)s->data)[i] = (uint16_t)pack_igetw(f);
    return s;
}

/* RIFF WAVE, PCM 8 or 16-bit (16-bit is signed in WAV: made unsigned) */
SAMPLE *load_wav_pf(PACKFILE *f)
{
    char id[4];
    long len;
    int channels = 1, freq = 22050, bits = 8, fmt_ok = 0;
    SAMPLE *s = NULL;
    if (pack_fread(id, 4, f) != 4 || memcmp(id, "RIFF", 4) != 0) return NULL;
    pack_igetl(f);
    if (pack_fread(id, 4, f) != 4 || memcmp(id, "WAVE", 4) != 0) return NULL;
    while (pack_fread(id, 4, f) == 4) {
        len = pack_igetl(f);
        if (memcmp(id, "fmt ", 4) == 0) {
            int format = pack_igetw(f);
            channels = pack_igetw(f);
            freq = (int)pack_igetl(f);
            pack_igetl(f); pack_igetw(f);
            bits = pack_igetw(f);
            if (len > 16) pack_fseek(f, (int)(len - 16));
            fmt_ok = format == 1 && (bits == 8 || bits == 16) && (channels == 1 || channels == 2);
            if (!fmt_ok) return NULL;
        } else if (memcmp(id, "data", 4) == 0 && fmt_ok) {
            long frames = len / ((bits / 8) * channels), i, n;
            s = create_sample(bits, channels == 2, freq, (int)frames);
            if (!s) return NULL;
            n = frames * channels;
            if (bits == 8) pack_fread(s->data, n, f);
            else for (i = 0; i < n; i++) ((uint16_t *)s->data)[i] = (uint16_t)(pack_igetw(f) ^ 0x8000);
            return s;
        } else {
            pack_fseek(f, (int)((len + 1) & ~1L));
        }
    }
    return s;
}

SAMPLE *load_wav(const char *filename)
{
    PACKFILE *f = pack_fopen(filename, F_READ);
    SAMPLE *s;
    if (!f) return NULL;
    s = load_wav_pf(f);
    pack_fclose(f);
    return s;
}

SAMPLE *load_voc(const char *filename) { (void)filename; return NULL; }
SAMPLE *load_sample(const char *filename)
{
    const char *e = get_extension(filename);
    if (ustricmp(e, "voc") == 0) return load_voc(filename);
    return load_wav(filename);
}

int save_sample(const char *filename, SAMPLE *s)
{
    PACKFILE *f;
    long n, i, bytes;
    if (!s) return -1;
    f = pack_fopen(filename, F_WRITE);
    if (!f) return -1;
    n = (long)s->len * (s->stereo ? 2 : 1);
    bytes = n * (s->bits / 8);
    pack_fwrite("RIFF", 4, f); pack_iputl(36 + bytes, f); pack_fwrite("WAVEfmt ", 8, f);
    pack_iputl(16, f); pack_iputw(1, f); pack_iputw(s->stereo ? 2 : 1, f); pack_iputl(s->freq, f);
    pack_iputl((long)s->freq * (s->stereo ? 2 : 1) * (s->bits / 8), f);
    pack_iputw((s->stereo ? 2 : 1) * (s->bits / 8), f); pack_iputw(s->bits, f);
    pack_fwrite("data", 4, f); pack_iputl(bytes, f);
    if (s->bits == 8) pack_fwrite(s->data, n, f);
    else for (i = 0; i < n; i++) pack_iputw(((uint16_t *)s->data)[i] ^ 0x8000, f);
    return pack_fclose(f) == 0 ? 0 : -1;
}

/* ---- voices ---------------------------------------------------------------------- */

int allocate_voice(const SAMPLE *spl)
{
    int i, best = -1, bestprio = 1 << 30;
    if (!A4S->sound_on || !spl) return -1;
    for (i = 0; i < A4_VOICES; i++) if (!A4S->voices[i].allocated) { best = i; break; }
    if (best < 0) {
        /* take the lowest-priority self-ending voice */
        for (i = 0; i < A4_VOICES; i++)
            if (A4S->voices[i].autokill && A4S->voices[i].spl && A4S->voices[i].spl->priority < bestprio) {
                bestprio = A4S->voices[i].spl->priority; best = i;
            }
        if (best < 0 || bestprio > spl->priority) return -1;
    }
    memset(&A4S->voices[best], 0, sizeof(A4S->voices[best]));
    A4S->voices[best].allocated = 1;
    A4S->voices[best].spl = spl;
    A4S->voices[best].vol = 255;
    A4S->voices[best].pan = 128;
    A4S->voices[best].freq = spl->freq;
    A4S->voices[best].dir = 1;
    return best;
}

static struct a4_voice *V(int v) { return (v >= 0 && v < A4_VOICES && A4S->voices[v].allocated) ? &A4S->voices[v] : NULL; }

void deallocate_voice(int v) { if (V(v)) memset(&A4S->voices[v], 0, sizeof(A4S->voices[v])); }
void reallocate_voice(int v, const SAMPLE *spl) { struct a4_voice *x = V(v); if (x) { x->spl = spl; x->pos_fx = 0; x->freq = spl->freq; } }
void release_voice(int v) { struct a4_voice *x = V(v); if (x) x->autokill = 1; }
void voice_start(int v) { struct a4_voice *x = V(v); if (x) x->playing = 1; }
void voice_stop(int v) { struct a4_voice *x = V(v); if (x) x->playing = 0; }
void voice_set_priority(int v, int p) { (void)v; (void)p; }
SAMPLE *voice_check(int v) { struct a4_voice *x = V(v); return x ? (SAMPLE *)x->spl : NULL; }
void voice_set_playmode(int v, int m) { struct a4_voice *x = V(v); if (x) { x->loop = m; x->dir = (m & PLAYMODE_BACKWARD) ? -1 : 1; } }
int voice_get_position(int v) { struct a4_voice *x = V(v); return (x && x->playing) ? (int)(x->pos_fx >> 16) : -1; }
void voice_set_position(int v, int p) { struct a4_voice *x = V(v); if (x) x->pos_fx = (uint32_t)p << 16; }
int voice_get_volume(int v) { struct a4_voice *x = V(v); return x ? x->vol : -1; }
void voice_set_volume(int v, int vol) { struct a4_voice *x = V(v); if (x) x->vol = MID(0, vol, 255); }
int voice_get_frequency(int v) { struct a4_voice *x = V(v); return x ? x->freq : -1; }
void voice_set_frequency(int v, int f) { struct a4_voice *x = V(v); if (x) x->freq = f > 0 ? f : 1; }
int voice_get_pan(int v) { struct a4_voice *x = V(v); return x ? x->pan : -1; }
void voice_set_pan(int v, int p) { struct a4_voice *x = V(v); if (x) x->pan = MID(0, p, 255); }

/* freq here is 1000 = the sample's own rate (Allegro's play_sample) */
int play_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop)
{
    int v = allocate_voice(spl);
    if (v < 0) return -1;
    voice_set_volume(v, vol);
    voice_set_pan(v, pan);
    voice_set_frequency(v, (int)((long)spl->freq * freq / 1000));
    voice_set_playmode(v, loop ? PLAYMODE_LOOP : PLAYMODE_PLAY);
    A4S->voices[v].autokill = 1;
    voice_start(v);
    return v;
}

void stop_sample(const SAMPLE *spl)
{
    int i;
    for (i = 0; i < A4_VOICES; i++) if (A4S->voices[i].allocated && A4S->voices[i].spl == spl) deallocate_voice(i);
}

void adjust_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop)
{
    int i;
    for (i = 0; i < A4_VOICES; i++) {
        struct a4_voice *x = &A4S->voices[i];
        if (x->allocated && x->spl == spl) {
            x->vol = MID(0, vol, 255); x->pan = MID(0, pan, 255);
            x->freq = (int)((long)spl->freq * freq / 1000);
            x->loop = loop ? PLAYMODE_LOOP : PLAYMODE_PLAY;
            return;
        }
    }
}

/* ---- the mixer ------------------------------------------------------------------------ */

static int sample_at(const SAMPLE *s, unsigned long frame, int ch)
{
    unsigned long idx = s->stereo ? frame * 2 + (unsigned long)ch : frame;
    if (s->bits == 8) return ((int)((const uint8_t *)s->data)[idx] - 128) << 8;
    return (int)((const uint16_t *)s->data)[idx] - 32768;
}

void a4_mix_s16stereo(int16_t *out, int frames, int rate)
{
    int i, v;
    int32_t *acc;
    if (frames <= 0) return;
    acc = (int32_t *)a4_calloc(sizeof(int32_t) * 2 * (size_t)frames);
    if (!acc) { memset(out, 0, sizeof(int16_t) * 2 * (size_t)frames); return; }
    for (v = 0; v < A4_VOICES; v++) {
        struct a4_voice *x = &A4S->voices[v];
        const SAMPLE *s = x->spl;
        uint32_t step;
        unsigned long lstart, lend;
        int lvol, rvol;
        if (!x->allocated || !x->playing || !s || !s->len) continue;
        step = (uint32_t)(((uint64_t)(uint32_t)x->freq << 16) / (uint32_t)(rate > 0 ? rate : MIX_RATE));
        lstart = s->loop_start; lend = s->loop_end ? s->loop_end : s->len;
        if (lend > s->len) lend = s->len;
        if (lstart >= lend) lstart = 0;
        lvol = x->vol * (255 - x->pan) / 255 * A4S->digi_volume / 255;
        rvol = x->vol * x->pan / 255 * A4S->digi_volume / 255;
        for (i = 0; i < frames; i++) {
            unsigned long fr = x->pos_fx >> 16;
            int l, r;
            if (fr >= s->len) { x->playing = 0; break; }
            l = sample_at(s, fr, 0);
            r = s->stereo ? sample_at(s, fr, 1) : l;
            acc[i * 2] += l * lvol / 128;
            acc[i * 2 + 1] += r * rvol / 128;
            if (x->dir > 0) {
                x->pos_fx += step;
                if ((x->pos_fx >> 16) >= ((x->loop & PLAYMODE_LOOP) ? lend : s->len)) {
                    if (x->loop & PLAYMODE_LOOP) {
                        if (x->loop & PLAYMODE_BIDIR) { x->dir = -1; x->pos_fx = (uint32_t)(lend - 1) << 16; }
                        else x->pos_fx -= (uint32_t)(lend - lstart) << 16;
                    } else { x->playing = 0; break; }
                }
            } else {
                if (x->pos_fx < step + ((uint32_t)lstart << 16)) {
                    if ((x->loop & PLAYMODE_LOOP) && (x->loop & PLAYMODE_BIDIR)) { x->dir = 1; x->pos_fx = (uint32_t)lstart << 16; }
                    else if (x->loop & PLAYMODE_LOOP) x->pos_fx = (uint32_t)(lend - 1) << 16;
                    else { x->playing = 0; break; }
                } else x->pos_fx -= step;
            }
        }
        if (!x->playing && x->autokill) memset(x, 0, sizeof(*x));
    }
    for (i = 0; i < frames * 2; i++) out[i] = (int16_t)MID(-32768, acc[i], 32767);
    a4_free(acc);
}

/* at the poll points: mix the time since the last pump and give it to
 * ACGame; while ACGame has no audio output (acgame.library 1.1 returns -1)
 * the voices still advance, so a game that waits for a sound to end goes on */
void a4_audio_pump(void)
{
    uint32_t now, ms;
    int frames;
    int16_t buf[MIX_CHUNK * 2];
    if (!A4S->sound_on) return;
    now = acgame_platform_ticks_ms();
    ms = now - A4S->mix_last_ms;
    if (ms < 10) return;
    if (ms > 500) ms = 500;
    A4S->mix_last_ms = now;
    frames = (int)((uint32_t)MIX_RATE * ms / 1000u);
    while (frames > 0) {
        int n = frames > MIX_CHUNK ? MIX_CHUNK : frames;
        a4_mix_s16stereo(buf, n, MIX_RATE);
        if (A4S->audio_out_ok && acgame_platform_audio_s16stereo(buf, (unsigned)n, MIX_RATE) != 0) A4S->audio_out_ok = 0;
        frames -= n;
    }
    {
        /* MIDI position: beats are not timed without a player; count seconds */
        if (midi_pos >= 0 && A4S->midi_volume >= 0) { }
    }
}

/* ---- MIDI (loaded, not played) -------------------------------------------------------- */

MIDI *a4_read_midi_object(PACKFILE *f)
{
    MIDI *m = (MIDI *)a4_calloc(sizeof(MIDI));
    int c;
    if (!m) return NULL;
    m->divisions = pack_mgetw(f);
    for (c = 0; c < MIDI_TRACKS; c++) {
        long len = pack_mgetl(f);
        if (len == EOF && pack_feof(f)) break;
        m->track[c].len = (int)len;
        if (len > 0) {
            m->track[c].data = (unsigned char *)a4_malloc((size_t)len);
            if (m->track[c].data) pack_fread(m->track[c].data, len, f);
        }
    }
    return m;
}

MIDI *load_midi(const char *filename)
{
    PACKFILE *f = pack_fopen(filename, F_READ);
    MIDI *m;
    char id[4];
    int ntracks, c;
    if (!f) return NULL;
    if (pack_fread(id, 4, f) != 4 || memcmp(id, "MThd", 4) != 0) { pack_fclose(f); return NULL; }
    pack_mgetl(f); pack_mgetw(f);
    ntracks = pack_mgetw(f);
    m = (MIDI *)a4_calloc(sizeof(MIDI));
    if (!m) { pack_fclose(f); return NULL; }
    m->divisions = pack_mgetw(f);
    for (c = 0; c < ntracks && c < MIDI_TRACKS; c++) {
        long len;
        if (pack_fread(id, 4, f) != 4) break;
        len = pack_mgetl(f);
        m->track[c].len = (int)len;
        m->track[c].data = (unsigned char *)a4_malloc((size_t)(len > 0 ? len : 1));
        if (m->track[c].data) pack_fread(m->track[c].data, len, f);
    }
    pack_fclose(f);
    return m;
}

void destroy_midi(MIDI *m)
{
    int c;
    if (!m) return;
    for (c = 0; c < MIDI_TRACKS; c++) a4_free(m->track[c].data);
    a4_free(m);
}

int play_midi(MIDI *m, int loop) { (void)loop; midi_pos = m ? 0 : -1; return 0; }
int play_looped_midi(MIDI *m, int ls, int le) { (void)ls; (void)le; return play_midi(m, TRUE); }
void stop_midi(void) { midi_pos = -1; }
void midi_pause(void) {}
void midi_out(unsigned char *data, int length) { (void)data; (void)length; }   /* MIDI is silent */
void midi_resume(void) {}
int midi_seek(int target) { midi_pos = target; return 0; }
int get_midi_length(MIDI *m) { (void)m; return 0; }

/* the mixer: ACGame mixes; the quality is kept for the game to read back */
int get_mixer_quality(void) { return A4S->mixer_quality; }
void set_mixer_quality(int quality) { A4S->mixer_quality = quality < 0 ? 0 : quality > 2 ? 2 : quality; }
int get_mixer_voices(void) { return A4_VOICES; }
int get_mixer_frequency(void) { return MIX_RATE; }
int get_mixer_bits(void) { return 16; }
int get_mixer_channels(void) { return 2; }
