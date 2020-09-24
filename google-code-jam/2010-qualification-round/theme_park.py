#!/usr/bin/python

import bisect
import itertools

def solve(G, R, K):
    V = list(itertools.accumulate([0] + G + G))
    indices = [min(i + len(G), bisect.bisect(V[1:], v + K)) % len(G)
               for i, v in enumerate(V[:len(G)])]
    sums = [V[j] - V[i] if i < j else V[j] + V[len(G)] - V[i]
            for i, j in enumerate(indices)]
    index, out = 0, 0
    for _ in range(R):
        index, out = indices[index], out + sums[index]
    return out

def run():
    T = int(input())
    for i in range(T):
        R, K, _ = (int(x) for x in input().split())
        G = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(G, R, K)))

run()
