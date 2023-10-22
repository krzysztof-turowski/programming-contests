#!/usr/bin/python3

import collections

def apply(S, b):
    for i in range(b - 1, len(S), b):
        S[i] = '1' if S[i] == '0' else '0'

def solve(S, B):
    count = collections.defaultdict(int)
    for b in B:
        count[b] += 1
    B = list(sorted(k for k, v in count.items() if v % 2 == 1))
    for b in B:
        apply(S, b)
    out = 0
    for i, s in enumerate(S, start = 1):
        if s == '1':
            apply(S, i)
            out += 1
    return out

def run():
    T = int(input())
    for i in range(T):
        _, S = input(), list(input().strip())
        Q = int(input())
        B = [int(input()) for _ in range(Q)]
        print(f'Case #{i + 1}: {solve(S, B)}')

run()
