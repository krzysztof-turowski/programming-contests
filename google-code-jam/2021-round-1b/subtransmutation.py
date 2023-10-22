#!/usr/bin/python3

import itertools

def check(V, U, A, B):
    for i in range(len(V) - 1, -1, -1):
        if i < len(U):
            if U[i] > V[i]:
                return False
            V[i] -= U[i]
        if i >= B:
            V[i - A], V[i - B], V[i] = V[i - A] + V[i], V[i - B] + V[i], 0
        elif i >= A:
            V[i - A], V[i] = V[i - A] + V[i], 0
    return True

def solve(A, B, U):
    for i in itertools.count(len(U) - 1):
        if check([0] * i + [1], U, A, B):
            return i + 1
    return 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        _, A, B = (int(x) for x in input().split())
        U = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(A, B, U)))

run()
