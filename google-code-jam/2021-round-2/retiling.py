#!/usr/bin/python3

import networkx
import networkx.algorithms.bipartite

def distance(a, b, C):
    ax, ay, bx, by = *divmod(a, C), *divmod(b, C)
    return abs(ax - bx) + abs(ay - by)

def solve(start, finish, F, S, C):
    vertices, GM, MG = {}, [], []
    for r, row in enumerate(start):
        for c, _ in enumerate(row):
            position = r * C + c
            if start[r][c] == 'G' and finish[r][c] == 'M':
                GM.append(position)
                vertices[position] = len(vertices)
            if start[r][c] == 'M' and finish[r][c] == 'G':
                MG.append(position)
                vertices[position] = len(vertices)
    if not GM or not MG:
        return F * len(vertices)
    G = networkx.Graph(
        (vertices[i], vertices[j], {'weight': min(distance(i, j, C) * S, 2 * F)})
        for i in GM for j in MG)
    M = networkx.algorithms.bipartite.minimum_weight_full_matching(G)
    return sum(G[u][v]['weight'] for u, v in M.items() if u < v) + F * (len(vertices) - len(M))


def run():
    T = int(input())
    for i in range(T):
        R, C, F, S = (int(x) for x in input().split())
        start = [input().strip() for _ in range(R)]
        finish = [input().strip() for _ in range(R)]
        print(f'Case #{i + 1}: {solve(start, finish, F, S, C)}')

run()
