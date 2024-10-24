#!/usr/bin/python3

import random

TRIES = 100

def solve(P):
    colinear = 2
    for _ in range(TRIES):
        u, v = list(random.sample(P, k = 2))
        if u[0] == v[0]:
            colinear = max(colinear, sum(1 for p in P if p[0] == v[0]))
        else:
            a = (v[1] - u[1]) / (v[0] - u[0])
            b = v[1] - a * v[0]
            colinear = max(colinear, sum(1 for p in P if abs(p[1] - a * p[0] - b) < 1e-6))
    return len(P) - colinear

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        P = [tuple(int(x) for x in input().split()) for _ in range(N)]
        print(f'Case #{i + 1}: {solve(P)}')

run()
