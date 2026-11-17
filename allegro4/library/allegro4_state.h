/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro4.library: an opener's state is in a4 while the library runs, the
 * way acgame.library does it. Every file of the library is built with
 * -ffixed-a4; each entry point keeps the caller's a4, puts the opener's
 * struct a4_state there, and gives the caller's back.
 */
#ifndef ALLEGRO4_LIBRARY_STATE_H
#define ALLEGRO4_LIBRARY_STATE_H

struct a4_state;
register struct a4_state *a4_state_ptr __asm__("a4");

#endif
