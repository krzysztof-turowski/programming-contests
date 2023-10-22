#!/usr/bin/python3

import math

LIMIT = 10 ** 6

def get_primes(N):
    out = [True for _ in range(N + 1)]
    for p in range(2, math.ceil(math.sqrt(N)) + 1):
        if out[p]:
            for q in range(p, N // p + 1):
                out[p * q] = False
    return out

def logarithm(N, b):
    if N < b:
        return 0, 1
    if N < b * b:
        return 1, b
    p, v = logarithm(N, b * b)
    if N < v * b:
        return 2 * p, v
    return 2 * p + 1, v * b

def solve(N, P):
    if N == 1:
        return 0
    return 1 + sum(logarithm(N, i)[0] - 1 for i, p in enumerate(P)
                   if p and 2 <= i * i <= N)

def run():
    P = get_primes(LIMIT)
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(i + 1, solve(int(input()), P)))

run()
