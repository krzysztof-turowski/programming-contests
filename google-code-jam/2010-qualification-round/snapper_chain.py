#!/usr/bin/python3

def solve(N, K):
    return 'ON' if ((2 ** N - 1) & K) == 2 ** N - 1 else 'OFF'

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, K)))

run()
