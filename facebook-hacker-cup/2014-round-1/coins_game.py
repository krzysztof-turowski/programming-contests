#!/usr/bin/python3

def solve(N, K, C):
    if C <= (K // N) * N or K % N == 0:
        return C
    for i in range(1, N):
        if K % (N - i) < K // (N - i):
            return C + i
    return None

def run():
    T = int(input())
    for i in range(T):
        N, K, C = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, K, C)))

run()
