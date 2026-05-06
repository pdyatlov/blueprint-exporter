"""Diff two probe captures and dump wider context around each drift region.

Prints 64 bytes on either side of each run so we can identify the FName /
FString container the drift sits inside.
"""

import sys


def _read(path):
    with open(path, "rb") as fp:
        return fp.read()


def main():
    if len(sys.argv) != 3:
        sys.stderr.write("usage: dump_drift_context.py <a.bin> <b.bin>\n")
        sys.exit(2)
    a = _read(sys.argv[1])
    b = _read(sys.argv[2])
    n = min(len(a), len(b))
    diffs = [i for i in range(n) if a[i] != b[i]]
    if not diffs:
        print("IDENTICAL")
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
    print(f"{len(runs)} runs, {len(diffs)} differing bytes")
    for idx, (s, e) in enumerate(runs[:20]):
        ctx_s = max(0, s - 40)
        ctx_e = min(n, e + 40 + 1)
        a_slice = a[ctx_s:ctx_e]
        b_slice = b[ctx_s:ctx_e]
        ascii_a = ''.join(chr(c) if 32 <= c < 127 else '.' for c in a_slice)
        ascii_b = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b_slice)
        print(f"\n--- run {idx:2d} bytes [{s}..{e}] len={e-s+1} ---")
        print(f"  A [{ctx_s:6d}..{ctx_e:6d}]: {ascii_a}")
        print(f"  B [{ctx_s:6d}..{ctx_e:6d}]: {ascii_b}")


main()
