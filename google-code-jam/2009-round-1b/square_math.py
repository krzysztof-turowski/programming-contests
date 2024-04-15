#!/usr/bin/python3

import collections
import queue

VALUES, MAX = 250, 1000
DIRECTIONS = [
    (-1, 0, 0, 0), (-1, 0, -2, 0), (-1, 0, -1, -1), (-1, 0, -1, 1),
    (1, 0, 0, 0), (1, 0, 2, 0), (1, 0, 1, -1), (1, 0, 1, 1),
    (0, -1, 0, -2), (0, -1, 0, 0), (0, -1, -1, -1), (0, -1, 1, -1),
    (0, 1, 0, 2), (0, 1, 0, 0), (0, 1, -1, 1), (0, 1, 1, 1)]

def solve(B, Q):
    L, S, V = queue.Queue(), collections.defaultdict(str), set()
    for x, b in enumerate(B):
        for y, c in enumerate(b):
            if ord('0') <= ord(c) <= ord('9'):
                S[(x, y, int(c))] = c
                L.put((x, y, int(c)))
    while len(V) < len(Q):
        x, y, value = L.get()
        expression = S[(x, y, value)]
        for s_x, s_y, m_x, m_y in DIRECTIONS:
            x_prim, y_prim = x + m_x, y + m_y
            if not (0 <= x_prim < len(B) and 0 <= y_prim < len(B)):
                continue
            x_sign, y_sign = x + s_x, y + s_y
            if not (0 <= x_sign < len(B) and 0 <= y_sign < len(B)):
                continue
            sign, v = B[x_sign][y_sign], int(B[x_prim][y_prim])
            expression_prim = expression + sign + B[x_prim][y_prim]
            value_prim = value + v if sign == '+' else value - v
            if value_prim in Q:
                V.add(value_prim)
            if (x_prim, y_prim, value_prim) in S:
                continue
            S[(x_prim, y_prim, value_prim)] = expression_prim
            L.put((x_prim, y_prim, value_prim))
    out = [min((S[(i, j, q)] for i, b in enumerate(B) for j, c in enumerate(b)
               if ord('0') <= ord(c) <= ord('9') and (i, j, q) in S), key = len) for q in Q]
    return '\n'.join(out)

def run():
    T = int(input())
    for i in range(T):
        W, _ = (int(x) for x in input().split())
        B = [input().strip() for _ in range(W)]
        Q = [int(x) for x in input().split()]
        print(f'Case #{i + 1}:\n{solve(B, Q)}')

run()
