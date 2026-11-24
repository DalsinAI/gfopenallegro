#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
# The host Allegro 4 kit for a game's data tools, from this allegro4 built
# with the build host's C compiler (HOSTCC, else cc):
#   OUT/include/        allegro.h and the rest
#   OUT/lib/liballeg.a  allegro4 for the host, with the host tests' stand-ins
#                       for acgame.library, the music and the synth (no
#                       screen, no sound: pictures, fonts, samples, MIDI,
#                       packfiles and datafiles work)
#   OUT/bin/dat         the datafile writer (tools/a4dat/a4dat.c, README.md)
#   build-host.sh OUT
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
A4=$(CDPATH= cd -- "$HERE/../.." && pwd)
OUT=${1:?usage: build-host.sh OUT}
CC=${HOSTCC:-cc}
mkdir -p "$OUT/obj" "$OUT/lib" "$OUT/bin"
OUT=$(CDPATH= cd -- "$OUT" && pwd)
# the library as the host tests build it (-Werror there, at -O0), here at -O2
LIBFLAGS="-std=c99 -D_DEFAULT_SOURCE -DA4_WRITERS -O2 -I$A4/include -I$A4/src -I$A4/tests"
CFLAGS="-std=c99 -D_DEFAULT_SOURCE -O2 -Wall -Wextra -Werror -I$A4/include"
for s in a4_bitmap a4_blit a4_palette a4_fixed a4_gfx a4_input a4_timer a4_file a4_datafile a4_font a4_image \
         a4_sound a4_system a4_config a4_public a4_gui a4_menu a4_fli a4_dumb a4_os_host; do
    # shellcheck disable=SC2086
    "$CC" $LIBFLAGS -c "$A4/src/$s.c" -o "$OUT/obj/$s.o"
done
for s in fake_acgame fake_music fake_synth; do
    # shellcheck disable=SC2086
    "$CC" $LIBFLAGS -c "$A4/tests/$s.c" -o "$OUT/obj/$s.o"
done
rm -f "$OUT/lib/liballeg.a"
ar rcs "$OUT/lib/liballeg.a" "$OUT"/obj/*.o
mkdir -p "$OUT/include"
cp -R "$A4/include/." "$OUT/include/"
# shellcheck disable=SC2086
"$CC" $CFLAGS "$HERE/a4dat.c" -L"$OUT/lib" -lalleg -lm -o "$OUT/bin/dat"
echo "host Allegro 4: $OUT/lib/liballeg.a, $OUT/include, $OUT/bin/dat"
