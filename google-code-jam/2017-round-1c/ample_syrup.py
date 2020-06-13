#!/usr/bin/python

import math

def solve(P, K):
    P, out = sorted(P, key = lambda x: x[0]), 0
    for i, lowest in enumerate(P):
        value = (
            lowest[0] ** 2 + 2 * lowest[0] * lowest[1]
            + sum(2 * x[0] * x[1] for x in sorted(
                P[:i], key = lambda x: x[0] * x[1], reverse = True)[:K - 1]))
        out = max(out, value)
    return out * math.pi

def run():
    T = int(input())
    for i in range(T):
        N, K = [int(x) for x in input().split()]
        P = [tuple(int(x) for x in input().split()) for _ in range(N)]
        print('Case #{0}: {1:.9f}'.format(i + 1, solve(P, K)))

run()
