#!/usr/bin/python

class DisjointSet:
    def __init__(self, n):
        self.rank, self.parent = [1] * n, list(range(n))

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        xset, yset = self.find(x), self.find(y)
        if self.rank[xset] < self.rank[yset]:
            self.parent[xset] = yset
        elif self.rank[xset] > self.rank[yset]:
            self.parent[yset] = xset
        else:
            self.parent[yset] = xset
            self.rank[xset] = self.rank[xset] + 1

def solve(N, K, E):
    out, S = 0, DisjointSet(N)
    for u, v in E:
        if min(u, v) < K:
            continue
        S.union(u, v)
    for u, v in E:
        if min(u, v) >= K:
            continue
        u, v = S.find(u), S.find(v)
        if u != v:
            S.union(u, v)
        else:
            out += 1
    return out

def run():
    T = int(input())
    for i in range(T):
        N, M, K = (int(x) for x in input().split())
        E = [tuple(int(x) for x in input().split()) for _ in range(M)]
        print(f'Case #{i + 1}: {solve(N, K, E)}')

run()
