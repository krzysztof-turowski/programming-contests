#!/usr/bin/python

import collections

def path_cost(v, parent, G, C):
    return C[v - 1] + max(
        (path_cost(u, v, G, C) for u in G[v] if u != parent), default = 0)

def solve(G, C):
    paths = sorted(
        list(path_cost(v, 1, G, C) for v in G[1]), reverse = True)
    return C[0] + sum(paths[0:2])

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        G = collections.defaultdict(list)
        C = [int(x) for x in input().split()]
        for _ in range(1, N):
            u, v = (int(x) for x in input().split())
            G[u].append(v)
            G[v].append(u)
        print('Case #{0}: {1}'.format(i + 1, solve(G, C)))

run()
