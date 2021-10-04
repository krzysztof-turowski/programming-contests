#!/usr/bin/python

import math

def floyd_warshall(D):
    C = [[math.inf for _ in range(ord('A'), ord('Z') + 1)]
         for _ in range(ord('A'), ord('Z') + 1)]
    for i, _ in enumerate(C):
        C[i][i] = 0
    for d in D:
        C[ord(d[0]) - ord('A')][ord(d[1]) - ord('A')] = 1
    for k, _ in enumerate(C):
        for i, _ in enumerate(C):
            for j, _ in enumerate(C):
                C[i][j] = min(C[i][k] + C[k][j], C[i][j])
    return C

def solve(S, D):
    C = floyd_warshall(D)
    out = min(sum(C[ord(s) - ord('A')][c - ord('A')] for s in S)
                  for c in range(ord('A'), ord('Z') + 1))
    return out if out != math.inf else -1

def run():
    T = int(input())
    for i in range(T):
        S = input().strip()
        K = int(input())
        D = [input().strip() for _ in range(K)]
        print('Case #{0}: {1}'.format(i + 1, solve(S, D)))

run()
