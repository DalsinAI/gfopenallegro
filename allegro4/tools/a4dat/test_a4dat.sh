#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
# The datafile writer's tests, on the host: build-host.sh's kit, then datafiles of every object type
# (a bitmap, a palette, a colour font from a grid, a sample, a MIDI file, raw and plain data, and a
# nested datafile), unpacked (-c0), each object packed (-c1) and packed whole (-c2), each read back by
# allegro4's own reader and compared object by object with its source (test_a4dat.c); and the writer's
# own round trips: a datafile written again unchanged is the same bytes, and so is -c0 after -c1 or -c2.
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
T=$(mktemp -d "${TMPDIR:-/tmp}/a4dat-test.XXXXXX")
trap 'rm -rf "$T"' EXIT HUP INT TERM
CC=${HOSTCC:-cc}
sh "$HERE/build-host.sh" "$T/host" > /dev/null
DAT=$T/host/bin/dat
"$CC" -std=c99 -D_DEFAULT_SOURCE -Wall -Wextra -Werror -I"$T/host/include" "$HERE/test_a4dat.c" -L"$T/host/lib" -lalleg -lm -o "$T/test_a4dat"
mkdir "$T/src"
"$T/test_a4dat" make "$T/src"
cd "$T/src"
cp pic.pcx pal.pcx
cp raw.bin data.bin
export SOURCE_DATE_EPOCH=1700000000
fill() {    # fill FILE.dat OPTIONS...: the objects, one dat call a type as a game's Makefile makes them
    f=$1; shift
    "$DAT" -a "$@" -t bmp "$f" pic.pcx
    "$DAT" -a "$@" -k -t pal "$f" pal.pcx
    "$DAT" -a "$@" -t font "$f" font.pcx
    "$DAT" -a "$@" -t sample "$f" beep.wav
    "$DAT" -a "$@" -t midi "$f" tune.mid
    "$DAT" -a "$@" -t raw "$f" raw.bin
    "$DAT" -a "$@" "$f" data.bin
}
fill sub.dat
for c in 0 1 2; do
    fill "c$c.dat" "-c$c"
    "$DAT" -a "-c$c" "c$c.dat" sub.dat
    "$T/test_a4dat" check "$T/src" "c$c.dat"
done
# round trips
cp c0.dat again.dat && "$DAT" again.dat && cmp c0.dat again.dat
cp c1.dat back.dat && "$DAT" -c0 back.dat && cmp c0.dat back.dat
cp c2.dat back.dat && "$DAT" -c0 back.dat && cmp c0.dat back.dat
cp c0.dat c1again.dat && "$DAT" -c1 c1again.dat && cmp c1.dat c1again.dat
# the magic and the packing each -c asks for
[ "$(head -c 4 c0.dat)" = "slh." ] && [ "$(head -c 4 c1.dat)" = "slh." ] && [ "$(head -c 4 c2.dat)" = "slh!" ]
[ "$(wc -c < c1.dat)" -lt "$(wc -c < c0.dat)" ] && [ "$(wc -c < c2.dat)" -lt "$(wc -c < c0.dat)" ]
# -s1 keeps the names only, -s2 no properties; the listing
cp c0.dat s1.dat && "$DAT" -s1 s1.dat && ! grep -q ORIG s1.dat && grep -q PIC_PCX s1.dat
cp c0.dat s2.dat && "$DAT" -s2 s2.dat && ! grep -q PIC_PCX s2.dat
"$DAT" -l c0.dat | grep -q "FONT - FONT_PCX"
if "$DAT" -x c0.dat 2> /dev/null; then echo "test_a4dat.sh: -x should be refused"; exit 1; fi
echo "test_a4dat.sh: all passed"
