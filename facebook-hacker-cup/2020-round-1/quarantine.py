#!/usr/bin/python3

import collections
import queue

def generate(N):
    X = [0] + [int(x) for x in input().split()]
    A, B, C = (int(x) for x in input().split())
    while len(X) < N:
        X.append((X[-2] * A + X[-1] * B + C) % len(X) + 1)
    return X

def bfs(G, S):
    out, visited = [], set()
    for v in G:
        if v in visited or S[v - 1] == '#':
            continue
        current, Q = set(), queue.Queue()
        Q.put(v)
        while not Q.empty():
            u = Q.get()
            if u in current or S[u - 1] == '#':
                continue
            current.add(u)
            for w in G[u]:
                Q.put(w)
        out.append((len(current), current))
        visited |= current
    return sorted(out, reverse = True), visited

def find_root(G, S, C):
    for v in C:
        for u in G[v]:
            if S[u - 1] != '#':
                return v
    return None

def merge(G, u, v):
    for w in G[v]:
        G[w].remove(v)
        if w != u:
            G[w].add(u)
            G[u].add(w)
    del G[v]
    return G

def remove(G, v):
    for w in G[v]:
        G[w].remove(v)
    del G[v]
    return G

def squeeze(G, C):
    for _, c in C:
        u = min(c)
        for v in c:
            if u != v:
                G = merge(G, u, v)
    return G

def get_all_lengths(G, v, V, N):
    order, visited = [], {}
    Q = queue.Queue()
    Q.put((v, None))
    while not Q.empty():
        u, parent = Q.get()
        if u in visited:
            continue
        if parent is not None:
            order.append((u, parent))
        visited[u] = [1 if u in V else 0, 0]
        for w in G[u]:
            Q.put((w, u))
    for u, parent in order[::-1]:
        visited[parent][0] += visited[u][0]
        visited[u][1] += (N - visited[u][0]) * visited[u][0]
        visited[parent][1] += visited[u][1]
    return visited[v][1]

def get_lengths_to_root(G, v, V, visited = None):
    order, visited = [], {}
    Q = queue.Queue()
    Q.put((v, None))
    while not Q.empty():
        u, parent = Q.get()
        if u in visited:
            continue
        if parent is not None:
            order.append((u, parent))
        visited[u] = [1 if u in V else 0, 0]
        for w in G[u]:
            Q.put((w, u))
    for u, parent in order[::-1]:
        visited[parent][0] += visited[u][0]
        visited[parent][1] += visited[u][1] + visited[u][0]
    return visited[v][1]

def solve(N, S, E):
    def b2(K):
        return K * (K - 1) // 2
    G = collections.defaultdict(set)
    for i, e in enumerate(E, start = 1):
        if e == 0:
            continue
        G[i].add(e)
        G[e].add(i)
    C, V = bfs(G, S)
    out, ways = 0, 0
    if len(C) == 0:
        V = set(G.keys())
        ways += get_all_lengths(G, min(V), V, len(V))
    elif len(C) == 1:
        out += b2(len(V))
        ways += get_all_lengths(G, min(V), V, len(V))
        C, _ = bfs(G, ''.join('*' if s == '#' else '#' for s in S))
        roots = [find_root(G, S, c) for _, c in C]
        for v in V:
            G = remove(G, v)
        for root, (w, c) in zip(roots, C):
            ways += w * (N - w)
            ways += get_all_lengths(G, root, c, N)
    elif C[0][0] == C[1][0]:
        G = squeeze(G, C)
        V = {min(c[1]) for c in C if c[0] == C[0][0]}
        out += b2(C[0][0] + C[1][0]) + sum(b2(c[0]) for c in C[2:])
        ways += C[0][0] ** 2 * get_all_lengths(G, min(C[0][1]), V, len(V))
    else:
        G = squeeze(G, C)
        V = {min(c[1]) for c in C if c[0] == C[1][0]}
        out += b2(C[0][0] + C[1][0]) + sum(b2(c[0]) for c in C[2:])
        ways += C[0][0] * C[1][0] * get_lengths_to_root(G, min(C[0][1]), V)
    return (out, ways)

def run():
    T = int(input())
    for i in range(T):
        N, _ = (int(x) for x in input().split())
        S = input()
        E = generate(N)
        print('Case #{0}: {1} {2}'.format(i + 1, *solve(N, S, E)))

run()
