#!/usr/bin/python3

import math

def solve(N, P):
    return f'{(10 ** (((N - 1) * math.log10(P) + 2) / N) - P):.10f}'

def run():
    T = int(input())
    for i in range(T):
        N, P = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(N, P)}')

run()
