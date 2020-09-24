#!/usr/bin/python

def solve(L, P, C):
    out = 0
    while C < P / L:
        out, C = out + 1, C ** 2
    return out

def run():
    T = int(input())
    for i in range(T):
        L, P, C = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(L, P, C)))

run()
