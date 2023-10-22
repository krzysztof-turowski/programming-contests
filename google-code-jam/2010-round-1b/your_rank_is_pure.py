#!/usr/bin/python3

import functools

MAX, MOD = 501, 100003

@functools.lru_cache(maxsize = 1)
def generate():
    BIN = {(0, 0): 1}
    for a in range(1, MAX + 1):
        BIN[(a, 0)], BIN[(a, a)] = 1, 1
        for b in range(1, a):
            BIN[(a, b)] = (BIN[(a - 1, b)] + BIN[(a - 1, b - 1)]) % MOD
    return BIN

@functools.lru_cache(maxsize = 1)
def get_solutions():
    BIN = generate()
    D = [{1: 1} for _ in range(MAX)]
    for n in range(2, MAX):
        for k in range(2, n):
            D[n][k] = sum(BIN[(n - k - 1, k - i - 1)] * D[k][i]
                          for i in range(1, k) if n - k >= k - i) % MOD
    return D

def solve(N):
    D = get_solutions()
    return sum(D[N].values()) % MOD

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        print('Case #{0}: {1}'.format(i + 1, solve(N)))

run()
