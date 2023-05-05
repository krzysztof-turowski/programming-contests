#!/usr/bin/python

import collections

def get_cycle(v, D):
    C, u = [v], D[v]
    while u != v:
        C.append(u)
        u = D[u]
    return C

def solve(D, C):
    out, R, indeg = 0, [0] * len(D), collections.Counter(D)
    Q = collections.deque(i for i, _ in enumerate(D) if i not in indeg)
    while len(Q):
        v = Q.pop()
        u = D[v]
        out, R[u], indeg[u] = out + max(C[v] - R[v], 0), R[u] + C[v], indeg[u] - 1
        if indeg[u] == 0:
            Q.append(u)
    cost, cost_in_cycle = [0] * len(D), [0] * len(D)
    for u, v in enumerate(D):
        if indeg[u] == 0:
            continue
        cost[u] = max(C[u] - R[u], 0)
        cost_in_cycle[v] = max(C[v] - R[v] - C[u], 0)
    for v, d in indeg.items():
        if d == 0:
            continue
        C = get_cycle(v, D)
        total = sum(cost_in_cycle[u] for u in C)
        out += min(total + cost[u] - cost_in_cycle[u] for u in C)
        for u in C:
            indeg[u] = 0
    return out

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        D = [int(x) - 1 for x in input().split()]
        C = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(D, C)}')

run()
