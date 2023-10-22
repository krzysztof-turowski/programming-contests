#!/usr/bin/python3

import collections
import math
import queue

class Heap:
    def __init__(self, M):
        self.L, self.I = [None] * (M + 1), {}

    def _swap(self, a, b):
        self.I[self.L[a][1]], self.I[self.L[b][1]] = b, a
        self.L[a], self.L[b] = self.L[b], self.L[a]


    def _sift_up(self, a):
        parent = (a - 1) // 2
        while a > 0 and self.L[a] < self.L[parent]:
            self._swap(a, parent)
            a, parent = parent, (parent - 1) // 2

    def _sift_down(self, a):
        child = 2 * a + 1
        while child < len(self.I):
            if child + 1 < len(self.I) and self.L[child] > self.L[child + 1]:
                child += 1
            if self.L[child] < self.L[a]:
                self._swap(a, child)
                a, child = child, 2 * child + 1
            else:
                break

    def get_cheapest(self):
        if len(self.I) == 0:
            return -1
        return self.L[0][0]

    def add_to_queue(self, index, cost):
        self.L[len(self.I)] = (cost, index)
        self.I[index] = len(self.I)
        self._sift_up(self.I[index])

    def remove(self, index):
        if index not in self.I:
            return
        position = self.I[index]
        self.L[position] = (-math.inf, self.L[position][1])
        self._sift_up(position)
        self._swap(0, len(self.I) - 1)
        del self.I[self.L[len(self.I) - 1][1]]
        self._sift_down(0)

    def size(self):
        return len(self.I)

def dijkstra(G, A, B):
    S, visited = [(A, None)], {}
    while len(S) > 0:
        i, parent = S[-1]
        S.pop()
        visited[i] = parent
        if i == B:
            break
        for j in G[i]:
            if j == parent:
                continue
            S.append((j, i))
    L = [B]
    while L[-1] != A:
        L.append(visited[L[-1]])
    return L[::-1]

def neighborhood(G, v, M):
    S, visited = queue.Queue(), set()
    S.put((v, 0))
    while not S.empty():
        u, distance = S.get()
        if distance > M:
            break
        if u in visited:
            continue
        visited.add(u)
        for w in G[u]:
            S.put((w, distance + 1))
    return visited

def remove(G, V, L):
    for v in V:
        S, visited = list(G[v]), set()
        while len(S) > 0:
            u = S[-1]
            S.pop()
            if u in L or u in visited:
                continue
            visited.add(u)
            S.extend(G[u])
        for u in visited:
            for w in G[u]:
                G[w].remove(u)
            del G[u]
    return G

def merge(G, u, v):
    for x in G[v]:
        G[x].remove(v)
        if x != u:
            G[x].add(u)
            G[u].add(x)
    del G[v]
    return G

def flatten(G, V, L, C, M):
    for v in V:
        S, visited = [(u, 1) for u in G[v]], set()
        D = collections.defaultdict(list)
        while len(S) > 0:
            u, depth = S[-1]
            S.pop()
            if u in L or u in visited:
                continue
            visited.add(u)
            D[depth].append(u)
            S.extend((w, depth + 1) for w in G[u])
        for depth, d in D.items():
            if depth <= M // 2:
                u = d[0]
                for w in d[1:]:
                    u, other = ((w, u) if C[u] == 0 or C[u] > C[w] > 0
                                else (u, w))
                    G = merge(G, u, other)
            else:
                for u in d:
                    for w in G[u]:
                        G[w].remove(u)
                    del G[u]
    return G

def simplify(G, C, M, A, B):
    L = dijkstra(G, A, B)
    SL = set(L)
    G = flatten(remove(G, [A, B], SL), L[1:-1], SL, C, M)
    return G, L, SL

def get_path(G, v, L):
    S = [v]
    while True:
        u = next((w for w in G[S[-1]]
                  if w not in L and (len(S) == 1 or w != S[-2])), None)
        if u is None:
            break
        S.append(u)
    return S

def solve(G, C, M, A, B):
    G, L, SL = simplify(G, C, M, A, B)
    cost, previous, Q = {}, [[] for _ in range(M)] + [[A]], Heap(len(G))
    cost[A] = 0
    Q.add_to_queue(A, 0)
    for v in L[1:]:
        previous.append([])
        restore = []
        for d, u in enumerate(get_path(G, v, SL)):
            if C[u] != 0 and Q.get_cheapest() >= 0:
                cost[u] = Q.get_cheapest() + C[u]
                Q.add_to_queue(u, cost[u])
                previous[-d - 1].append(u)
            else:
                cost[u] = -1
            for w in previous[-M - 1 + d]:
                Q.remove(w)
            if d > 0:
                restore.extend(previous[-M - 1 + d])
        for w in restore:
            Q.add_to_queue(w, cost[w])
    V = neighborhood(G, B, M)
    return min((cost[v] for v in V if cost[v] != -1), default = -1)

def naive(G, C, M, A, B):
    N = len(G)
    D = [[math.inf] * N for _ in range(N)]
    for i in range(N):
        D[i][i] = 0
        for j in G[i]:
            D[i][j] = 1
    for k in range(N):
        for i in range(N):
            for j in range(N):
                D[i][j] = min(D[i][j], D[i][k] + D[k][j])
    H = collections.defaultdict(list)
    for i in range(N):
        for j in range(N):
            if D[i][j] <= M:
                H[i].append(j)
    cost, S = [None] * N, {(0, A)}
    while len(S) > 0:
        distance, i = min(S)
        S.remove((distance, i))
        if cost[i] is not None:
            continue
        cost[i] = distance
        for j in H[i]:
            if C[j] > 0:
                S.add((distance + C[j], j))
    return min((cost[c] for c in H[B] if cost[c] is not None), default = -1)

def run():
    T = int(input())
    for i in range(T):
        N, M, A, B = (int(x) for x in input().split())
        G, C = collections.defaultdict(set), [None] * N
        for j in range(N):
            p, C[j] = (int(x) for x in input().split())
            if j > 0:
                G[j].add(p - 1)
                G[p - 1].add(j)
        print('Case #{0}: {1}'.format(i + 1, solve(G, C, M, A - 1, B - 1)))

run()
