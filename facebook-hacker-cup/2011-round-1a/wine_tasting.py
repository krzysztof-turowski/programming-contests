#!/usr/bin/python

import functools

MOD = 1051962371

@functools.lru_cache(maxsize = 10 ** 4)
def binomial(a, b):
    if b in (0, a):
        return 1
    return binomial(a - 1, b) + binomial(a - 1, b - 1)

@functools.lru_cache(maxsize = 10 ** 2)
def derangements(a):
    if a <= 1:
        return 1 - a
    return (a - 1) * (derangements(a - 1) + derangements(a - 2))

def solve(G, C):
    return sum(binomial(G, i) * derangements(G - i)
               for i in range(C, G + 1)) % MOD

def run():
    T = int(input())
    for i in range(T):
        G, C = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(G, C)))

run()
