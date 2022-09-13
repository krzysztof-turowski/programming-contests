#!/usr/bin/python

import functools

def solve(G, Q):
    @functools.lru_cache(maxsize = 10 ** 6)
    def capacity(a, b):
        direct = G[a][b] if b in G[a] else 0
        u, v = (G[a], G[b]) if len(G[a]) < len(G[b]) else (G[b], G[a])
        return 2 * direct + sum(min(u[w], v[w]) for w in u if w in v)
    return ' '.join(str(capacity(a, b)) for a, b in Q)

def run():
    T = int(input())
    for t in range(T):
        N, M, Q = (int(x) for x in input().split())
        G = [{} for _ in range(N)]
        for _ in range(M):
            a, b, c = (int(x) for x in input().split())
            G[a - 1][b - 1] = G[b - 1][a - 1] = c
        Q = [tuple(int(x) - 1 for x in input().split()) for _ in range(Q)]
        print(f'Case #{t + 1}: {solve(G, Q)}')

run()
