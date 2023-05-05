#!/usr/bin/python

def solve(X, M, R):
    out, previous, current = 0, -R - 1, 0
    for x in X:
        if current < x - R:
            return 'IMPOSSIBLE'
        if previous < x - R:
            current, previous, out = x + R, current, out + 1
        else:
            current = x + R
        if current >= M:
            return out
    return 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        M, R, _ = (int(x) for x in input().split())
        X = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(X, M, R)}')

run()
