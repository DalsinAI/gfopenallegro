#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
# SPDX-License-Identifier: MIT
# allegro4.library and liballeg.a with the os32-gcc16 stove (GCC 16, libnix):
#   allegro4.library   the library: bare (no startup code, no C library), its
#                      RomTag first; 68040, soft float, -Os
#   liballeg.a         what a game links: the public variables, the calls
#                      made game-side (formats, floats, the GUI) and a stub per call
#   tests/A4LibSmoke   opens a screen, draws, blits, reads a key, times 1 s
#   tests/A4MidiPlay   plays a MIDI file as a game does (A4MidiPlay FILE [LOOP])
#   build-amiga.sh     STOVE=dir (default ~/AmiCradle/stoves/os32-gcc16)  OUT=dir
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
STOVE=${STOVE:-"$HOME/AmiCradle/stoves/os32-gcc16"}
P="$STOVE/prefix"
CC=${CC:-"$P/bin/m68k-amigaos-gcc"}
AR=${AR:-"$P/bin/m68k-amigaos-ar"}
NM=${NM:-"$P/bin/m68k-amigaos-nm"}
OUT=${OUT:-"$HERE/build-amiga"}
mkdir -p "$OUT/obj" "$OUT/tests"

python3 "$HERE/tools/gen_lib.py" --check

SOFT="-specs=$HERE/specs/m68k-soft-m68040.specs"
WARN="-Wall -Wextra -Werror -Wno-unused-parameter"
INC="-I$HERE/include -I$HERE/src -I$HERE/library/gfopensynth"
# The library: a4 holds the opener's state (library/allegro4_state.h), so no
# file of it may use a4 for anything else.
LIBCFLAGS="-m68040 $SOFT -Os -fomit-frame-pointer -fno-delete-null-pointer-checks -ffixed-a4 -DA4_LIBRARY $WARN $INC -fno-builtin -fno-tree-loop-distribute-patterns"

CORE="a4_bitmap a4_blit a4_palette a4_fixed a4_gfx a4_input a4_timer a4_file a4_datafile a4_font a4_image a4_sound a4_system a4_config"
OBJS=""
for m in $CORE; do
    # shellcheck disable=SC2086
    "$CC" $LIBCFLAGS -c -o "$OUT/obj/$m.o" "$HERE/src/$m.c"
    OBJS="$OBJS $OUT/obj/$m.o"
done
for m in a4_os_amiga a4_acgame_glue a4_synth_amiga; do
    # shellcheck disable=SC2086
    "$CC" $LIBCFLAGS -c -o "$OUT/obj/$m.o" "$HERE/library/$m.c"
    OBJS="$OBJS $OUT/obj/$m.o"
done
# allegro4_lib.c first: its start() and RomTag lead the hunk.
# shellcheck disable=SC2086
"$CC" $LIBCFLAGS -fno-toplevel-reorder -nostartfiles -nostdlib -o "$OUT/allegro4.library" \
    "$HERE/library/allegro4_lib.c" $OBJS -lgcc
if "$NM" -u "$OUT/allegro4.library" | grep .; then
    echo "allegro4.library has undefined symbols" >&2; exit 1
fi
echo "$OUT/allegro4.library ($(wc -c < "$OUT/allegro4.library") bytes)"
sha256sum "$OUT/allegro4.library"

# liballeg.a, for games (libnix)
GAMECFLAGS="-noixemul -m68040 $SOFT -O2 -fomit-frame-pointer -fno-delete-null-pointer-checks $WARN $INC"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -c -o "$OUT/obj/a4_public.o" "$HERE/src/a4_public.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -c -o "$OUT/obj/a4_gui.o" "$HERE/src/a4_gui.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -c -o "$OUT/obj/a4_menu.o" "$HERE/src/a4_menu.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -c -o "$OUT/obj/a4_fli.o" "$HERE/src/a4_fli.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -c -o "$OUT/obj/a4_dumb.o" "$HERE/src/a4_dumb.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -I"$HERE/library/gfopenmusic" -c -o "$OUT/obj/a4_dumb_gm.o" "$HERE/src/a4_dumb_gm.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -I"$HERE/stubs" -c -o "$OUT/obj/allegro4_open.o" "$HERE/stubs/allegro4_open.c"
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -I"$HERE/stubs" -c -o "$OUT/obj/allegro4_calls.o" "$HERE/stubs/allegro4_calls.c"
rm -f "$OUT/liballeg.a"
"$AR" rcs "$OUT/liballeg.a" "$OUT/obj/a4_public.o" "$OUT/obj/a4_gui.o" "$OUT/obj/a4_menu.o" "$OUT/obj/a4_fli.o" "$OUT/obj/a4_dumb.o" "$OUT/obj/a4_dumb_gm.o" "$OUT/obj/allegro4_open.o" "$OUT/obj/allegro4_calls.o"
echo "$OUT/liballeg.a ($(wc -c < "$OUT/liballeg.a") bytes)"

# the smoke test, linked as a game links
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -o "$OUT/tests/A4LibSmoke" "$HERE/tests/lib_smoke.c" "$OUT/liballeg.a"
echo "$OUT/tests/A4LibSmoke ($(wc -c < "$OUT/tests/A4LibSmoke") bytes)"
# A4MidiPlay: a MIDI file played as a game plays it (the lab's music check)
# shellcheck disable=SC2086
"$CC" $GAMECFLAGS -o "$OUT/tests/A4MidiPlay" "$HERE/tests/midi_play.c" "$OUT/liballeg.a"
echo "$OUT/tests/A4MidiPlay ($(wc -c < "$OUT/tests/A4MidiPlay") bytes)"
