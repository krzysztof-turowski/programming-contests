#!/usr/bin/python

import sys

def solve(A, B):
    mid = int((A + B) / 2)
    print(mid)
    sys.stdout.flush()
    value = input()
    if value == 'TOO_BIG':
        solve(A, mid - 1)
    elif value == 'TOO_SMALL':
        solve(mid + 1, B)
    elif value == 'CORRECT':
        return
    elif value == 'WRONG_ANSWER':
        return

def run():
    T = int(input())
    for _ in range(T):
        A, B = [int(x) for x in input().split()]
        _ = int(input())
        solve(A + 1, B)

run()
