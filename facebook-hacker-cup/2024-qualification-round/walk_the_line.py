#!/usr/bin/python3

def solve(S, K):
    return 'YES' if max(2 * len(S) - 3, 1) * min(S) <= K else 'NO'

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        S = [int(input()) for _ in range(N)]
        print(f'Case #{i + 1}: {solve(S, K)}')

run()
