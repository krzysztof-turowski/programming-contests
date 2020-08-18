#!/usr/bin/python

import bisect
import math

import blist

MOD = 1000000007

def generate(N):
    X = [int(x) for x in input().split()]
    A, B, C, D = (int(x) for x in input().split())
    while len(X) < N:
        X.append((X[-2] * A + X[-1] * B + C) % D + 1)
    return X

def solve(L, H, W):
    out, P, I_x, I_y = 1, 0, blist.sortedlist(), blist.sortedlist()
    I_y.add((-math.inf, 0, 0))
    I_y.add((math.inf, 0, 0))
    for l, h, w in zip(L, H, W):
        P += 2 * (w + h)
        start = bisect.bisect(I_y, (l, 0, 0))
        end = bisect.bisect(I_y, (l + w, math.inf, math.inf))
        left, right = I_y[start - 1][2], I_y[end][1]
        P -= (left + right)
        for _, s, e in I_y[start:end]:
            P -= abs(s - e)
        del I_y[start:end]
        if left < h:
            I_y.add((l, left, h))
        if right < h:
            I_y.add((l + w, h, right))

        start = bisect.bisect(I_x, (l, 0))
        if start > 0 and I_x[start - 1][1] >= l:
            start -= 1
        end = bisect.bisect(I_x, (l + w, math.inf))
        left, right = l, l + w
        for s, e in I_x[start:end]:
            left, right = min(s, left), max(e, right)
            P -= 2 * (min(e, l + w) - max(s, l))
        del I_x[start:end]
        I_x.add((left, right))
        out = (out * P) % MOD
    return out

def run():
    T = int(input())
    for i in range(T):
        N, _ = (int(x) for x in input().split())
        L, W, H = generate(N), generate(N), generate(N)
        print('Case #{0}: {1}'.format(i + 1, solve(L, H, W)))

run()
