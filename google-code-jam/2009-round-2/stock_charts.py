#!/usr/bin/python3

import itertools
import networkx

def solve(P, N):
    E = [(i, j + N, {'capacity': 1}) for i, j in itertools.permutations(range(N), 2)
         if all(x < y for x, y in zip(P[i], P[j]))]
    S = [(2 * N, i, {'capacity': 1}) for i in range(N)]
    T = [(i + N, 2 * N + 1, {'capacity': 1}) for i in range(N)]
    G = networkx.DiGraph(E + S + T)
    return N - networkx.maximum_flow(G, 2 * N, 2 * N + 1)[0]


def run():
    T = int(input())
    for i in range(T):
        N, _ = (int(x) for x in input().split())
        P = [[int(x) for x in input().split()] for _ in range(N)]
        print(f'Case #{i + 1}: {solve(P, N)}')

run()
