#!/usr/bin/python3

def test(A, h):
    I = [0] + [i for i, (a, b) in enumerate(zip(A, A[1:]), start=1) if abs(a - b) > h] + [len(A)]
    return all(min(A[start:end]) <= h for start, end in zip(I, I[1:]))

def solve(A):
    if len(A) == 1:
        return A[0]

    low, high = 0, max(A)
    while low + 1 < high:
        mid = (low + high) // 2
        if test(A, mid):
            high = mid
        else:
            low = mid
    return high

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(A)}')

run()
