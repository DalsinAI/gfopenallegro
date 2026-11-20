# Open-source game port candidates

This is a deliberately conservative shortlist, not a complete catalogue.
Every entry below has source code and an identifiable open-source licence.
The code licence does not necessarily cover the original game data, music,
trademarks or fan-game assets, so those are called out separately.

## Allegro 5

These games can exercise `amigaallegro` directly and are the most useful
targets for the current port.

| Game | Licence | Port value | Important qualification |
| --- | --- | --- | --- |
| [OpenSurge](https://github.com/alemart/opensurge) | GPL-3.0 | Current qualification game; broad use of Allegro 5 drawing, input, audio and add-ons | Keep its Allegro calls unchanged and pin an `amigaallegro` revision |
| [Liberation Circuit](https://github.com/linleyh/liberation-circuit) | GPL-3.0 | Best small independent second target; C and Allegro 5 | Native-dialog use may need disabling or a small backend stub |
| [Dune Dynasty](https://github.com/gameflorist/dunedynasty) | GPL-2.0 | Larger real-game workload | Requires data files from an original Dune II installation |
| [Icy Tower open remake](https://github.com/royeldar/icytower) | MIT | Compact Allegro 5 game | Extracted original graphics and sound require a separate redistribution review |
| [SuperDerpy](https://github.com/dos1/SuperDerpy) | GPL-2.0 | Useful 2D game framework and add-on coverage | Fan-game art, names and trademarks need a separate content review |
| [Crystal Picnic](https://github.com/Cloudxtreme/crystal-picnic) | zlib | Heavy integration test | Adds Lua, BASS/BASSMIDI, poly2tri and TGUI2; not an early port target |

`Paintown` is not classified here as an Allegro 5 target: its current tree
uses SDL2. `Dr. Destructo 2` has Allegro 5 source in public, but the examined
tree has no explicit source licence, so source availability alone is not
enough to call it open source.

## Allegro 4

Allegro 4 is a separate API and repository. These games would benefit from a
future Allegro 4 compatibility/port project, not directly from the Allegro 5
library in this repository.

| Game | Licence | Port value | Important qualification |
| --- | --- | --- | --- |
| [Liquid War 5](https://github.com/ufoot/liquidwar5) | GPL | Well-known native Allegro 4 game | Treat as an Allegro 4 port target |
| [UFO2000](https://github.com/ufo2000/ufo2000) | GPL-2.0 | Substantial network tactics game | Full play uses original X-COM data; demo data is available |
| [KQ Lives](https://github.com/taschemann/kq-lives) | GPL-2.0 | CRPG using Allegro 4, Lua and DUMB | Extra Lua and DUMB dependencies |

## Allegro 2 and 3

Surviving game trees from the Allegro 2/3 era rarely record an exact library
generation, and many maintained copies were migrated to Allegro 4. Do not
create separate Amiga Allegro 2 and 3 projects from an unverified game list.
After Allegro 5 is stable, investigate a single Allegro 4 compatibility path;
that is likely to cover more of this older source with less duplicated work.

## Recommended order

1. Finish OpenSurge qualification on Allegro 5.
2. Port Liberation Circuit as the independent Allegro 5 proof.
3. Try Dune Dynasty to expose larger-game and data-path issues.
4. Decide whether demand justifies a separate Allegro 4 repository.

