#!/usr/bin/python

import itertools

NEGATE = {'0': '1', '1': '0'}

def get_jumps(V):
    return sum(a != b for a, b in zip(V, V[1:] + '0'))

def apply_not(V):
    return ''.join(NEGATE[v] for v in V).lstrip('0') or '0'

def solve(S, E):
    out = []
    for v in itertools.count():
        if E.startswith(S) and v >= get_jumps(E[len(S):]):
            out.append(v + len(E) - len(S))
        if S == '0':
            if v >= get_jumps(E):
                out.append(v + len(E) - (E[0] == '0'))
            jumps = get_jumps(E[1:])
            if jumps == 0:
                out.append(v + len(E))
            elif jumps == 1:
                out.append(v + len(E) + 2)
            break
        S = apply_not(S)
    return min(out, default = 'IMPOSSIBLE')

def run():
    T = int(input())
    for i in range(T):
        S, E = input().split()
        print(f'Case #{i + 1}: {solve(S, E)}')

run()
