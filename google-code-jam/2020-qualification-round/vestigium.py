#!/usr/bin/python

def solve(M, N):
    def get_repeated(A):
        row = sorted(A)
        return any(a == b for a, b in zip(row, row[1:]))
    trace = sum(M[i][i] for i in range(N))
    rows = sum(get_repeated(M[i]) for i in range(N))
    columns = sum(get_repeated([M[j][i] for j in range(N)]) for i in range(N))
    return trace, rows, columns


def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        M = [[int(x) for x in input().split()] for i in range(N)]
        print('Case #{0}: {1} {2} {3}'.format(i + 1, *solve(M, N)))

run()
