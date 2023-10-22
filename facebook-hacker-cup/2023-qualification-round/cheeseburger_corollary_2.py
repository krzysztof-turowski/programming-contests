#!/usr/bin/python3

def solve(A, B, C):
    return max(0, max(2 * ((C - A * s) // B) + (s if s > 0 else -1) for s in (0, 1, 2, C // A)))

def run():
    T = int(input())
    for i in range(T):
        A, B, C = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(A, B, C)}')

run()
