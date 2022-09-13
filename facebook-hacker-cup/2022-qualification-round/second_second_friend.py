#!/usr/bin/python

import collections

SHIFT = [(-1, 0), (0, -1), (0, 1), (1, 0)]

def solve(R, C, S):
    def get_neighbors(i, j):
        return (S[i + x][j + y] for x, y in SHIFT
                if 0 <= i + x < R and 0 <= j + y < C)

    total = sum(1 for row in S for v in row if v == '^')
    if total == 0:
        return 'Possible\n' + '\n'.join(''.join(s) for s in S)
    if min(R, C) == 1:
        return 'Impossible'

    Q, V = collections.deque(), [[0] * C for _ in range(R)]
    for i in range(R):
        for j in range(C):
            V[i][j] = sum(s != '#' for s in get_neighbors(i, j))
            if V[i][j] <= 1 and S[i][j] != '#':
                Q.append((i, j))
    while len(Q):
        i, j = Q.pop()
        if S[i][j] == '^':
            return 'Impossible'
        if S[i][j] != '.':
            continue
        S[i][j] = '$'
        for x, y in SHIFT:
            if 0 <= i + x < R and 0 <= j + y < C:
                V[i + x][j + y] -= 1
                if V[i + x][j + y] <= 1:
                    Q.append((i + x, j + y))
    S = [''.join(s).replace('.','^').replace('$','.') for s in S]
    return 'Possible\n' + '\n'.join(S)

def run():
    T = int(input())
    for t in range(T):
        R, C = (int(x) for x in input().split())
        S = [list(input().strip()) for _ in range(R)]
        print(f'Case #{t + 1}: {solve(R, C, S)}')

run()
