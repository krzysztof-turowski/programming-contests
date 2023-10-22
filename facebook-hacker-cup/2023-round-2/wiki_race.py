#!/usr/bin/python3

import collections

def merge(P, S, u, v):
    S[u] |= S[v]
    P[u] = P[v]

def compress(P, S, N):
    children = [0] * N
    for v in P:
        if v is not None:
            children[v] += 1
    L = [i for i, v in enumerate(children) if v == 0]
    visited = [False] * N
    Q = collections.deque(L)
    while Q:
        v = Q.popleft()
        if visited[v] or P[v] is None:
            continue
        if children[P[v]] == 1:
            merge(P, S, v, P[v])
            Q.append(v)
        else:
            visited[v] = True
            Q.append(P[v])
    return L

def check_candidate(P, S, l, c, visited):
    Q = collections.deque([l])
    while Q:
        v = Q.popleft()
        if visited[v] and P[v] is None:
            continue
        visited[v] = True
        if c in S[v]:
            return True
        if not visited[P[v]]:
            Q.append(P[v])
    return False

def check_candidates(P, S, L, c, N):
    visited = [False] * N
    return 1 if all(check_candidate(P, S, l, c, visited) for l in L) else 0

def solve(P, S, N):
    F = collections.defaultdict(int)
    for s in S:
        for w in s:
            F[w] += 1
    L = compress(P, S, N)
    return sum(check_candidates(P, S, L, k, N) for k, v in F.items() if v >= len(L))

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        P = [None] + [int(x) - 1 for x in input().split()]
        S = [set(input().split()[1:]) for _ in range(N)]
        print(f'Case #{i + 1}: {solve(P, S, N)}')

run()
