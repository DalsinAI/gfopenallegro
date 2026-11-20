# GFOpenAllegro

Allegro 4 and Allegro 5 for GFOS, in one place.

- **allegro4/**: allegro4.library, built on acgame.library. Its GFOpenUp part is built on every merge (`.github/workflows/part.yml`).
- **allegro5/**: Allegro 5.2.11.3 with the classic AmigaOS 3.x port (see `allegro5/README_amigaos3.md`). Today it links into each program and draws through SDL2.module, GL.module and OpenGPU. Moving it onto acgame.library, alongside allegro4, is the next step. Where it came from is in `allegro5/IMPORT.md`.

acgame.library can use either when told.

Allegro 5 is under the zlib licence (`allegro5/LICENSE.txt`). The rest is Copyright (c) 2026 AmiCradle Team.
