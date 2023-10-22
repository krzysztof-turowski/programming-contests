#!/usr/bin/python3

def solve(S, D, K):
    return 'YES' if K + 1 <= 2 * (S + D) and K <= S + 2 * D else 'NO'

def run():
    T = int(input())
    for i in range(T):
        S, D, K = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(S, D, K)}')

run()
