#!/usr/bin/python3

import math

def solve(P):
    low_bound = max(i / p[1] for i, p in enumerate(P, start = 1))
    high_bound = min(i / p[0] if p[0] > 0 else math.inf for i, p in enumerate(P, start = 1))
    return low_bound if low_bound <= high_bound else -1

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        P = [tuple(int(x) for x in input().split()) for _ in range(N)]
        print(f'Case #{i + 1}: {solve(P)}')

run()
