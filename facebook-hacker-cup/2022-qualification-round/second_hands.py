#!/usr/bin/python

import collections

def solve(N, K, S):
    if N > 2 * K:
        return 'NO'
    D = collections.defaultdict(int)
    for s in S:
        D[s] += 1
    return 'YES' if max(D.values()) <= 2 else 'NO'

def run():
    T = int(input())
    for t in range(T):
        N, K = (int(x) for x in input().split())
        S = [int(x) for x in input().split()]
        print(f'Case #{t + 1}: {solve(N, K, S)}')

run()
