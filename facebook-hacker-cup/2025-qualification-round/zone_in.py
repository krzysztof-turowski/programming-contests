#!/usr/bin/python3

import collections
import itertools

DIRECTIONS = [(-1, 0), (1, 0), (0, -1), (0, 1)]

def solve(B, R, C, S):
    Q = collections.deque()
    Q.extend((r, -1, S) for r in range(R))
    Q.extend((r, C, S) for r in range(R))
    Q.extend((-1, c, S) for c in range(C))
    Q.extend((R, c, S) for c in range(C))
    Q.extend((r, c, S) for r in range(R) for c in range(C) if B[r][c] == '#')

    while Q:
        r, c, s = Q.popleft()
        if 0 <= r < R and 0 <= c < C:
            if B[r][c] == '*':
                continue
            B[r][c] = '*'
        Q.extend(
            (r + h, c + v, s - 1) for h, v in DIRECTIONS
            if 0 <= r + h < R and 0 <= c + v < C and s > 0)

    out = 0
    for r, c in itertools.product(range(R), range(C)):
        if B[r][c] != '.':
            continue
        Q, count = collections.deque([(r, c)]), 0
        while Q:
            r, c = Q.popleft()
            if B[r][c] != '.':
                continue
            B[r][c], count = 'X', count + 1
            Q.extend(
                (r + h, c + v) for h, v in DIRECTIONS
                if 0 <= r + h < R and 0 <= c + v < C)
        out = max(out, count)
    return out

def run():
    T = int(input())
    for i in range(T):
        R, C, S = (int(x) for x in input().split())
        B = [list(input().strip()) for _ in range(R)]
        print(f'Case #{i + 1}: {solve(B, R, C, S)}')

run()
