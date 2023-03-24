#!/usr/bin/python

import math
import itertools

def rotate_X(P, theta):
    R = [[1, 0, 0], [0, math.cos(theta), -math.sin(theta)], [0, math.sin(theta), math.cos(theta)]]
    return [[sum(pi * ri for (pi, ri) in zip(p, r)) for r in R] for p in P]

def rotate_Y(P, theta):
    R = [[math.cos(theta), 0, math.sin(theta)], [0, 1, 0], [-math.sin(theta), 0, math.cos(theta)]]
    return [[sum(pi * ri for (pi, ri) in zip(p, r)) for r in R] for p in P]

def rotate_Z(P, theta):
    R = [[math.cos(theta), -math.sin(theta), 0], [math.sin(theta), math.cos(theta), 0], [0, 0, 1]]
    return [[sum(pi * ri for (pi, ri) in zip(p, r)) for r in R] for p in P]

def area(P):
    return max(x[1] for x in P) - min(x[1] for x in P)

def check(C, Q, A):
    if abs(area(Q) - A) > 10e-7:
        raise Warning(A)
    R = [[sum(C[i][j] * X[i] for i in range(len(X))) for j in range(len(C))]
         for X in itertools.product([-1, 1], repeat = 3)]
    if abs(area(R) - A) > 10e-7:
        raise Warning(A)
    for c in C:
        if abs(math.sqrt(sum(x ** 2 for x in c)) - 0.5) > 10e-7:
            raise Warning(c)
    for c1, c2 in itertools.combinations(C, 2):
        numerator = sum(x * y for (x, y) in zip(c1, c2))
        denominator = math.sqrt(sum(x ** 2 for x in c1)) * math.sqrt(sum(x ** 2 for x in c2))
        if abs(math.acos(numerator / denominator) - math.pi / 2) > 10e-7:
            raise Warning(c1, c2)

def binary_search(P, A, high, low = 0):
    while abs(A - area(rotate_X(P, low))) > 10e-9 or abs(A - area(rotate_X(P, high))) > 10e-9:
        mid = (high + low) / 2
        B = area(rotate_X(P, mid))
        if A < B:
            high = mid
        else:
            low = mid
    return low

def solve(A):
    C = [[0.5, 0.0, 0.0], [0.0, 0.5, 0.0], [0.0, 0.0, 0.5]]
    Q = list(itertools.product([-0.5, 0.5], repeat = 3))
    if A <= math.sqrt(2):
        theta = binary_search(Q, A, math.pi / 4)
    else:
        C, Q = rotate_Y(C, -math.pi / 4), rotate_Y(Q, -math.pi / 4)
        theta = binary_search(Q, A, math.pi / 2 - math.atan(1 / math.sqrt(2)))
    C = rotate_X(C, theta)
    Q = rotate_X(Q, theta)
    check(C, Q, A)
    return C

def run():
    T = int(input())
    for i in range(T):
        A = float(input())
        print('Case #{0}:\n{1}'.format(i + 1, '\n'.join(' '.join(str(x) for x in p)
                                                        for p in solve(A))))

run()
