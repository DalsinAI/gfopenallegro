#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
# SPDX-License-Identifier: MIT
"""allegro4.library's calls, made from include/allegro.h.

Every function allegro.h declares is a library call, in the order of
library/calls.txt (a new call only ever goes at the end of that list, so a
game built against an older library runs on a later one), except the ones
the stubs do themselves (STUB_SIDE: the calls with a format string, the
floating point ones, and the ones whose result the game frees with free()).

Writes:
  library/allegro4_lib.sfd      the calls, their offsets and registers
  library/allegro4_entries.h    the library's entry points (included by allegro4_lib.c)
  stubs/allegro4_calls.c        the game's side: each call through the library base

  tools/gen_lib.py              (re)write them; --check: fail if they are not up to date
"""
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
HEADER = os.path.join(ROOT, "include", "allegro.h")
CALLS = os.path.join(ROOT, "library", "calls.txt")

STUB_SIDE = {
    "install_allegro", "allegro_message", "usprintf", "uszprintf", "uvszprintf",
    "textprintf_ex", "textprintf_centre_ex", "textprintf_right_ex", "textprintf_justify_ex",
    "textprintf", "textprintf_centre", "textprintf_right", "textprintf_justify",
    "hsv_to_rgb", "rgb_to_hsv", "_a4_strdup", "file_size_ex",
}
# the library's own calls that are not in allegro.h
EXTRA = [
    ("int", "a4_install", [("struct a4_public *", "pub"), ("int", "system_id")]),
]

AREGS = ["a0", "a1", "a2", "a3"]
DREGS = ["d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"]
SCRATCH = ["d0", "d1", "a0", "a1"]


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_arg(a):
    """(type with the name left out, name, is_pointer)"""
    m = re.match(r"^(.*)\(\s*\*\s*(\w+)\s*\)\s*(\(.*\))\s*$", a)
    if m:                                   # a function pointer
        return ("%s(*)%s" % (m.group(1).strip(), m.group(3)), m.group(2), True)
    m = re.match(r"^(.*?)(\w+)\s*(\[[^\]]*\])+\s*$", a)
    if m:                                   # an array: a pointer
        return (m.group(1).strip() + " *", m.group(2), True)
    m = re.match(r"^(.*?)(\w+)\s*$", a)
    typ, name = m.group(1).strip(), m.group(2)
    if typ in ("PALETTE", "const PALETTE"):
        return (typ.replace("PALETTE", "RGB *"), name, True)
    return (typ, name, "*" in typ)


def decl(typ, name):
    if "(*)" in typ:
        return typ.replace("(*)", "(*%s)" % name, 1)
    return "%s %s" % (typ, name)


def read_protos():
    src = open(HEADER).read()
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    src = re.sub(r"^\s*#.*$", "", src, flags=re.M)
    src = re.sub(r"static inline[^{]*\{[^}]*\}", "", src)
    protos = {}
    for m in re.finditer(r"(?:^|;|\})\s*([A-Za-z_][\w \*]*?[\s\*])(\w+)\s*\(([^;{]*)\)\s*;", src, flags=re.S):
        ret, name, args = m.group(1).strip(), m.group(2), " ".join(m.group(3).split())
        if ret.startswith(("typedef", "extern", "return")) or "..." in args or "va_list" in args:
            continue
        if ret.startswith("struct ") and "{" in ret:
            continue
        al = [] if args in ("void", "") else [parse_arg(x) for x in split_args(args)]
        raw = [] if args in ("void", "") else split_args(args)
        protos[name] = (ret, al, raw)
    return protos


def assign(args):
    a, d, regs = list(AREGS), list(DREGS), []
    for typ, name, ptr in args:
        pool, other = (a, d) if ptr else (d, a)
        r = pool.pop(0) if pool else other.pop(0)
        regs.append(r)
    return regs


def main():
    check = "--check" in sys.argv
    protos = read_protos()
    for ret, name, args in EXTRA:
        protos[name] = (ret, [(t, n, "*" in t) for t, n in args], [decl(t, n) for t, n in args])
    wanted = sorted(n for n in protos if n not in STUB_SIDE)
    order = []
    if os.path.exists(CALLS):
        order = [l.strip() for l in open(CALLS) if l.strip() and not l.startswith("#")]
    missing = [n for n in order if n not in protos]
    if missing:
        sys.exit("calls.txt names calls allegro.h no longer has: %s" % ", ".join(missing))
    new = [n for n in wanted if n not in order]
    order += new
    calls_txt = "# allegro4.library's calls in library order (offset -30 - 6*n). Only add at the end.\n" + "\n".join(order) + "\n"

    sfd = ["==id $Id: allegro4_lib.sfd 1.0 (16.11.2026) $",
           '* "allegro4.library" (Allegro 4 on acgame.library), AmiCradle Team',
           "==base _Allegro4Base", "==basetype struct Library *", "==libname allegro4.library",
           "==bias 30", "==public", "==include <exec/types.h>", "==include <allegro.h>"]
    entries = ["/* Made by tools/gen_lib.py from include/allegro.h: do not edit. */"]
    vectors = []
    stubs = ["/* Made by tools/gen_lib.py from include/allegro.h: do not edit.",
             " * Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE). */",
             '#include "allegro4_stubs.h"', ""]
    for i, name in enumerate(order):
        ret, args, raw = protos[name]
        regs = assign(args)
        if len(args) > 12:
            sys.exit("%s: too many arguments for registers" % name)
        off = 30 + 6 * i
        sfd.append("%s %s(%s)(%s)" % (ret, name, ", ".join(decl(t, n) for t, n, p in args) or "",
                                       ",".join(regs)))
        isvoid = ret == "void"
        # the library side
        params = ["REG(%s, %s)" % (r, decl(t, n)) for (t, n, p), r in zip(args, regs)]
        params.append("REG(a6, struct A4Base *_lb)")
        call = "%s(%s)" % (name, ", ".join(n for t, n, p in args))
        body = ("    ENTER(_lb);\n    %s;\n    LEAVE();\n" % call) if isvoid else \
               ("    %s _r;\n    ENTER(_lb);\n    _r = %s;\n    LEAVE();\n    return _r;\n" % (ret, call))
        entries.append("static %s L_%s(%s)\n{\n%s}" % (ret, name, ", ".join(params), body))
        vectors.append("(APTR)L_%s" % name)
        # the game side
        sargs = ", ".join(raw) or "void"   # as allegro.h has it
        lines = ["%s %s(%s)" % (ret, name, sargs), "{",
                 "    struct Library *const _b = a4_base();",
                 "    if (!_b) return%s;" % ("" if ret == "void" else " (%s)0" % ret)]
        used = dict(zip(regs, args))
        for r in SCRATCH:
            if r in used:
                t, n, p = used[r]
                lines.append("    register %s __asm(\"%s\") = %s;" % (decl(t, "_" + r), r, n))
            else:
                lines.append("    register long _%s __asm(\"%s\") = 0;" % (r, r))
        ins = []
        for r, (t, n, p) in used.items():
            if r not in SCRATCH:
                lines.append("    register %s __asm(\"%s\") = %s;" % (decl(t, "_" + r), r, n))
                ins.append('"r"(_%s)' % r)
        lines.append("    register struct Library *_a6 __asm(\"a6\") = _b;")
        ins.append('"r"(_a6)')
        lines.append('    __asm volatile ("jsr -%d(%%%%a6)" : "+r"(_d0), "+r"(_d1), "+r"(_a0), "+r"(_a1) : %s : "cc", "memory");'
                     % (off, ", ".join(ins)))
        if not isvoid:
            lines.append("    return (%s)_d0;" % ret)
        lines.append("}")
        stubs.extend(lines)
        stubs.append("")
    sfd.append("==end")
    entries.append("static const APTR a4_vectors[] = {\n    (APTR)lib_open, (APTR)lib_close, (APTR)lib_expunge, (APTR)lib_null,\n    "
                   + ",\n    ".join(vectors) + ",\n    (APTR)-1,\n};")
    outs = {
        CALLS: calls_txt,
        os.path.join(ROOT, "library", "allegro4_lib.sfd"): "\n".join(sfd) + "\n",
        os.path.join(ROOT, "library", "allegro4_entries.h"): "\n\n".join(entries) + "\n",
        os.path.join(ROOT, "stubs", "allegro4_calls.c"): "\n".join(stubs),
    }
    stale = []
    for path, text in outs.items():
        old = open(path).read() if os.path.exists(path) else None
        if old != text:
            stale.append(os.path.relpath(path, ROOT))
            if not check:
                open(path, "w").write(text)
    if check and stale:
        sys.exit("out of date (run tools/gen_lib.py): " + ", ".join(stale))
    print("%d calls%s" % (len(order), (", wrote " + ", ".join(stale)) if stale and not check else ""))


if __name__ == "__main__":
    main()
