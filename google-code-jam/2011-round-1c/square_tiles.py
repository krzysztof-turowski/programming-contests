#!/usr/bin/python

def check(r, c, A):
    return (A[r][c] == '#' and A[r][c + 1] == '#' and A[r + 1][c] == '#'
            and A[r + 1][c + 1] == '#')

def solve(R, C, A):
    for r in range(R - 1):
        for c in range(C - 1):
            if A[r][c] == '#':
                if not check(r, c, A):
                    return 'Impossible'
                A[r][c], A[r][c + 1] = '/', '\\'
                A[r + 1][c], A[r + 1][c + 1] = '\\', '/'
    for r in range(R):
        if A[r][C - 1] == '#':
            return 'Impossible'
    for c in range(C):
        if A[R - 1][c] == '#':
            return 'Impossible'
    return '\n'.join(''.join(a) for a in A)

def run():
    T = int(input())
    for i in range(T):
        R, C = (int(x) for x in input().split())
        A = [list(input()) for _ in range(R)]
        print('Case #{0}:\n{1}'.format(i + 1, solve(R, C, A)))

run()
