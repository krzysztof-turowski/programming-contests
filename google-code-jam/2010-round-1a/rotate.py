#!/usr/bin/python

def rotate(A, N):
    B = [['.'] * N for _ in range(N)]
    for i, row in enumerate(A):
        position = N - 1
        for c in row[::-1]:
            if c != '.':
                B[position][i], position = c, position - 1
    return B

def find(A, N, K, c):
    for i in range(N):
        index = 0
        for j in range(N):
            index = index + 1 if A[i][j] == c else 0
            if index == K:
                return True
        index = 0
        for j in range(N):
            index = index + 1 if A[j][i] == c else 0
            if index == K:
                return True
    for inv in range(2 * N):
        index = 0
        for i in range(N):
            if inv - i >= N or inv - i < 0:
                continue
            index = index + 1 if A[i][inv - i] == c else 0
            if index == K:
                return True
        index = 0
        for i in range(N):
            if i + inv - N >= N or i + inv - N < 0:
                continue
            index = index + 1 if A[i][inv + i - N] == c else 0
            if index == K:
                return True
    return False

def solve(A, N, K):
    A = rotate(A, N)
    red, blue = find(A, N, K, 'R'), find(A, N, K, 'B')
    return (('Both' if blue else 'Red') if red
            else ('Blue' if blue else 'Neither'))

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        A = [input() for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(A, N, K)))

run()
