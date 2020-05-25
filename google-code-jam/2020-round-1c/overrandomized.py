#!/usr/bin/python

from collections import defaultdict

def solve(Q):
    A, B = {}, defaultdict(int)
    for q, r in Q:
        for c in r:
            if c not in A:
                A[c] = 10
        if len(q) == len(r) and q != '-1':
            A[r[0]] = min(A[r[0]], int(q[0]))
        B[r[0]] += 1
    out = ['*'] * 10
    for i, c in enumerate(sorted(A, key = lambda c: (A[c], -B[c]))):
        out[(i + 1) % 10] = c
    return ''.join(out)

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        Q = [input().split() for _ in range(10000)]
        print('Case #{0}: {1}'.format(i + 1, solve(Q)))

run()
