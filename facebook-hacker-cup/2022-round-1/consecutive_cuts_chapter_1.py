#!/usr/bin/python

def solve(A, B, K):
    if len(A) == 2:
        return 'YES' if (K % 2) != (A[0] == B[0]) else 'NO'
    if K == 1 and A[0] == B[0]:
        return 'NO'
    if K > 0:
        start = B.index(A[0])
        B = B[start:] + B[:start]
    return 'YES' if all(a == b for a, b in zip(A, B)) else 'NO'

def run():
    T = int(input())
    for t in range(T):
        _, K = (int(x) for x in input().split())
        A = [int(x) for x in input().split()]
        B = [int(x) for x in input().split()]
        print(f'Case #{t + 1}: {solve(A, B, K)}')

run()
