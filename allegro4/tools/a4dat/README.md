# dat for the build host

`dat` writes Allegro 4 datafiles the way Allegro 4's own `dat` does, and the way
allegro4.library reads them. It runs on the PC that builds a game, so a port's
`data/` Makefiles (Liquid War 5's, for one) can make their `.dat` files without a
host Allegro 4. It is its own code, built on this allegro4 compiled for the host:
the pictures, fonts, samples and MIDI files load through allegro4's own loaders,
and a font is written by `a4_write_font_object` (a4_font.c, built with
`A4_WRITERS`).

    sh tools/a4dat/build-host.sh OUT     # OUT/bin/dat, OUT/lib/liballeg.a, OUT/include
    sh tools/a4dat/test_a4dat.sh         # the tests

`OUT/lib/liballeg.a` and `OUT/include` are allegro4 for the host, with the host
tests' stand-ins for acgame.library, the music and the synth: no screen and no
sound. A game's own data tools build against them too (Liquid War's
`utils/liquidwar*`).

## The command line

    dat [-a] [-k] [-t TYPE] [-bpp N] [-c0|-c1|-c2] [-s0|-s1|-s2] [-v] FILE.dat [FILES...]
    dat -l FILE.dat

| Option | |
| --- | --- |
| `-a` | add each FILE as an object; one with the same NAME is replaced (`-a` can be left out) |
| `-t TYPE` | the object type, as Allegro's: upper case, four characters (`bmp`, `pal`, `font`, `sample`, `midi`, `raw`...). Without it the type comes from the extension: `.pcx` `.bmp` `.tga` `.lbm` a bitmap, `.wav` `.voc` a sample, `.mid` MIDI, `.fnt` a font, `.dat` a nested datafile, anything else `DATA` |
| `-k` | NAME is the file's name as it is (otherwise upper case, `.` as `_`: `back.dat` is `BACK_DAT`) |
| `-bpp N` | new bitmaps at colour depth N (otherwise each picture at its own depth) |
| `-c0` `-c1` `-c2` | unpacked (`slh.`), each object packed, or the whole file packed (`slh!`), in Allegro's LZSS |
| `-s0` `-s1` `-s2` | every property; only NAME; none |
| `-l` | list the objects, nested datafiles too |
| `-v` | say what is added and written |

With no FILES, the datafile is written again as it is, packed and stripped as
`-c` and `-s` say.

What each object holds:

- **bitmap** (`BMP `): depth, width, height, then the pixels. 8-bit as they are;
  15/16-bit 5-6-5 words; 24-bit r, g, b; 32-bit with alpha (depth -32).
  Properties XPOS, YPOS, XSIZ and YSIZ are -1, as for a whole picture.
- **palette** (`PAL `): Allegro's PALETTE, 256 times r, g, b (0 to 63) and a
  filler byte. Allegro 4.4's dat leaves the filler unset; this one writes 0, and
  readers skip it.
- **font** (`FONT`): from a picture of a glyph grid (`-t font`), as allegro4's
  `load_font` reads it. It is written in the new format: 0, the ranges, and
  each range's depth (1 mono, 0 8-bit colour), first and last character, and
  glyphs.
- **sample** (`SAMP`): bits (negative for stereo), frequency, length in
  frames, then the data (8-bit unsigned bytes, 16-bit unsigned little-endian
  words).
- **MIDI** (`MIDI`): divisions, then 32 tracks of length and data.
- **nested datafile** (`FILE`, a `.dat`): its object count and objects, with
  no `ALL.`, as Allegro's grabber nests one. The grabber's own `info` object
  of the inner file is left out.
- **anything else**: the file's bytes.

Each new object gets NAME, ORIG (the file's full path) and DATE (the file's
time, `month-day-year, hour:minute`; with `SOURCE_DATE_EPOCH` set, that time
in UTC). The objects are kept in the grabber's order: by NAME, case ignored,
then the grabber's `info` object (NAME `GrabberInfo`, "For internal use by the
grabber"). The properties of each object are kept in type order.

Not here, because Liquid War's data doesn't need them: `-d` (delete), `-e` and
`-x` (export, extract), `-u` and `-w` (update), `-f`, `-g` (grids of sprites),
`-m`, `-n`, `-o` and `-p` (dependencies, headers), `-007` (passwords),
`-transparency`, RLE and compiled sprites, and fonts in Allegro's `.fnt` and
GRX formats. An option it doesn't have is refused, never ignored.

## Compared with Allegro 4.4's dat

Liquid War 5's `data/`, made with this `dat` and Liquid War's own utils built
on this kit (amigaliquidwar5's `build-amiga.sh`), against the `liquidwar.dat`
that Allegro 4.4.3's dat made for amigaliquidwar5 v5.6.7-open8-rc1-test, with
`datcmp.py` (object by object, nested files followed, ORIG and DATE aside):

- Byte-identical: every font, mouse bitmap, sample, MIDI file and object
  property, and 151 of the 152 maps.
- Palettes are the same in r, g and b; only Allegro 4.4's unset filler bytes
  differ.
- The background picture and the textures (`BACK_DAT`, `TEXTURE_DAT`,
  `MAPTEX_DAT`) differ. Liquid War's `liquidwarcol` picks their palettes from
  random pixels (`srandom(time(NULL))`), so no two builds give the same bytes,
  with Allegro or without.
- One map, `sonnesystem.map`, differs. Its source is a 24-bit BMP, and
  allegro4's reduction of it to 256 colours is not Allegro's.

A whole `.dat` is never byte-identical to another dat's, since ORIG and DATE
say where and when each object was grabbed.
