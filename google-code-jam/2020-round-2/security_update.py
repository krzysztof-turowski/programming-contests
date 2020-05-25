#!/usr/bin/python

from collections import defaultdict
import heapq

def get_graph(C, X):
    G = defaultdict(dict)
    for u in range(C):
        for v in range(C):
            if u != v and u in X and v in X:
                G[u][v] = abs(X[u] - X[v])
    return G

def shortest_paths(C, X):
    Q, L, V, G = [], [], {}, get_graph(C, X)
    heapq.heappush(Q, (0, 0))
    while len(Q) > 0:
        dv, v = heapq.heappop(Q)
        if v in V:
            continue
        V[v] = dv
        L.append(v)
        for u in G[v]:
            heapq.heappush(Q, (dv + G[v][u], u))
    return V, L

def solve(C, L, O, E):
    VL, LL, VO, LO, last = *shortest_paths(C, L), *shortest_paths(C, O), None
    for i in range(C):
        if len(LL) == 0:
            VL[LO[0]] = VL[last] + (VO[last] != VO[LO[0]])
            last, LO = LO[0], LO[1:]
        elif len(LO) == 0:
            VO[LL[0]] = VO[last] + (VL[last] != VL[LL[0]])
            last, LL = LL[0], LL[1:]
        elif LL[0] == LO[0]:
            last, LL, LO = LL[0], LL[1:], LO[1:]
        elif VO[LO[0]] > i:
            VO[LL[0]] = VO[last] + (VL[last] != VL[LL[0]])
            last, LL = LL[0], LL[1:]
        else:
            VL[LO[0]] = VL[last] + (VO[last] != VO[LO[0]])
            last, LO = LO[0], LO[1:]
    G = get_graph(C, VL)
    return ' '.join(str(G[u][v]) if G[u][v] > 0 else '1' for u, v in E)

def run():
    T = int(input())
    for i in range(T):
        C, D = [int(x) for x in input().split()]
        L, O = {0: 0}, {0: 0}
        for j, x in enumerate(input().split()):
            x = int(x)
            if x > 0:
                L[j + 1] = x
            else:
                O[j + 1] = -x
        E = [[int(x) - 1 for x in input().split()] for _ in range(D)]
        print('Case #{0}: {1}'.format(i + 1, solve(C, L, O, E)))

run()
