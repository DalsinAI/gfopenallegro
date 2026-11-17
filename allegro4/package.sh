#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
# SPDX-License-Identifier: MIT
# The release files from a build-amiga.sh OUT:
#   allegro4-VERSION-part.tar.gz   Parts/Allegro4: the GFOpenUp part
#                                  (GFOpenUpTool INSTALL Parts/Allegro4)
#   allegro4-VERSION-sdk.tar.gz    include/, liballeg.a, README, LICENSE: for building games
#   SHA256SUMS
#   package.sh OUT DEST VERSION
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
OUT=$1 DEST=$2 VERSION=$3
for f in allegro4.library liballeg.a; do
    [ -f "$OUT/$f" ] || { echo "$OUT/$f is missing: run build-amiga.sh first" >&2; exit 1; }
done
mkdir -p "$DEST"
DEST=$(CDPATH= cd -- "$DEST" && pwd)
T=$(mktemp -d)
trap 'rm -rf "$T"' EXIT

P="$T/part/Parts/Allegro4"
mkdir -p "$P/Libs"
cp "$OUT/allegro4.library" "$P/Libs/allegro4.library"
cat > "$P/Part" <<PART
part Allegro4 $VERSION
; allegro4.library: the Allegro 4 API for ACGame games (AGA and RTG)
needs 68040
needs part ACGame
add "Libs/allegro4.library" "LIBS:allegro4.library"
PART
(cd "$T/part" && tar -czf "$DEST/allegro4-$VERSION-part.tar.gz" --owner=0 --group=0 Parts)

S="$T/sdk/allegro4-$VERSION"
mkdir -p "$S/lib"
cp -R "$HERE/include" "$S/include"
cp "$OUT/liballeg.a" "$S/lib/liballeg.a"
cp "$HERE/README.md" "$HERE/LICENSE" "$S/"
(cd "$T/sdk" && tar -czf "$DEST/allegro4-$VERSION-sdk.tar.gz" --owner=0 --group=0 "allegro4-$VERSION")

(cd "$DEST" && sha256sum "allegro4-$VERSION-part.tar.gz" "allegro4-$VERSION-sdk.tar.gz" > SHA256SUMS && cat SHA256SUMS)
