#!/usr/bin/python

import collections
import itertools
import queue

def bfs(G, start, end):
    Q, D = queue.Queue(), {}
    Q.put((0, start))
    while not Q.empty():
        d, v = Q.get()
        if v in D:
            continue
        D[v] = d
        if v == end:
            break
        for u in G[v]:
            Q.put((d + 1, u))
    return D

def shortest_paths(G):
    forward, backward = bfs(G, 0, 1), bfs(G, 1, 0)
    distance = max(forward.values())
    D = [[] for _ in range(distance)]
    for v, _ in enumerate(G):
        if v not in forward or v not in backward:
            continue
        if forward[v] + backward[v] == distance and backward[v] > 0:
            D[forward[v]].append(v)
    return D

def solve(G):
    if 1 in G[0]:
        return '{0} {1}'.format(0, len(G[0]))
    D, N = shortest_paths(G), collections.defaultdict(int)
    for v in D[1]:
        N[(0, v)] = len(G[0] | G[v])
    for V1, V2, V3 in zip(D, D[1:], D[2:]):
        for v1, v2, v3 in itertools.product(V1, V2, V3):
            if v2 not in G[v1] or v3 not in G[v2]:
                continue
            N[(v2, v3)] = max(
                N[(v2, v3)], N[(v1, v2)] + len(G[v3] - G[v2] - G[v1]))
    D2 = max(N[(u, v)] for u in D[-2] for v in D[-1] if (u, v) in N)
    return '{0} {1}'.format(len(D) - 1, D2 - len(D))

def run():
    T = int(input())
    for i in range(T):
        P, _ = (int(x) for x in input().split())
        G = [set() for _ in range(P)]
        for line in input().split():
            x, y = (int(p) for p in line.split(','))
            G[x].add(y)
            G[y].add(x)
        print('Case #{0}: {1}'.format(i + 1, solve(G)))

run()
