#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
# The host unit tests of allegro4.library's core, on a fake acgame.library.
set -eu
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
OUT="${TMPDIR:-/tmp}/allegro4-test-$$"
trap 'rm -f "$OUT"' EXIT HUP INT TERM
CC=${CC:-cc}
"$CC" -std=c99 -D_DEFAULT_SOURCE -Wall -Wextra -Werror -g ${SANITIZE:-} \
  -I"$ROOT/include" -I"$ROOT/src" -I"$ROOT/tests" \
  "$ROOT"/src/a4_bitmap.c "$ROOT"/src/a4_blit.c "$ROOT"/src/a4_palette.c "$ROOT"/src/a4_fixed.c \
  "$ROOT"/src/a4_gfx.c "$ROOT"/src/a4_input.c "$ROOT"/src/a4_timer.c "$ROOT"/src/a4_file.c \
  "$ROOT"/src/a4_datafile.c "$ROOT"/src/a4_font.c "$ROOT"/src/a4_image.c "$ROOT"/src/a4_sound.c \
  "$ROOT"/src/a4_system.c "$ROOT"/src/a4_config.c "$ROOT"/src/a4_public.c "$ROOT"/src/a4_gui.c "$ROOT"/src/a4_menu.c "$ROOT"/src/a4_fli.c "$ROOT"/src/a4_os_host.c \
  "$ROOT"/tests/fake_acgame.c "$ROOT"/tests/test_allegro4.c \
  -o "$OUT"
"$OUT"
