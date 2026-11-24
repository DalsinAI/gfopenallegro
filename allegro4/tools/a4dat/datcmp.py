#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
"""Two Allegro 4 datafiles, object by object: the same objects (type and NAME, nested files followed) with the
same bytes, and the same properties apart from ORIG and DATE (where and when each was grabbed).

    datcmp.py A.dat B.dat [OBJECT/PATH]     exit 0 when equivalent; one line for each difference
"""
import struct, sys

def lzss(data, want):
    N, F = 4096, 18
    ring = bytearray(N + F); r = N - F; out = bytearray(); i = 0; flags = 0
    while i < len(data) and len(out) < want:
        flags >>= 1
        if not flags & 256:
            flags = data[i] | 0xFF00; i += 1
        if flags & 1:
            if i >= len(data): break
            c = data[i]; i += 1; out.append(c); ring[r] = c; r = (r + 1) & (N - 1)
        else:
            if i + 1 >= len(data): break
            a = data[i] | ((data[i + 1] & 0xF0) << 4); n = (data[i + 1] & 0x0F) + 3; i += 2
            for k in range(n):
                c = ring[(a + k) & (N - 1)]; out.append(c); ring[r] = c; r = (r + 1) & (N - 1)
    return bytes(out)

def objects(b):
    """[(type, {prop: value}, bytes)] of a datafile's object list (count first)"""
    n = struct.unpack(">i", b[:4])[0]; o = 4; out = []
    while len(out) < n:
        props = {}
        t = b[o:o + 4]; o += 4
        while t == b"prop":
            pt = b[o:o + 4].decode("latin1"); ps = struct.unpack(">i", b[o + 4:o + 8])[0]
            props[pt] = b[o + 8:o + 8 + ps].decode("latin1"); o += 8 + ps
            t = b[o:o + 4]; o += 4
        fs, ds = struct.unpack(">ii", b[o:o + 8]); o += 8
        raw = b[o:o + fs]; o += fs
        out.append((t.decode("latin1"), props, lzss(raw, -ds) if ds < 0 else raw))
    return out

def load(name):
    b = open(name, "rb").read()
    if b[:4] == b"slh!": b = lzss(b[4:], 1 << 40)
    elif b[:4] == b"slh.": b = b[4:]
    else: raise SystemExit(f"{name}: not a datafile")
    if b[:4] != b"ALL.": raise SystemExit(f"{name}: no ALL.")
    return objects(b[4:])

def compare(a, b, where, out):
    ka = {(t, p.get("NAME", "")): (p, d) for t, p, d in a}
    kb = {(t, p.get("NAME", "")): (p, d) for t, p, d in b}
    if [k for k in ka] != [k for k in kb]:
        out.append(f"{where or '/'}: objects {list(ka)} | {list(kb)}")
    for k in ka:
        if k not in kb: continue
        (pa, da), (pb, db) = ka[k], kb[k]
        path = f"{where}/{k[1]}" if where else k[1]
        ra = {x: v for x, v in pa.items() if x not in ("ORIG", "DATE")}
        rb = {x: v for x, v in pb.items() if x not in ("ORIG", "DATE")}
        if ra != rb: out.append(f"{path}: properties {ra} | {rb}")
        if k[0] == "FILE": compare(objects(da), objects(db), path, out)
        elif k[0] == "PAL " and len(da) == len(db) == 1024 and \
                all(da[i] == db[i] for i in range(1024) if i % 4 != 3):
            pass    # r, g, b alike; the fourth byte of each is Allegro's filler (4.4's dat leaves it unset)
        elif da != db:
            first = next((i for i in range(min(len(da), len(db))) if da[i] != db[i]), min(len(da), len(db)))
            out.append(f"{path} ({k[0]}): {len(da)} | {len(db)} bytes, first difference at {first}")
    return out

if __name__ == "__main__":
    if len(sys.argv) < 3: raise SystemExit(__doc__)
    diffs = compare(load(sys.argv[1]), load(sys.argv[2]), "", [])
    for d in diffs: print(d)
    n = sum(1 for _ in load(sys.argv[1]))
    print("equivalent, object by object (ORIG and DATE aside)" if not diffs else f"{len(diffs)} differences")
    sys.exit(1 if diffs else 0)
