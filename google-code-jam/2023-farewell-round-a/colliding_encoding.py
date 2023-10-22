#!/usr/bin/python3

def solve(S):
    M = set(S)
    return 'NO' if len(M) == len(S) else 'YES'

def run():
    T = int(input())
    for i in range(T):
        D = {chr(k): v for k, v in zip(range(ord('A'), ord('Z') + 1), input().split())}
        N = int(input())
        S = [''.join(D[x] for x in input().strip()) for _ in range(N)]
        print(f'Case #{i + 1}: {solve(S)}')

run()
