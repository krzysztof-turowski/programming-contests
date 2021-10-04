#!/usr/bin/python3

def push_up(B, R, C, K):
    down = [[int(B[i][j] == 'X') for j in range(C)] for i in range(R)]
    for i in range(1, R):
        for j in range(C):
            down[i][j] += down[i - 1][j]
    return min(
        i + 1 - K + sum(B[i][j] == 'X' or down[i][j] >= K for j in range(C))
        for i in range(K - 1, R))

def solve(B, R, C, K):
    B.append('.' * C)
    out = push_up(B, R + 1, C, K)
    for i in range(R // 2):
        B[i], B[R - i - 1] = B[R - i - 1], B[i]
    return min(out, push_up(B, R + 1, C, R - K + 1))

def run():
    T = int(input())
    for i in range(T):
        R, C, K = (int(x) for x in input().split())
        B = [input().strip() for _ in range(R)]
        print('Case #{0}: {1}'.format(i + 1, solve(B, R, C, K)))

run()
