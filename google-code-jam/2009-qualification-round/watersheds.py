#!/usr/bin/python3

import collections
import math

def get_neighbor(A, i, j):
    value, out = math.inf, None
    if i > 0 and A[i - 1][j] < value:
        value, out = A[i - 1][j], (i - 1, j)
    if j > 0 and A[i][j - 1] < value:
        value, out = A[i][j - 1], (i, j - 1)
    if j < len(A[i]) - 1 and A[i][j + 1] < value:
        value, out = A[i][j + 1], (i, j + 1)
    if i < len(A) - 1 and A[i + 1][j] < value:
        value, out = A[i + 1][j], (i + 1, j)
    return out if value < A[i][j] else None

def solve(A, H, W):
    G = collections.defaultdict(set)
    for h in range(H):
        for w in range(W):
            neighbor = get_neighbor(A, h, w)
            if neighbor is None:
                continue
            G[(h, w)].add(neighbor)
            G[neighbor].add((h, w))
    out, symbol = [[None] * W for _ in range(H)], ord('a') - 1
    for h in range(H):
        for w in range(W):
            if out[h][w] is not None:
                continue
            Q, symbol = collections.deque(), symbol + 1
            Q.append((h, w))
            while Q:
                x, y = Q.popleft()
                if out[x][y] is not None:
                    continue
                out[x][y] = chr(symbol)
                Q.extend(G[(x, y)])
    return '\n' + '\n'.join(' '.join(str(r) for r in row) for row in out)

def run():
    T = int(input())
    for i in range(T):
        H, W = (int(x) for x in input().split())
        A = [[int(x) for x in input().split()] for _ in range(H)]
        print('Case #{0}:{1}'.format(i + 1, solve(A, H, W)))

run()
