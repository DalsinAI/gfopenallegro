/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * A4MidiPlay: plays a MIDI file the way an Allegro 4 game does (load_midi,
 * play_midi), linked as a game links (liballeg.a), with no screen. It says
 * which way the music sounds, then the beat once a second until the song
 * ends or Ctrl-C.
 *   A4MidiPlay FILE [LOOP]
 */
#include <allegro.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

static volatile int stop;
static void on_break(int sig) { (void)sig; stop = 1; }

int main(int argc, char **argv)
{
    MIDI *m;
    int len, shown = -1;
    if (argc < 2) { printf("A4MidiPlay FILE [LOOP]\n"); return 10; }
    signal(SIGINT, on_break);
    if (allegro_init() != 0) { printf("allegro_init failed\n"); return 20; }
    install_timer();
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) { printf("install_sound: %s\n", allegro_error); return 20; }
    if (midi_driver->id == MIDI_NONE) {
        printf("A4MidiPlay: no synth (gfopensynth.library, and a MIDI port or DEVS:SoundFonts/default.sf2): FAIL\n");
        allegro_exit();
        return 5;
    }
    printf("MIDI driver: %s\n", midi_driver->desc);
    if (!(m = load_midi(argv[1]))) { printf("%s is not a MIDI file\n", argv[1]); allegro_exit(); return 10; }
    len = get_midi_length(m);
    printf("%s: %d s\n", argv[1], len);
    if (play_midi(m, argc > 2 && !strcmp(argv[2], "LOOP")) != 0) { printf("play_midi failed\n"); allegro_exit(); return 5; }
    while (midi_pos >= 0 && !stop) {
        rest(50);
        if ((int)midi_time != shown) { shown = (int)midi_time; printf("beat %ld, %d s\n", midi_pos, shown); fflush(stdout); }
    }
    stop_midi();
    rest(300);                              /* the last notes' release */
    destroy_midi(m);
    allegro_exit();
    printf("A4MidiPlay: %s\n", stop ? "stopped" : "PASS");
    return 0;
}
