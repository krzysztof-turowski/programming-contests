#!/usr/bin/python

import functools

MOD = 1000000007

@functools.lru_cache(maxsize = 1)
def generate():
    BIN, MAX = {(0, 0): 1}, 10000
    for a in range(1, MAX + 1):
        BIN[(a, 0)], BIN[(a, a)] = 1, 1
        for b in range(1, a):
            BIN[(a, b)] = (BIN[(a - 1, b)] + BIN[(a - 1, b - 1)]) % MOD
    return BIN

def solve(A, N, K):
    BIN = generate()
    return sum(a * BIN[(i - 1, K - 1)]
               for i, a in enumerate(sorted(A)[K - 1:], start = K)) % MOD

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        A = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(A, N, K)))

run()
