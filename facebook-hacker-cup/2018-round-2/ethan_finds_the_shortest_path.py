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

def solve(N, K):
    E, W = [(1, N, K)], 0
    L = min(N, K) - 2
    if L > 0:
        E += [(i, i + 1, K - i) for i in range(1, L + 1)] + [(L + 1, N, K - L - 1)]
        W += K * L - (L + 1) * (L + 2) // 2
    return f'{W}\n{len(E)}\n' + '\n'.join(f'{u} {v} {w}' for u, v, w in E)

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(N, K)}')

run()
