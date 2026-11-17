/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * liballeg.a for allegro4.library: what every stub (allegro4_calls.c) needs.
 */
#ifndef ALLEGRO4_STUBS_H
#define ALLEGRO4_STUBS_H

#include <exec/types.h>
#include <exec/libraries.h>
#include <allegro.h>

struct a4_public;

/* allegro4.library for this game: opened at the first call; NULL once the
 * game has closed it as it exits */
struct Library *a4_base(void);

#endif
