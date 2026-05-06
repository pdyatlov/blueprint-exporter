"""Diff two probe_cross_session_drift.py byte captures.

Pure Python (no `unreal` import). Reads two .bin files produced by the probe,
prints summary md5s + sizes, then lists every differing byte run with ±8 bytes
of context in hex. Prints up to 30 runs.

Usage:

    python scripts/diff_cross_session_drift.py <path_to_shellA.bin> <path_to_shellB.bin>
"""

import hashlib
import sys


def _read(path):
    with open(path, "rb") as fp:
        return fp.read()


def main():
    if len(sys.argv) != 3:
        sys.stderr.write("usage: diff_cross_session_drift.py <a.bin> <b.bin>\n")
        sys.exit(2)
    a = _read(sys.argv[1])
    b = _read(sys.argv[2])
    a_md5 = hashlib.md5(a).hexdigest()
    b_md5 = hashlib.md5(b).hexdigest()
    print(f"A: {sys.argv[1]}  bytes={len(a)}  md5={a_md5}")
    print(f"B: {sys.argv[2]}  bytes={len(b)}  md5={b_md5}")
    if a == b:
        print("BYTES IDENTICAL")
        return
    n = min(len(a), len(b))
    diffs = [i for i in range(n) if a[i] != b[i]]
    print(f"DRIFT: {len(diffs)} differing bytes within overlap={n} (size diff={len(a)-len(b)})")
    if not diffs:
        return
    runs = []
    start = diffs[0]
    prev = diffs[0]
    for i in diffs[1:]:
        if i - prev <= 4:
            prev = i
        else:
            runs.append((start, prev))
            start = i
            prev = i
    runs.append((start, prev))
    print(f"coalesced into {len(runs)} runs (gap<=4 bytes)")
    for idx, (s, e) in enumerate(runs[:30]):
        ctx_s = max(0, s - 8)
        ctx_e = min(n, e + 8 + 1)
        a_slice = a[ctx_s:ctx_e].hex()
        b_slice = b[ctx_s:ctx_e].hex()
        ascii_a = ''.join(chr(c) if 32 <= c < 127 else '.' for c in a[ctx_s:ctx_e])
        ascii_b = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b[ctx_s:ctx_e])
        print(f"  run {idx:2d}: bytes [{s}..{e}] len={e-s+1}")
        print(f"    A @[{ctx_s}..{ctx_e}]: {a_slice}  |{ascii_a}|")
        print(f"    B @[{ctx_s}..{ctx_e}]: {b_slice}  |{ascii_b}|")


main()
