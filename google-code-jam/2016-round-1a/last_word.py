#!/usr/bin/python

def solve(S):
    if not S:
        return []
    M = max(S)
    L = [i for i, j in enumerate(S) if j == M]
    out = solve(S[:L[0]])
    for i, j in zip(L, L[1:] + [len(S)]):
        out += S[(i + 1):j]
    return [M] * len(L) + out

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(i + 1, ''.join(solve(input()))))

run()
