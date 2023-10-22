#!/usr/bin/python3

import math

EPS = 10e-6

def f(s, q):
    return 1 / (1 + math.exp(q - s))

def F(s):
    return (math.log(math.exp(3 + s) + 1) - math.log(math.exp(-3 + s) + 1)) / 6

def binary(low, high, threshold):
    while low + EPS < high:
        mid = (low + high) / 2
        low, high = (low, mid) if F(mid) > threshold else (mid, high)
    return low

def solve(A):
    row = [a.count('1') / len(a) for a in A]
    S = [binary(-3.0, 3.0, r) for a, r in zip(A, row)]
    index = next((i for i, (s, r) in enumerate(zip(S, row))
                  if s > 3 - EPS and r > 0.9), None)
    if index is not None:
        return index + 1

    A_T = [[A[j][i] for j in range(len(A))] for i in range(len(A[0]))]
    column = [a.count('1') / len(a) for a in A_T]
    Q = [-binary(-3.0, 3.0, c) for a, c in zip(A_T, column)]
    P = [sum(-math.log(1 - f(s, q)) if v == '0' and f(s, q) > 0.95 else 0
             for v, q in zip(a, Q)) for a, s in zip(A, S)]
    return max((p, i) for i, p in enumerate(P))[1] + 1

def run():
    T, _ = int(input()), int(input())
    for i in range(T):
        A = [input().strip() for _ in range(100)]
        print('Case #{0}: {1}'.format(i + 1, solve(A)))

run()
