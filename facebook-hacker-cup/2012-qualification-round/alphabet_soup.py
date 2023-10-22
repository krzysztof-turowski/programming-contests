#!/usr/bin/python3

import collections

def solve(S):
    A = collections.defaultdict(int)
    for s in S:
        A[s] += 1
    out = A['C'] // 2
    for c in 'HAKERUP':
        out = min(out, A[c])
    return out

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(i + 1, solve(input())))

run()
