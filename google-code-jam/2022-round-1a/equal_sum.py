#!/usr/bin/python3

import sys

MP, M = 30, 78

def read_input():
    return (int(x) for x in input().split())

def print_output(S):
    print(' '.join(str(s) for s in S))
    sys.stdout.flush()

def solve(N):
    S = list(sorted(
        set(2 ** k for k in range(MP)) | set(range(1, M)), reverse = True))[:N]
    print_output(S)
    T = list(read_input())
    L1, L2, difference = [], [], 0
    for v in T + S:
        if difference <= 0:
            L1.append(v)
            difference += v
        else:
            L2.append(v)
            difference -= v
    print_output(L1)

def run():
    T = int(input())
    for _ in range(T):
        N = int(input())
        solve(N)

run()
