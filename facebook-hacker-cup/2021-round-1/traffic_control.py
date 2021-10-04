#!/usr/bin/python

def solve(N, M, A, B):
    if min(A, B) < N + M - 1:
        return 'Impossible'
    C = [[1] * M for _ in range(N)]
    C[0][0], C[N - 1][0] = A - (N + M - 2), B - (N + M - 2)
    return 'Possible\n' + '\n'.join(' '.join(str(c) for c in row) for row in C)

def run():
    T = int(input())
    for i in range(T):
        N, M, A, B = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, M, A, B)))

run()
