#!/usr/bin/python

import collections

class Fenwick:
    def __init__(self, n):
        self.data = [0] * n

    def count(self, index):
        out = 0
        while index > 0:
            out += self.data[index]
            index -= index & (-index)
        return out

    def update(self, index):
        while index < len(self.data):
            self.data[index] += 1
            index += index & (-index)

def solve(P, S, K):
    G = [[] for _ in S]
    for u, v in enumerate(P, start = 1):
        G[v].append(u)

    Q, start, end, N = collections.deque([0]), [None] * len(S), [None] * len(S), 0
    while Q:
        v, N = Q.popleft(), N + 1
        if start[v]:
            end[v] = N
        else:
            start[v] = N
            Q.appendleft(v)
            Q.extendleft(G[v])

    S, F, first, out = list(sorted((s, v) for v, s in enumerate(S))), Fenwick(N + 1), 0, 0
    for S_last, v in S:
        while K * S[first][0] < S_last:
            F.update(end[S[first][1]])
            first += 1
        in_tree = F.count(end[v]) - F.count(start[v] - 1)
        out += in_tree * (first - in_tree)
    return out

def run():
    T = int(input())
    for t in range(T):
        _, K = (int(x) for x in input().split())
        S = [int(x) for x in input().split()]
        P = [int(x) - 1 for x in input().split()]
        print(f'Case #{t + 1}: {solve(P, S, K)}')

run()
