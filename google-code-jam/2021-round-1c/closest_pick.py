#!/usr/bin/python

def solve(K, P):
    out = sorted(
        [P[0] - 1, K - P[-1]] \
            + [(b - a) // 2 for a, b in zip(P[:-1], P[1:]) if a < b] \
            + [(b - a - 1) // 2 for a, b in zip(P[:-1], P[1:]) if a < b],
        reverse = True)
    return sum(out[:2]) / K if len(out) >= 2 else sum(out) / K

def run():
    T = int(input())
    for i in range(T):
        _, K = (int(x) for x in input().split())
        P = list(sorted([int(x) for x in input().split()]))
        print('Case #{0}: {1:.6f}'.format(i + 1, solve(K, P)))

run()
