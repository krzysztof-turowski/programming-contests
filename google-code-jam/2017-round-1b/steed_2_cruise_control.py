#!/usr/bin/python

import math

def solve(H, D):
    out = math.inf
    for K, S in H:
        out = min(out, D / (D - K) * S)
    return out

def run():
    T = int(input())
    for i in range(T):
        D, N = [int(x) for x in input().split()]
        H = [(int(x) for x in input().split()) for _ in range(N)]
        print('Case #{0}: {1:.7f}'.format(i + 1, solve(H, D)))

run()
