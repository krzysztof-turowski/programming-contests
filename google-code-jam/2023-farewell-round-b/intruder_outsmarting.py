#!/usr/bin/python3

import functools

@functools.lru_cache(maxsize = None)
def gcd(a, b):
    return b if a == 0 else gcd(b % a, a)

def extended_gcd(a, b):
    if a == 0:
        return (0, 1)
    y, x = extended_gcd(b % a, a)
    return (x - (b // a) * y, y)

@functools.lru_cache(maxsize = None)
def invert(a, b):
    x, _ = extended_gcd(a, b)
    return x % b

def match(d, N, D):
    g = gcd(N, D)
    if d % g != 0:
        return None
    d, N, D = d // g, N // g, D // g
    inv_D = invert(D, N)
    return min((d * inv_D) % N, ((N - d) * inv_D) % N)

def solve(X, N, D):
    out = 0
    for a, b in zip(X[:len(X) // 2], X[::-1]):
        m = match(abs(b - a), N, D)
        if m is not None:
            out += m
        else:
            return 'IMPOSSIBLE'
    return out

def run():
    T = int(input())
    for i in range(T):
        _, N, D = (int(x) for x in input().split())
        X = [int(x) - 1 for x in input().split()]
        print(f'Case #{i + 1}: {solve(X, N, D)}')

run()
