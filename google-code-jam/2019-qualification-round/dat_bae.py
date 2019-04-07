#!/usr/bin/python

import sys

def get_input(N, t):
    base = ['0'] * t + ['1'] * t
    while len(base) < N:
        base = base + base
    return ''.join(base[:N])

def solve(N, B):
    L = []
    for t in [1, 2, 4, 8, 16]:
        print(get_input(N, t))
        sys.stdout.flush()
        L.append(input().strip())
    out = []
    counter, before, after = 0, -1, -1
    for i in range(N - B):
        before, after = after, sum(int(L[j][i]) * (2 ** j) for j in range(len(L)))
        if after + counter * (2 ** len(L)) < before:
            counter += 1
        after += counter * (2 ** len(L))
        out += [v for v in range(before + 1, after)]
    out += [v for v in range(after + 1, N)]
    return ' '.join(str(v) for v in out)

def run():
    T = int(input())
    for _ in range(T):
        N, B, _ = [int(x) for x in input().split()]
        print('{0}'.format(solve(N, B)))
        sys.stdout.flush()
        _ = input()

run()
