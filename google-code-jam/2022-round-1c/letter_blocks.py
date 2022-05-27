#!/usr/bin/python

import enum
import itertools

Type = enum.Enum('Type', 'Empty Temporary Permanent')

def check(W):
    positions = [(W.index(c), W.rindex(c)) for c in set(c for c in W)]
    for u, v in itertools.combinations(positions, 2):
        if u[0] < v[0] < u[1]:
            return False
        if v[0] < u[0] < v[1]:
            return False
    return True

def build_graph(S):
    G = [[] for _ in S]
    for i, u in enumerate(S):
        for j, v in enumerate(S):
            if i == j:
                continue
            if u[-1] == v[0]:
                G[i].append(j)
    return G

def dfs(G, v, types, L):
    if types[v] != Type.Empty:
        return
    types[v] = Type.Temporary
    for u in G[v]:
        dfs(G, u, types, L)
    types[v] = Type.Permanent
    L.append(v)

def topological_order(G):
    types, L = [Type.Empty for v in G], []
    for i, _ in enumerate(G):
        if types[i] != Type.Permanent:
            dfs(G, i, types, L)
    types, out = [Type.Empty for v in G], []
    for i in L[::-1]:
        if types[i] != Type.Permanent:
            dfs(G, i, types, out)
    return out[::-1]

def solve(S):
    G = build_graph(S)
    L = topological_order(G)
    W = ''.join(S[i] for i in L)
    return W if L and check(W) else 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        print('Case #{0}: {1}'.format(i + 1, solve(input().strip().split())))

run()
