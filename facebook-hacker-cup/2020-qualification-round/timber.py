#!/usr/bin/python

import copy

def solve(X):
    P, Q, best = copy.deepcopy(X), copy.deepcopy(X), 0
    for p, h in X.items():
        if p + h in X:
            Q[p + h] = max(Q[p + h], Q[p] + X[p + h])
    for p, h in reversed(list(X.items())):
        if p - h in X:
            P[p - h] = max(P[p - h], P[p] + X[p - h])
    reverse, best = {}, 0
    for p, h in X.items():
        reverse[p + h] = min(reverse[p + h], p) if p + h in reverse else p
    for p, h in reversed(list(X.items())):
        if p - h in reverse:
            best = max(best, P[p] + Q[reverse[p - h]])
    best = max(best, max(Q.values()), max(P.values()))
    return best

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        X = dict(sorted(tuple(int(p) for p in input().split(' ')) for _ in range(N)))
        print('Case #{0}: {1}'.format(i + 1, solve(X)))

run()
