#!/usr/bin/python

def solve(A, r, c, h, v):
    total = sum(sum(1 for c in B if c == '@') for B in A)
    if total == 0:
        return 'POSSIBLE'
    if total % (v * h) > 0:
        return 'IMPOSSIBLE'

    R, count = [0] + [-1] * h, 0
    for i in range(r):
        count += sum(1 for j in range(c) if A[i][j] == '@')
        if (count * h) % total == 0:
            R[int((count * h) / total)] = i + 1
    for i in range(h):
        if R[i] == -1:
            return 'IMPOSSIBLE'

    C, count = [0] + [-1] * v, 0
    for i in range(c):
        count += sum(1 for j in range(r) if A[j][i] == '@')
        if (count * v) % total == 0:
            C[int((count * v) / total)] = i + 1
    for i in range(v):
        if C[i] == -1:
            return 'IMPOSSIBLE'

    for i in range(h):
        for j in range(v):
            if sum(sum(1 for k in range(R[i], R[i + 1]) if A[k][l] == '@')
                   for l in range(C[j], C[j + 1])) != total / (v * h):
                return 'IMPOSSIBLE'
    return 'POSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        R, C, H, V = [int(x) for x in input().split()]
        A = [input() for _ in range(R)]
        print('Case #{0}: {1}'.format(i + 1, solve(A, R, C, H + 1, V + 1)))

run()
