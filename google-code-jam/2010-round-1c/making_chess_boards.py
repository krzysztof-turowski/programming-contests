#!/usr/bin/python

import collections

D = {
    '0': '0000', '1': '0001', '2': '0010', '3': '0011', '4': '0100',
    '5': '0101', '6': '0110', '7': '0111', '8': '1000', '9': '1001',
    'A': '1010', 'B': '1011', 'C': '1100', 'D': '1101', 'E': '1110',
    'F': '1111'
}

def disable(used, i, j, d):
    for k in range(i, i + d):
        for l in range(j, j + d):
            used[k][l] = True
    return used

def update(best, i, j, d):
    for k in range(i, i + d):
        for l in range(max(0, j - d + 1), j + d):
            best[k][l] = 0
    return best

def get(A, i, j):
    cell = ord(A[i][j // 4])
    value = cell + 10 - ord('A') if cell >= ord('A') else cell - ord('0')
    return (value & (1 << (3 - (j % 4)))) != 0

def solve(A, M, N):
    squares = [[
        (i < M - 1 and j < N - 1 and get(A, i, j) == get(A, i + 1, j + 1)
         and get(A, i, j) != get(A, i, j + 1)
         and get(A, i, j) != get(A, i + 1, j))
        for j in range(N)] for i in range(M)]
    best = [[0 for _ in range(N)] for _ in range(M)]
    used = [[False for _ in range(N)] for _ in range(M)]
    out = collections.defaultdict(int)
    for d in range(min(M, N), 0, -1):
        for i in range(M - 1, -1, -1):
            for j in range(N - 1, -1, -1):
                if used[i][j]:
                    best[i][j] = 0
                elif squares[i][j]:
                    best[i][j] = 1 + min(
                        best[i + 1][j], best[i][j + 1], best[i + 1][j + 1])
                else:
                    best[i][j] = 1
        for i in range(M):
            for j in range(N):
                if best[i][j] >= d:
                    used = disable(used, i, j, d)
                    best = update(best, i, j, d)
                    out[d] += 1
    return '{}\n{}'.format(
        len(out), '\n'.join('{} {}'.format(d, v) for d, v in out.items()))

def run():
    T = int(input())
    for i in range(T):
        M, N = (int(x) for x in input().split())
        A = [input().strip() for _ in range(M)]
        # A = [''.join(D[c] for c in input().strip()) for _ in range(M)]
        print('Case #{0}: {1}'.format(i + 1, solve(A, M, N)))

run()
