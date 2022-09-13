#!/usr/bin/python

MOD = 1000000007

def solve(A, X):
    out = len(X) * sum(
        ((X[0][0] - a[0]) ** 2 + (X[0][1] - a[1]) ** 2 for a in A)) % MOD
    HA, VA = sum(a[0] for a in A), sum(a[1] for a in A)
    for i, (u, v) in enumerate(zip(X, X[1:]), start = 1):
        out += (len(X) - i) * (
            len(A) * (v[0] ** 2 - u[0] ** 2 + v[1] ** 2 - u[1] ** 2)
                - 2 * (v[0] - u[0]) * HA - 2 * (v[1] - u[1]) * VA) % MOD
    return out % MOD

def run():
    T = int(input())
    for t in range(T):
        N = int(input())
        A = [tuple(int(x) for x in input().split()) for _ in range(N)]
        Q = int(input())
        X = [tuple(int(x) for x in input().split()) for _ in range(Q)]
        print(f'Case #{t + 1}: {solve(A, X)}')

run()
