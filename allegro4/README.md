# allegro4.library

The Allegro 4 API for AmigaOS 3.x (68040), drawing and reading the keyboard,
mouse and pads through acgame.library, so Allegro 4 games run on AGA and RTG.
Written for GFOS; its own code, not Allegro's.

## For a game

Build the game against `include/allegro.h` and link `liballeg.a`. At the first
Allegro call the stubs ask acgame.library for Allegro 4
(`ACG_OpenAllegro(4)`, acgame.library 1.2), or with an older acgame.library
open `allegro4.library` themselves: the game's own `Libs/` drawer first, then
`LIBS:`. Ship `allegro4.library` and `acgame.library` in the game's `Libs/`.

Each game that opens the library gets its own state and its own
acgame.library, so two Allegro games can run at once.

## What is there

Bitmaps, sub-bitmaps, clipping and drawing modes; blits, masked and stretched
blits, sprites (flipped, lit, translucent, rotated, scaled, RLE);
primitives; palettes, fades, colour, light and translucency tables; keyboard
(`key[]`, `readkey`, the callbacks), mouse and joystick; timers on a task of
their own (`install_int_ex`, `rest`, `retrace_count`); packfiles with
Allegro's LZSS, datafiles (`load_datafile`, `load_datafile_object`,
`file.dat#OBJECT`); PCX and BMP; samples, WAV and a 22050 Hz mixer; fonts
from datafiles and an 8x8 built-in font; `al_findfirst` and file names;
the GUI: dialogs (`do_dialog`, `init_dialog`/`update_dialog`/`shutdown_dialog`,
`popup_dialog`) and the standard objects (`d_box_proc`, `d_button_proc`,
`d_check_proc`, `d_radio_proc`, `d_edit_proc`, `d_list_proc`, `d_textbox_proc`,
`d_slider_proc`, `d_keyboard_proc` and the text ones), and menus (`do_menu`,
`init_menu`/`update_menu`/`shutdown_menu`, the `d_menu_proc` menu bar, the
`gui_menu_draw_menu*` hooks), run in the game's own code; FLI and FLC
animations (`open_fli`, `open_memory_fli`, `next_fli_frame`, `play_fli`);
`gfx_mode_select`, `palette_color`, `get_config_text` and the GUI names
Allegro's internal header gives (`gui_shadow_box_proc`, `gui_mouse_focus`,
`_default_font`...).

Limits: 8-bit colour only. MIDI loads but plays silent; samples are mixed,
but stay silent until acgame.library has audio. Games written for Unix paths
work: "./data" and "../save" become "data" and "/save".

## Building

    tests/run_tests.sh     host unit tests (497 checks; SANITIZE="-fsanitize=address,undefined")
    build-amiga.sh         allegro4.library, liballeg.a, tests/A4LibSmoke (STOVE=, OUT=)
    tools/gen_lib.py       the library's calls from include/allegro.h

`library/calls.txt` fixes the order of the library's calls. New calls only go
at its end, so a game built against an older library runs on a later one.

Copyright (c) 2026 AmiCradle Team. MIT licence (see LICENSE).
