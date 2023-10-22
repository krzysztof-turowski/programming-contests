#!/usr/bin/python3

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
    out, P, I = 1, 0, blist.sortedlist()
    for l, h, w in zip(L, H, W):
        P += 2 * (w + h)
        start = bisect.bisect(I, (l, 0))
        if start > 0 and I[start - 1][1] >= l:
            start -= 1
        end = bisect.bisect(I, (l + w, math.inf))
        left, right = l, l + w
        P -= 2 * h * (end - start)
        for s, e in I[start:end]:
            left, right = min(s, left), max(e, right)
            P -= 2 * (min(e, l + w) - max(s, l))
        del I[start:end]
        I.add((left, right))
        out = (out * P) % MOD
    return out

def run():
    T = int(input())
    for i in range(T):
        N, _ = (int(x) for x in input().split())
        L, W, H = generate(N), generate(N), generate(N)
        print('Case #{0}: {1}'.format(i + 1, solve(L, H, W)))

run()
