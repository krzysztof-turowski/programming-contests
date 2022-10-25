#!/usr/bin/python

import functools

MOD = 1000000007
MAX = 10 ** 8
BIN = {}

@functools.lru_cache(maxsize = None)
def invert(n):
    return pow(n, MOD - 2, MOD)

@functools.lru_cache(maxsize = None)
def factorial(n):
    if n <= 1:
        return 1
    return (n * factorial(n - 1)) % MOD

def binomial(n, m):
    if m > n:
        return 0
    return (factorial(n) * invert(factorial(m)) * invert(factorial(n - m))) % MOD

def solve(V, K):
    first, weight = V[0]
    low = sum(v[0] for v in V[1:] if v[1] < weight)
    equal = sum(v[0] for v in V[1:] if v[1] == weight)
    high = sum(v[0] for v in V[1:] if v[1] > weight)
    if first + low + equal < K + 1:
        return 0
    num = binomial(first + low + equal, K + 1) - binomial(low, K + 1)
    den = binomial(first + low + equal + high, K + 1)
    return (first * invert(first + equal) * num * invert(den)) % MOD

def run():
    T = int(input())
    for i in range(MAX):
        factorial(i)
    for t in range(T):
        N, K = (int(x) for x in input().split())
        V = [(tuple(int(x) for x in input().split())) for _ in range(N)]
        print(f'Case #{t + 1}: {solve(V, K)}')

run()
