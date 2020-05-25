#!/usr/bin/python

def brute_force(A, D):
    best = D
    for a in A:
        for i in range(1, D + 1):
            S = sorted([((b * i) % a != 0, (b * i) // a) for b in A])
            slices, cuts = 0, 0
            for not_full, s in S:
                if slices + s <= D:
                    slices, cuts = slices + s, cuts + s + not_full - 1
                else:
                    slices, cuts = D, cuts + D - slices
                    break
            if slices == D:
                best = min(best, cuts)
    return best

def solve(A, D):
    def gcd(a, b):
        return a if b == 0 else gcd(b, a % b)
    def test(v):
        return sum(int(a / v) for a in A) >= D
    low, high = 1 / D, max(A) * len(A)
    while low + 1 / D <= high:
        mid = (low + high) / 2
        if test(mid):
            low = mid
        else:
            high = mid
    S, best = {}, D
    for a in A:
        for d in range(1, D + 1):
            if a / d > high:
                continue
            div = gcd(a, d)
            ad, dd = a // div, d // div
            if (ad, dd) not in S:
                S[(ad, dd)] = (0, 0)
            full, slices = S[(ad, dd)]
            if slices + d <= D:
                S[(ad, dd)] = (full + 1, slices + d)
    for s in S.items():
        best = min(best, D - s[1][0])
    return best

def run():
    T = int(input())
    for i in range(T):
        _, D = [int(x) for x in input().split()]
        A = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(sorted(A), D)))

run()
