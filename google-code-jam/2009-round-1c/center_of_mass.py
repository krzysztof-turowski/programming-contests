#!/usr/bin/python

import decimal
import math

def solve(A):
    def distance(A, t):
        x = sum(a[0] + a[3] * t for a in A) / len(A)
        y = sum(a[1] + a[4] * t for a in A) / len(A)
        z = sum(a[2] + a[5] * t for a in A) / len(A)
        return math.sqrt(x ** 2 + y ** 2 + z ** 2)
    low, high = decimal.Decimal(0), decimal.Decimal(10 ** 50)
    low_distance, high_distance = distance(A, low), distance(A, high)
    while high - low > 10 ** -8:
        mid = (low + high) / 2
        mid_distance = distance(A, mid)
        if low_distance < high_distance:
            high, high_distance = mid, mid_distance
        else:
            low, low_distance = mid, mid_distance
    return low_distance, low

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        A = [tuple(decimal.Decimal(x) for x in input().split())
             for _ in range(N)]
        print('Case #{0}: {1:.6f} {2:.6f}'.format(i + 1, *solve(A)))

run()
