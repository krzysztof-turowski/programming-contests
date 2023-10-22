#!/usr/bin/python3

import itertools
import math

def get_score(SA, a, b):
    return SA[(a + b) // 2] if a < b else SA[-1] - SA[(a + b - 1) // 2]

def solve(A, L, R):
    SA = list(itertools.accumulate(A))
    if L[1] < R[0]:
        return get_score(SA, L[1], R[0])
    if R[1] < L[0]:
        return get_score(SA, L[0], R[1])
    best = 0
    for l in range(L[0], L[1] + 1):
        left = get_score(SA, l, min(l - 1, R[1])) if l > R[0] else math.inf
        right = get_score(SA, l, max(l + 1, R[0])) if l < R[1] else math.inf
        best = max(best, min(left, right))
    return best

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = [int(x) for x in input().split()]
        X = [int(x) - 1 for x in input().split()]
        print(f'Case #{i + 1}: {solve(A, (X[0], X[1]), (X[2], X[3]))}')

run()
