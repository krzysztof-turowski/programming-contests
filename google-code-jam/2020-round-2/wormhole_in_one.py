#!/usr/bin/python

from collections import defaultdict

def get_lines(L, N):
    V, D = list(range(N)), defaultdict(int)
    for i, j in L:
        if V[i] != V[j]:
            D[i] += 1
        V[j] = V[i]
    out = [N - sum(D.values()) - len(D), 0, 0]
    for line in D.values():
        line += 1
        if line % 2 == 1:
            out[1] += (line - 3) // 2
            out[2] += 1
        else:
            out[1] += line // 2
    return out

def solve(P):
    def nwd(a, b):
        if a < b:
            a, b = b, a
        while b > 0:
            a, b = b, a % b
        return a
    def get_direction(u, v):
        if u[0] == v[0]:
            return (0, 1)
        if u[1] == v[1]:
            return (1, 0)
        if u[0] < v[0]:
            u, v = v, u
        d = nwd(abs(u[0] - v[0]), abs(u[1] - v[1]))
        return ((u[0] - v[0]) // d, (u[1] - v[1]) // d)
    D = defaultdict(list)
    for i, u in enumerate(P):
        for j, v in enumerate(P):
            if i >= j:
                continue
            D[get_direction(u, v)].append((i, j))
    out = 1
    for L in D.values():
        S = get_lines(L, len(P))
        if S[2] % 2 == 1:
            out = max(out, (S[0] > 0) + 3 * S[2] + 2 * S[1])
        else:
            out = max(out, (S[0] > 0) + 3 * S[2] + 2 * S[1] + (S[0] > 1))
    return out

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        P = [[int(x) for x in input().split()] for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(P)))

run()
