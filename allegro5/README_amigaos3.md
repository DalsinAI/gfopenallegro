# Classic AmigaOS 3.x port

`amigaallegro` is the maintained classic AmigaOS 3.x port of Allegro 5. It
starts from upstream Allegro 5.2.11.3 and keeps the public Allegro API intact.
Applications should not need Amiga-specific replacements for calls such as
`al_create_display()`, `al_draw_bitmap()` or `al_flip_display()`.

## Architecture

The first release deliberately does **not** introduce an `allegro.library`:

```text
OpenSurge or another Allegro application
             |
             v
  Allegro 5 static/monolithic libraries
             |
             v
     existing SDL2.module
             |
             v
       existing GL.module
             |
             v
       OpenGPU / OpenRTG
```

Allegro is linked into each program while SDL2.module and GL.module remain the
shared system components. This avoids creating and stabilising an Amiga shared
library ABI, base/interface lifecycle, add-on dependency model and versioning
scheme before the port itself is stable. It also leaves the application's
source code using the normal Allegro 5 API.

An `allegro.library` can be considered later as a packaging and memory-sharing
milestone. It must not be required to port a game, and it must preserve the
same public API and ABI.

OpenSurge should consume a pinned `amigaallegro` commit during its dependency
build. It should not carry replacements for Allegro draw, event, bitmap or
display calls. Game-side changes are limited to genuine application policy,
such as choosing F10 instead of the browser-reserved F11 key and packaging its
data correctly.

## Lessons from the earlier AmigaOS 4 renderer

The incomplete AmigaOS 4 reimplementation is prior art, not a code base for
this port. No source was copied from it. Its useful behaviours have been
translated into requirements for the SDL/OpenGL/OpenGPU stack:

| Earlier technique | Learning retained here | OpenGPU status |
| --- | --- | --- |
| One bitmap is two triangles and six vertices | Qualify exactly Allegro's six-vertex quad and larger held-drawing batches | `ex_amiga_batch` exercises 6 through 6144 vertices |
| Displayable A8R8G8B8 intermediate bitmaps | Keep a single explicit channel order between Allegro, GL and presentation | GL.module uses ARGB; OpenRTG presentation treats screen alpha as XRGB |
| Present through each visible layer rectangle | Never write through covered windows | OpenRTG direct presentation already walks visible pieces |
| Override source alpha and ignore destination alpha for the final display | A display surface is opaque; alpha must not alter fullscreen colour | Direct and fallback presentation must be regression-tested across a fullscreen transition |
| Fixed-point affine scaling in the compositor | Keep scale, rotation, flip, tint and filtering out of application-specific code | OpenGPU `COMPOSITE_AFFINE` and GL already provide these operations |
| Wait for presentation before reusing storage | Preserve fence/layer-lock ordering | OpenGPU fences complete before the target layer is unlocked |

The old implementation's CPU PNG channel shuffle, one compositor submission
per sprite, direct Picasso96 allocation and raw Intuition event handling are
not adopted. They duplicate work already performed more generally by Allegro,
SDL2.module, GL.module and OpenGPU.

## Rendering qualification

`examples/ex_amiga_batch.c` reproduces the held-bitmap path used by OpenSurge:
one texture, tinted quads, a 36-byte all-float internal Allegro vertex, and one
`glBufferData()`/`glDrawArrays()` submission per held batch. It tests these
batch sizes:

| Quads | Vertices | Vertex bytes |
| ---: | ---: | ---: |
| 1 | 6 | 216 |
| 2 | 12 | 432 |
| 16 | 96 | 3,456 |
| 64 | 384 | 13,824 |
| 256 | 1,536 | 55,296 |
| 1,024 | 6,144 | 221,184 |

Controls are Left/Right to change batch size, A to cycle automatically, F10 to
toggle fullscreen and Escape to quit. The window title reports the current
batch. Every square must remain visible and the red, green and blue squares
must retain their channel order before and after fullscreen transitions.

The matching GL.module regression should use the same interleaved layout and
batch sizes. Existing single-quad and generic triangle tests are necessary but
do not reproduce Allegro's larger streaming VBO.

For fault bisection only, configure
`-DALLEGRO_AMIGA_BITMAP_BATCH_LIMIT=<vertices>`. A value of 6 forces one quad
per GL submission; 96 permits sixteen quads. The production default is 0,
which leaves normal Allegro batching unlimited. This control must not become a
game-specific source patch or a permanent six-vertex performance penalty.

## Cross build

The supplied toolchain expects an OpenAmigaGCC/AmigaChrome stove to be passed
explicitly:

```sh
cmake -S . -B build/amigaos3 \
  -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-amigaos3.cmake \
  -DAMIGA_STOVE=/absolute/path/to/os32-gcc16 \
  -DCMAKE_INSTALL_PREFIX=/absolute/path/to/amiga-prefix \
  -DALLEGRO_SDL=ON \
  -DSHARED=OFF \
  -DWANT_MONOLITH=ON \
  -DWANT_ALLOW_SSE=OFF \
  -DWANT_DOCS=OFF \
  -DWANT_TESTS=OFF \
  -DWANT_EXAMPLES=ON \
  -DWANT_DEMO=OFF \
  -DWANT_OPENAL=OFF \
  -DWANT_VIDEO=OFF \
  -DWANT_NATIVE_DIALOG=OFF
cmake --build build/amigaos3 --parallel
cmake --install build/amigaos3
```

SDL2, OpenGL, image, font, audio and PhysicsFS dependencies must already be in
the selected stove or installation prefix. A release consumer should pin an
exact `amigaallegro` commit rather than applying a second copy of the port as a
patch to upstream Allegro.

See [PORT_CANDIDATES.md](PORT_CANDIDATES.md) for the conservative list of
open-source games that can qualify this Allegro 5 port, plus the separate
Allegro 4 candidates and the Allegro 2/3 compatibility recommendation.

## Prior art

- [AmigaOS 4 Allegro reimplementation](https://sourceforge.net/p/allegro5-for-amigaos/allegro5-for-amigaos/)
- [Picasso96/Composite implementation used for review](https://github.com/khval/VectorPlay/tree/master/VectorPlay/amigaos/allegro5)
- [Upstream Allegro 5](https://github.com/liballeg/allegro5)

