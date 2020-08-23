#!/usr/bin/python

import collections
import math

Horse = collections.namedtuple('Horse', ['distance', 'speed'])
Query = collections.namedtuple('Query', ['A', 'B'])

def floyd_warshall(G, N):
    for k in range(N):
        for i in range(N):
            for j in range(N):
                G[i][j] = min(G[i][j], G[i][k] + G[k][j])
    return G

def solve(D, H, N, Q):
    D = floyd_warshall(D, N)
    G = [[0] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            G[i][j] = (D[i][j] / H[i].speed if H[i].distance >= D[i][j]
                       else math.inf)
    G = floyd_warshall(G, N)
    return ' '.join(str(G[a - 1][b - 1]) for a, b in Q)

def run():
    T = int(input())
    for i in range(T):
        N, Q = (int(x) for x in input().split())
        H = [Horse(*(float(x) for x in input().split())) for _ in range(N)]
        D = [[float(x) if x != '-1' else math.inf for x in input().split()]
             for _ in range(N)]
        Q = [Query(*(int(x) for x in input().split())) for _ in range(Q)]
        print('Case #{0}: {1}'.format(i + 1, solve(D, H, N, Q)))

run()
