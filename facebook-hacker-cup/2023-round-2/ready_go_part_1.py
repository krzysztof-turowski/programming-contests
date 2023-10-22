#!/usr/bin/python3

import collections
import itertools

DIFF = {(-1, 0), (1, 0), (0, -1), (0, 1)}

def bfs(A, i, j, R, C):
    Q = collections.deque()
    Q.append((i, j))
    visited = collections.defaultdict(set)
    while len(Q):
        u, v = Q.popleft()
        if A[u][v] == 'W':
            A[u][v] = 'X'
            for a, b in DIFF:
                if 0 <= u + a < R and 0 <= v + b < C and A[u + a][v + b] != 'X':
                    Q.append((u + a, v + b))
        visited[A[u][v]].add((u, v))
    return visited

def solve(A, R, C):
    for i, j in itertools.product(range(R), range(C)):
        if A[i][j] == 'W':
            visited = bfs(A, i, j, R, C)
            if len(visited['.']) == 1:
                return 'YES'
    return 'NO'

def run():
    T = int(input())
    for i in range(T):
        R, C = (int(x) for x in input().split())
        A = [list(input().strip()) for _ in range(R)]
        print(f'Case #{i + 1}: {solve(A, R, C)}')

run()
