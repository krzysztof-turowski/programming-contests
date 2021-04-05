#!/usr/bin/python

import copy
import itertools

def aggregate(A):
    for i, a in enumerate(A):
        A[i] = list(itertools.accumulate(a))
    for j, _ in enumerate(A[0]):
        for i in range(1, len(A)):
            A[i][j] += A[i - 1][j]
    return A

def get_value(A, B, x, y, D):
    out = A[x - 1][y - 1]
    if x - D > 0:
        out -= A[x - D - 1][y - 1]
    if y - D > 0:
        out -= A[x - 1][y - D - 1]
    if x - D > 0 and y - D > 0:
        out += A[x - D - 1][y - D - 1]
    return out - B[x - 1][y - 1] - B[x - D][y - 1] - B[x - 1][y - D] - B[x - D][y - D]

def solve(R, C, B0):
    B = aggregate(copy.deepcopy(B0))
    X0 = [[(2 * i + 1) * b for b in row] for i, row in enumerate(B0)]
    X = aggregate(copy.deepcopy(X0))
    Y0 = [[(2 * j + 1) * b for j, b in enumerate(row)] for row in B0]
    Y = aggregate(copy.deepcopy(Y0))
    for D in range(min(R, C), 2, -1):
        for x in range(D, R + 1):
            for y in range(D, C + 1):
                mass = get_value(B, B0, x, y, D)
                if get_value(X, X0, x, y, D) != (2 * x - D) * mass:
                    continue
                if get_value(Y, Y0, x, y, D) != (2 * y - D) * mass:
                    continue
                return D
    return 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        R, C, _= (int(x) for x in input().split())
        B = [[int(x) for x in list(input().strip())] for _ in range(R)]
        print('Case #{0}: {1}'.format(i + 1, solve(R, C, B)))

run()
