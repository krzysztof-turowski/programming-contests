#!/usr/bin/python

import functools

def solve(N, K):
    f = lambda a, K, N: (a + K) % N
    g = lambda a, K, N, Np: (K * ((a - N % K) % Np)) // (K - 1)
    L = []
    while N > 1:
        if N < K:
            L.append(functools.partial(f, N = N, K = K))
            N -= 1
        else:
            L.append(functools.partial(g, N = N, K = K, Np = N - (N // K)))
            N -= N // K
    out = 0
    for func in L[::-1]:
        out = func(out)
    return out + 1

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, K + 1)))

run()
