#!/usr/bin/python

import math

def gcd(a, b):
    return gcd(b, a % b) if b != 0 else a

def get_divisors(X):
    L = []
    for i in range(1, X + 1):
        if i * i > X:
            yield from reversed(L)
            return
        if X % i == 0:
            yield i
            L.append(X // i)

def check(A, B, L, H):
    if H < A or B < L:
        return None
    for q in get_divisors(B // A):
        out = q * A
        if L <= out <= H:
            return out
    return None

def solve(N, L, H):
    A = 1
    for i, v in enumerate(N):
        B = v
        for b in N[i + 1:]:
            B = gcd(B, b)
            if B < L or B % A != 0:
                break
        else:
            out = check(A, B, L, H)
            if out is not None:
                return out
        A = A * v // gcd(A, v)
        if A > H:
            return 'NO'
    out = math.ceil(L / A) * A
    return out if L <= out <= H else 'NO'

def run():
    T = int(input())
    for i in range(T):
        _, L, H = (int(x) for x in input().split())
        N = {int(x) for x in input().split()}
        print('Case #{0}: {1}'.format(i + 1, solve(sorted(N), L, H)))

run()
