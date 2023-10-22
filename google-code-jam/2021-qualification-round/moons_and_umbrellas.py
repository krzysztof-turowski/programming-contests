#!/usr/bin/python3

import math

def solve(S, X, Y):
    out = {
        'C': 0 if S[0] != 'J' else math.inf,
        'J': 0 if S[0] != 'C' else math.inf}
    for s in S[1:]:
        if s == 'C':
            out = {'C': min(out['C'], out['J'] + Y), 'J': math.inf}
        elif s == 'J':
            out = {'C': math.inf, 'J': min(out['C'] + X, out['J'])}
        else:
            out = {
                'C': min(out['C'], out['J'] + Y),
                'J': min(out['C'] + X, out['J'])}
    return min(out.values())

def run():
    T = int(input())
    for i in range(T):
        X, Y, S = input().split()
        print('Case #{0}: {1}'.format(i + 1, solve(S, int(X), int(Y))))

run()
