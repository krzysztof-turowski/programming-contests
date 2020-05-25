#!/usr/bin/python

def solve(X, Y, M):
    for i, c in enumerate(M):
        if c == 'N':
            Y += 1
        elif c == 'S':
            Y -= 1
        elif c == 'E':
            X += 1
        else:
            X -= 1
        if abs(X) + abs(Y) <= i + 1:
            return str(i + 1)
    return 'IMPOSSIBLE'


def run():
    T = int(input())
    for i in range(T):
        X, Y, M = input().split()
        print('Case #{0}: {1}'.format(i + 1, solve(int(X), int(Y), M)))

run()
