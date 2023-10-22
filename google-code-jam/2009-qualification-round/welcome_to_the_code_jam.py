#!/usr/bin/python3

TEXT, MOD = "welcome to code jam", 10000

def solve(S):
    A = [1] + [0] * len(TEXT)
    for s in S:
        B = [1] + [0] * len(TEXT)
        for i, c in enumerate(TEXT):
            B[i + 1] = A[i + 1] + A[i] if c == s else A[i + 1]
        A = B
    return A[-1] % MOD

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1:04d}'.format(i + 1, solve(input())))

run()
