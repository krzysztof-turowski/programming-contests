#!/usr/bin/python

import itertools

THRESHOLD = 10000
BASE = 11
BASES = list(range(2, BASE))
MEMORY = [[set(), set()] for _ in range(BASE)]

def happy(H, N, B, add = False):
    if N in H[0]:
        return True
    if N in H[1]:
        return False
    S = {N}
    while True:
        N_next = 0
        while N > 0:
            N_next, N = N_next + (N % B) ** 2, N // B
        N = N_next
        if N in H[0] or N == 1:
            if add:
                H[0] |= S
            return True
        if N in H[1] or N in S:
            if add:
                H[1] |= S
            return False
        if add:
            S.add(N)

def get_start(D, v):
    out = 2
    for i, _ in enumerate(BASES):
        if (1 << i) > v:
            break
        if (1 << i) & v > 0:
            out = max(out, D[(1 << i) ^ v])
    return out

def precompute():
    out = {}
    for v in range(2, THRESHOLD):
        for b in BASES:
            happy(MEMORY[b], v, b, True)
    for v in range(1, 2 ** len(BASES)):
        bases = [b for i, b in enumerate(BASES) if (1 << i) & v > 0]
        if len(bases) == 1:
            continue
        start = 2 if len(bases) == 2 else get_start(out, v)
        for i in itertools.count(start):
            if all(happy(MEMORY[b], i, b) for b in bases):
                out[v] = i
                break
    return out

def convert(bases):
    return sum(1 << (b - 2) for b in bases)

def run():
    D = precompute()
    T = int(input())
    for i in range(T):
        B = convert(int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, D[B]))

run()
