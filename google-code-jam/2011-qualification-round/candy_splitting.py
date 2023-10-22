#!/usr/bin/python3

def solve(L):
    out = 0
    for v in L:
        out ^= v
    if out != 0:
        return 'NO'
    return sum(L) - min(L)

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        L = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(L)))

run()
