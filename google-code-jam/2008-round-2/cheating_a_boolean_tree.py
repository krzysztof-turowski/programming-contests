#!/usr/bin/python3

import math

def solve(M, V, N):
    out = [None] * M
    for i in range(M - 1, (M - 1) // 2 - 1, -1):
        out[i] = {N[i][0]: 0, 1 - N[i][0]: math.inf}
    for i in range((M - 1) // 2 - 1, -1, -1):
        left, right, G, C = 2 * i + 1, 2 * i + 2, *N[i]
        out[i] = {
            G: out[left][G] + out[right][G],
            1 - G: min(
                out[left][x] + out[right][y]
                for x in range(2) for y in range(2) if x != G or y != G)}
        if C:
            out[i][G] = min(
                out[i][G],
                min(
                    out[left][x] + out[right][y] + 1
                    for x in range(2) for y in range(2)
                    if x != 1 - G or y != 1 - G))
            out[i][1 - G] = min(
                out[i][1 - G],
                out[left][1 - G] + out[right][1 - G] + 1)
    return out[0][V] if out[0][V] != math.inf else 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        M, V = (int(x) for x in input().split())
        N = [[int(x) for x in input().split()] for _ in range(M)]
        print('Case #{0}: {1}'.format(i + 1, solve(M, V, N)))

run()
