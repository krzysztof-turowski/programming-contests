#!/usr/bin/python3

import heapq

MOD = 1000000007

def generate(N):
    X = [int(x) for x in input().split()]
    A, B, C, D = (int(x) for x in input().split())
    while len(X) < N:
        X.append((X[-2] * A + X[-1] * B + C) % D + 1)
    return X

def solve(L, H, W):
    out, P, previous = 1, 0, -W - 1
    Q = []
    for l, h in zip(L, H):
        if l > previous + W:
            P += 2 * (W + h)
            Q = [(-h, l + W)]
        else:
            P += 2 * (l - previous)
            while Q[0][1] < l:
                heapq.heappop(Q)
            if h > -Q[0][0]:
                P += 2 * (h + Q[0][0])
            heapq.heappush(Q, (-h, l + W))
        out, previous = (out * P) % MOD, l
    return out

def run():
    T = int(input())
    for i in range(T):
        N, _, W = (int(x) for x in input().split())
        L, H = generate(N), generate(N)
        print('Case #{0}: {1}'.format(i + 1, solve(L, H, W)))

run()
