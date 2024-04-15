#!/usr/bin/python3

import functools
import math

@functools.cache
def get_divisors(N):
    if N == 0:
        return []
    if N == 1:
        return [-math.inf]
    out = []
    for i in range(2, math.ceil(math.sqrt(N)) + 1):
        if N % i == 0:
            if i <= N // i:
                out.append(i)
            if i < N // i:
                out.append(N // i)
    if N >= 2:
        out.append(N)
    return out

@functools.cache
def g(N):
    return max((g(N // p - 1) + 1 for p in get_divisors(N) if p > 1), default = 1) if N > 1 else 0

def solve(N):
    return max((g(N // p - 1) + 1 for p in get_divisors(N) if p > 2), default = 1)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        print(f'Case #{i + 1}: {solve(N)}')

run()
