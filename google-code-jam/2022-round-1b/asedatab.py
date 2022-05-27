#!/usr/bin/python

import sys

def get_input(X):
    print(X)
    sys.stdout.flush()
    return int(input())

def get_sequence(k):
    if k == 0:
        return ['1']
    S = get_sequence(k - 1)
    S_double = [s + s for s in S]
    out = S_double[:]
    for s in S:
        out.append(s + '0' * len(s))
        out.extend(S_double)
    return out

def solve():
    for s in get_sequence(3):
        if get_input(s) == 0:
            return

def run():
    T = int(input())
    for _ in range(T):
        solve()

run()
