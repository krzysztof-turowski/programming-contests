#!/usr/bin/python

import decimal
import functools
import math

@functools.lru_cache(maxsize = 10 ** 6)
def brute_force(A, B):
    if A == B:
        return False
    A, B = max(A, B), min(A, B)
    return not all(
        brute_force(A - k * B, B) for k in range(1, math.ceil(A / B)))

def solve(A1, A2, B1, B2):
    out, phi = 0, decimal.Decimal(0.5) + decimal.Decimal(5).sqrt() / 2
    for a in range(A1, A2 + 1):
        C1, C2 = math.ceil((phi - 1) * a), math.ceil(phi * a) - 1
        if C1 > B2:
            out += B2 + 1 - B1
        elif C2 >= B2:
            out += max(C1 - B1, 0)
        elif C2 >= B1:
            out += max(B2 - C2, 0) + max(C1 - B1, 0)
        else:
            out += B2 + 1 - B1
    return out

def run():
    T = int(input())
    for i in range(T):
        A1, A2, B1, B2 = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(A1, A2, B1, B2)))

run()
