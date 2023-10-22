#!/usr/bin/python3

import decimal
import functools

MAX = 1000

@functools.lru_cache(maxsize = 1)
def factorial():
    F = [1] + [0] * MAX
    for a in range(1, MAX + 1):
        F[a] = a * F[a - 1]
    return [decimal.Decimal(f) for f in F]

@functools.lru_cache(maxsize = 1)
def derangements():
    DERANG = [1] + [0] * MAX
    for a in range(2, MAX + 1):
        DERANG[a] = (a - 1) * (DERANG[a - 1] + DERANG[a - 2])
    return [decimal.Decimal(d) for d in DERANG]

@functools.lru_cache(maxsize = 1)
def binomial():
    BIN = {(0, 0): 1}
    for a in range(1, MAX + 1):
        BIN[(a, 0)], BIN[(a, a)] = 1, 1
        for b in range(1, a):
            BIN[(a, b)] = BIN[(a - 1, b)] + BIN[(a - 1, b - 1)]
    return {k: decimal.Decimal(v) for k, v in BIN.items()}

@functools.lru_cache(maxsize = 1000)
def solve(N):
    if N <= 1:
        return 0
    F, DERANG, BIN = factorial(), derangements(), binomial()
    return (sum(BIN[(N, i)] * DERANG[i] * solve(i)
                for i in range(N)) + F[N]) / (F[N] - DERANG[N])

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        N = sum(int(x) != i for i, x in enumerate(input().split(), start = 1))
        print('Case #{0}: {1:.6f}'.format(i + 1, solve(N)))

run()
