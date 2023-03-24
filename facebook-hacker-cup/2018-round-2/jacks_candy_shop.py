#!/usr/bin/python

import collections
import heapq

def solve(T, C):
    bfs, visited = [], [False] * len(T)
    Q = collections.deque()
    Q.append(0)
    while len(Q) > 0:
        v = Q.popleft()
        if visited[v]:
            continue
        visited[v] = True
        bfs.append(v)
        Q.extend(T[v])
    out = 0
    heaps = [[-i] for i in range(len(T))]
    for v in bfs[::-1]:
        H = sorted([heaps[v]] + [heaps[u] for u in T[v]], key = len, reverse = True)
        # print(v, [len(h) for h in H])
        for h in H[1:]:
            for e in h:
                heapq.heappush(H[0], e)
        for _ in range(min(len(H[0]), C[v])):
            out -= heapq.heappop(H[0])
        heaps[v] = H[0]
    return out

def run():
    T = int(input())
    for t in range(T):
        N, M, A, B = (int(x) for x in input().split())
        T = [[] for _ in range(N)]
        for i in range(1, N):
            T[int(input())].append(i)
        C = [0] * N
        for i in range(M):
            C[(A * i + B) % N] += 1
        print(f'Case #{t + 1}: {solve(T, C)}')

run()
