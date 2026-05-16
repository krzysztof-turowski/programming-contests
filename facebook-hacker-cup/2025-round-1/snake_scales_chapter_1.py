#!/usr/bin/python3

def solve(A):
    return max(abs(a - b) for a, b in zip(A, A[1:])) if len(A) > 1 else 0

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(A)}')

run()
