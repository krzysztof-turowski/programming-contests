#!/usr/bin/python

import heapq

def build_graph(W, D):
    G = [[0] * (len(D) + 2) for _ in range(len(D) + 2)]
    for i, a in enumerate(D):
        for j, b in enumerate(D):
            if a[0] <= b[0] <= a[2] or b[0] <= a[0] <= b[2]:
                horizontal = 0
            else:
                horizontal = max(a[0] - b[2] - 1, b[0] - a[2] - 1)
            if a[1] <= b[1] <= a[3] or b[1] <= a[1] <= b[3]:
                vertical = 0
            else:
                vertical = max(0, a[1] - b[3] - 1, b[1] - a[3] - 1)
            G[i][j] = max(horizontal, vertical)
        G[-2][i] = G[i][-2] = a[0]
        G[-1][i] = G[i][-1] = W - 1 - a[2]
    G[-1][-2] = G[-2][-1] = W
    return G

def dijkstra(G, s, t):
    S, visited = [(0, s)], {}
    while len(S) > 0:
        d, v = heapq.heappop(S)
        if v in visited:
            continue
        visited[v] = d
        if v == t:
            break
        for u, w in enumerate(G[v]):
            heapq.heappush(S, (d + w, u))
    return visited[t]

def solve(W, D):
    G = build_graph(W, D)
    return dijkstra(G, len(G) - 2, len(G) - 1)

def run():
    T = int(input())
    for i in range(T):
        W, _, B = (int(x) for x in input().split())
        D = [tuple(int(x) for x in input().split()) for _ in range(B)]
        print(f'Case #{i + 1}: {solve(W, D)}')

run()
