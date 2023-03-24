#!/usr/bin/python

import math
import queue

def find_first_after(C, D):
    S, W, T = C
    threshold = T + ((D - T) // (S + W)) * (S + W)
    assert D - (S + W) < threshold <= D
    return (D, threshold + S) if threshold + S > D else (threshold + S + W, D)

def solve(N, M, C):
    out = [[math.inf for _ in range(2 * M)] for _ in range(2 * N)]
    Q = queue.PriorityQueue()
    Q.put((0, 2 * N - 1, 0))
    out[2 * N - 1][0] = 0
    while not Q.empty():
        d, h, w = Q.get()
        if h == 0 and w == 2 * M - 1:
            break
        ud, lr = find_first_after(C[h // 2][w // 2], d)
        if h % 2 == 0 and h > 0 and d + 2 < out[h - 1][w]:
            out[h - 1][w] = d + 2
            Q.put((out[h - 1][w], h - 1, w))
        if h % 2 == 0 and ud + 1 < out[h + 1][w]:
            out[h + 1][w] = ud + 1
            Q.put((out[h + 1][w], h + 1, w))
        if h % 2 == 1 and ud + 1 < out[h - 1][w]:
            out[h - 1][w] = ud + 1
            Q.put((out[h - 1][w], h - 1, w))
        if h % 2 == 1 and h < 2 * N - 1 and d + 2 < out[h + 1][w]:
            out[h + 1][w] = d + 2
            Q.put((out[h + 1][w], h + 1, w))
        if w % 2 == 0 and w > 0 and d + 2 < out[h][w - 1]:
            out[h][w - 1] = d + 2
            Q.put((out[h][w - 1], h, w - 1))
        if w % 2 == 0 and lr + 1 < out[h][w + 1]:
            out[h][w + 1] = lr + 1
            Q.put((out[h][w + 1], h, w + 1))
        if w % 2 == 1 and lr + 1 < out[h][w - 1]:
            out[h][w - 1] = lr + 1
            Q.put((out[h][w - 1], h, w - 1))
        if w % 2 == 1 and w < 2 * M - 1 and d + 2 < out[h][w + 1]:
            out[h][w + 1] = d + 2
            Q.put((out[h][w + 1], h, w + 1))
    return out[0][2 * M - 1]

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        C = [list(zip(*([iter(int(x) for x in input().split())] * 3)))
             for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(N, M, C)))

run()
