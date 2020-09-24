#!/usr/bin/python

def solve(L):
    D, base = {}, 0
    for c in L:
        if c not in D:
            D[c], base = base if base > 1 else 1 - base, base + 1
    return sum(D[c] * max(base, 2) ** i for i, c in enumerate(reversed(L)))

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(i + 1, solve(list(input()))))

run()
