#!/usr/bin/python

def solve(N, L):
    out = 0
    for i in range(N - 1):
        j = i + L[i:].index(min(L[i:]))
        L[i:j + 1] = reversed(L[i:j + 1])
        out += j - i + 1
    return out

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        L = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(N, L)))

run()
