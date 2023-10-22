#!/usr/bin/python3

import re

def query(T, Q):
    if len(T) == 1:
        return T[0]
    return T[0] * (query(T[2], Q) if T[1] in Q else query(T[3], Q))

def solve(S, Q):
    R = re.sub(r'([a-z]+)', r'"\1",', re.sub(r'([\.\d]+|\))', r'\1,', S))
    T = eval(R)[0]
    return '\n'.join('{:.9f}'.format(query(T, set(q[2:]))) for q in Q)

def run():
    T = int(input())
    for i in range(T):
        A = int(input())
        S = ' '.join(input() for _ in range(A))
        L = int(input())
        Q = [list(input().split()) for _ in range(L)]
        print('Case #{0}:\n{1}'.format(i + 1, solve(S, Q)))

run()
