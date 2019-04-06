#!/usr/bin/python

def solve(D, K):
    while True:
        N = max(D)
        V = D[N]
        del D[N]
        if K <= V:
            return (N / 2, N / 2 - 1) if N % 2 == 0 else ((N - 1) / 2, (N - 1) / 2)
        K -= V
        if N % 2 == 0:
            D[N / 2 - 1] = D.get(N / 2 - 1, 0) + V
            D[N / 2] = D.get(N / 2, 0) + V
        else:
            D[(N - 1) / 2] = D.get((N - 1) / 2, 0) + 2 * V

def run():
    T = int(input())
    for t in range(T):
        N, K = [int(x) for x in input().split()]
        L, R = solve({N: 1}, K)
        print("Case #{0}: {1:.0f} {2:.0f}".format(t + 1, L, R))

run()
