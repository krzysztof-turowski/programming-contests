#!/usr/bin/python

MAX = 1000001
MOD = 1000000007

def get_mobius(N):
    out, primes = [1] * N, [True] * N
    for i in range(2, N):
        if primes[i]:
            for j in range(2 * i, N, i):
                primes[j] = False
            for j in range(i, N, i):
                out[j] *= -1
            for j in range(i * i, N, i * i):
                out[j] = 0
    return out

MOBIUS = get_mobius(MAX)

def f(A, D, N):
    return (pow(D - A + 1, N, MOD) + sum(
        MOBIUS[p] * pow(D // p - (A - 1) // p, N, MOD)
        for p in range(2, D + 1))) % MOD if A <= D else 0

def solve(N, A, B, C, D):
    return (f(A, D, N) - f(A, C - 1, N) - f(B + 1, D, N)
            + f(B + 1, C - 1, N)) % MOD

def run():
    T = int(input())
    for i in range(T):
        N, A, B, C, D = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, A, B, C, D)))

run()
