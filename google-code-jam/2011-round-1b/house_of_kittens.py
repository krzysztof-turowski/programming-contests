#!/usr/bin/python

import collections
import math

def build_graph(N, E):
    G = collections.defaultdict(list)
    for i in range(1, N):
        G[i - 1].append(i)
        G[i].append(i - 1)
    G[0].append(N - 1)
    G[N - 1].append(0)
    for _ in range(2):
        for u, v in E:
            G[u].append(v)
            G[v].append(u)
    return G

def get_angle(a, b, c):
    angle = (math.atan2(c[1] - b[1], c[0] - b[0])
             - math.atan2(a[1] - b[1], a[0] - b[0]))
    return angle if angle >= 0 else angle + 2 * math.pi

def sort_neighbors(G, P):
    for v, _ in enumerate(G):
        u = v - 1 if v > 0 else len(G) - 1
        G[v] = sorted(G[v], key = lambda w: get_angle(P[u], P[v], P[w]))

def split_polygons(G):
    out = []
    for v, Gv in enumerate(G):
        while len(Gv) > 0:
            u1, u2 = Gv[-1], v
            out.append([u2])
            while u1 != v:
                index = max(i for i, w in enumerate(G[u1]) if w == u2)
                G[u1].remove(u2)
                G[u2].remove(u1)
                u1, u2 = G[u1][index], u1
                out[-1].append(u2)
            G[u1].remove(u2)
            G[u2].remove(u1)
    return out

def align_polygon(polygon, index, colors):
    polygon = polygon[index:] + polygon[:index]
    if colors[polygon[1]] is None:
        polygon = [polygon[0]] + polygon[:0:-1]
    return polygon

def solve(N, E):
    G = build_graph(N, E)
    P = [(math.sin(2 * math.pi * i / N), math.cos(2 * math.pi * i / N))
         for i in range(N)]
    sort_neighbors(G, P)
    polygons = split_polygons(G)
    colors = min(len(p) for p in polygons)
    out = [None] * N
    out[0], out[1] = 0, 1
    while any(v is None for v in out):
        for polygon in polygons:
            indices = [i for i, v in enumerate(polygon) if out[v] is not None]
            if len(indices) != 2:
                continue
            used = set(out[polygon[i]] for i in indices)
            C = list(used) + list(set(range(colors)) - used)
            polygon = align_polygon(polygon, indices[0], out)
            for v, c in zip(polygon, C * len(polygon)):
                if out[v] is None:
                    out[v] = c
            if out[polygon[0]] == out[polygon[-1]]:
                out[polygon[-1]] = min(
                    set(range(colors)) - set((out[polygon[0]], out[polygon[-2]])))
    check(E, out)
    return str(colors) + '\n' + ' '.join(str(i + 1) for i in out)

def check(E, out):
    for u, v in E:
        assert out[u] is None or out[u] != out[v]
    for i, v in enumerate(out):
        assert v is None or v != out[(i + 1) % len(out)]

def run():
    T = int(input())
    for i in range(T):
        N, _ = (int(x) for x in input().split())
        E = list(zip(
            (int(x) - 1 for x in input().split()),
            (int(x) - 1 for x in input().split())))
        print('Case #{0}: {1}'.format(i + 1, solve(N, E)))

run()
