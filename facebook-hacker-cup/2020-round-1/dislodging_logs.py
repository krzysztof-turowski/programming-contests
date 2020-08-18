#!/usr/bin/python

import bisect

def generate(N):
    X = [int(x) for x in input().split()]
    A, B, C, D = (int(x) for x in input().split())
    while len(X) < N:
        X.append((X[-2] * A + X[-1] * B + C) % D + 1)
    return sorted(X)

def check(P, Q, limit):
    left = 0
    for p in P:
        if p - limit > Q[left]:
            return False
        if Q[left] < p:
            left = max(
                bisect.bisect(Q, (p + Q[left] + limit) / 2),
                bisect.bisect(Q, 2 * Q[left] - p + limit))
        else:
            left = max(left, bisect.bisect(Q, p + limit))
        if left == len(Q):
            return True
    return False

def solve(P, Q):
    low, high = 0, 10 ** 24
    while low + 1 < high:
        mid = (low + high) // 2
        # print('check', mid, check(P, Q, mid))
        if check(P, Q, mid):
            high = mid
        else:
            low = mid
    return high

def run():
    T = int(input())
    for i in range(T):
        N, M, _, S = (int(x) for x in input().split())
        assert S == 0
        P = generate(N)
        Q = generate(M)
        # print(P, Q)
        print('Case #{0}: {1}'.format(i + 1, solve(P, Q)))

run()
