#!/usr/bin/python

import sys

def apply_value(C, P):
    print("{0} {1}".format(C + 1, 2))
    sys.stdout.flush()
    X, Y = [int(x) for x in input().split()]
    if X == -1 and Y == -1:
        exit(1)
    elif X == 0 and Y == 0:
        return True
    P[X - 1] |= 2 ** (Y - 1)
    return False

def solve(C, P):
    if C == 1:
        while not apply_value(C, P):
            pass
        return
    else:
        while P[C + 1] != 7:
            apply_value(C, P)
        solve(C - 1, P)

def run():
    T = int(input())
    for _ in range(T):
        A = int(input())
        solve((A + 2) // 3 - 2, [0] * ((A + 2) // 3))

run()
