#!/usr/bin/python

import functools
import math

LIMIT = 10000000

@functools.lru_cache(maxsize = 10 ** 6)
def binomial(a, b):
    if b in (0, a):
        return 1
    return binomial(a - 1, b) + binomial(a - 1, b - 1)

@functools.lru_cache(maxsize = 1)
def generate():
    D = {}
    for cxy in range(1, math.ceil(math.sqrt(3 * LIMIT)) + 1):
        for cy in range(cxy // 2 + 1):
            value = binomial(cxy, cy)
            if value > LIMIT:
                break
            if value not in D:
                D[value] = cxy
    return D

def solve(X, D):
    out = LIMIT
    for i in range(1, math.ceil(math.sqrt(X)) + 1):
        if X % i == 0:
            out = min(out, D.get(i, i) + D.get(X // i, X // i))
    return out

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(
            i + 1, solve(int(input()), generate())))

run()
