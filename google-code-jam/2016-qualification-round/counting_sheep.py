#!/usr/bin/python

def solve(N):
    X, digits = 0, set()
    while len(digits) < 10:
        X += N
        digits.update(str(X))
    return X

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        print('Case #{0}: {1}'.format(i + 1, solve(N) if N > 0 else 'INSOMNIA'))

run()
