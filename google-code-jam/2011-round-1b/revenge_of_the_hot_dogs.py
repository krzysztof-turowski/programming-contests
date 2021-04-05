#!/usr/bin/python

import decimal

def check(L, D):
    if any(v > 1 for _, v in L):
        return False
    return all(b[0] - a[0] >= D for a, b in zip(L, L[1:]))

def shift(L, D, T):
    right = L[0][0] - T - D
    for i, _ in enumerate(L):
        left = max(right + D, L[i][0] - T)
        right = left + (L[i][1] - 1) * D
        if right > L[i][0] + T:
            return False
    return True

def solve(L, D):
    if check(L, D):
        return 0
    low, high = decimal.Decimal(0), decimal.Decimal(sum(v for _, v in L) * D)
    while high - low > 10 ** -10:
        mid = (low + high) / 2
        if shift(L, D, mid):
            high = mid
        else:
            low = mid
    return low

def run():
    T = int(input())
    for i in range(T):
        C, D = (int(x) for x in input().split())
        L = [tuple(int(x) for x in input().split()) for _ in range(C)]
        print('Case #{0}: {1:.9f}'.format(i + 1, solve(L, D)))

run()
