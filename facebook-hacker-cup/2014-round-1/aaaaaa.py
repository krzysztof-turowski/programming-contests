#!/usr/bin/python3

import copy
import queue

def reverse(A):
    A = A[::-1]
    for i, row in enumerate(A):
        A[i] = row[::-1]
    return A

def find_ends(N, M, A):
    out = []
    for i in range(N):
        for j in range(M):
            if (A[i][j] == '.' and (i + 1 == N or A[i + 1][j] == '#')
                    and (j + 1 == M or A[i][j + 1] == '#')):
                out.append((N - 1 - i, M - 1 - j))
    return out

def cost(start, end, A):
    Q, out = queue.PriorityQueue(), 0
    for p in start:
        Q.put((p, -1))
    while not Q.empty():
        p, distance = Q.get()
        if A[p[0]][p[1]] != '.':
            continue
        if p[0] < end[0]:
            Q.put(((p[0] + 1, p[1]), distance - 1))
        if p[1] < end[1]:
            Q.put(((p[0], p[1] + 1), distance - 1))
        A[p[0]][p[1]], out = -distance, max(out, -distance)
    return A, out

def solve(N, M, A):
    forward, out = cost([(0, 0)], (N - 1, M - 1), copy.deepcopy(A))
    ends = sorted(find_ends(N, M, A), key = lambda p: p[0] + p[1])
    backward = reverse(cost(ends, (N - 1, M - 1), reverse(A))[0])
    for i in range(N):
        for j in range(M):
            if forward[i][j] == '#' or forward[i][j] == '.':
                continue
            if i + 1 < N and forward[i + 1][j] != '#':
                for k in range(j - 1, -1, -1):
                    if forward[i + 1][k] == '#':
                        break
                    back = (backward[i + 2][k]
                            if i + 2 < N and backward[i + 2][k] != '#' else 0)
                    out = max(out, forward[i][j] + (j - k + 1) + back)
            if j + 1 < M and forward[i][j + 1] != '#':
                for k in range(i - 1, -1, -1):
                    if forward[k][j + 1] == '#':
                        break
                    back = (backward[k][j + 2]
                            if j + 2 < M and backward[k][j + 2] != '#' else 0)
                    out = max(out, forward[i][j] + (i - k + 1) + back)
    return out

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        A = [list(input().strip()) for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(N, M, A)))

run()
