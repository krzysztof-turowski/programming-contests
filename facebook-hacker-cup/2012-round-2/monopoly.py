#!/usr/bin/python3

import math

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
        return self.parent[xset]

def merge_heights(A, B):
    a_low, b_low = min(A), min(B)
    return [math.inf] + [
        min(max(a, b_low + 1), max(b, a_low + 1)) for a, b in zip(A[:-1], B[:-1])]

def solve(N, D, M):
    S, H = DisjointSet(N), [[1] + [math.inf] * D for i in range(N)]
    for a, b in M:
        a, b = S.find(a - 1), S.find(b - 1)
        H[S.union(a, b)] = merge_heights(H[a], H[b])
    return min(H[S.find(0)])

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        N, D = (int(x) for x in input().split())
        M = [tuple(int(x) for x in input().split()) for _ in range(1, N)]
        print(f'Case #{i + 1}: {solve(N, D, M)}')

run()
