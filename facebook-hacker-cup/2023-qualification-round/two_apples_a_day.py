#!/usr/bin/python3

def check_simple(A, S, N):
    for a, b in zip(A[:N - 1], A[-1::-1]):
        if a + b != S:
            return False
    return True

def check_hard(A, S, N):
    missing, left, right = None, 0, 0
    for i in range(N):
        if i + left == N - 1 and i + right == N - 1:
            missing = A[N - 1]
        elif A[i + left] + A[-i - 1 - right] != S:
            if missing is not None:
                return None
            if A[i + left] + A[-i - 1 - right] < S:
                missing, right = A[i + left], -1
            else:
                missing, left = A[-i - 1 - right], -1
    return missing

def solve(A):
    N = (len(A) + 1) // 2
    if N == 1:
        return 1
    out = set()
    if A[0] + A[-2] - A[-1] > 0 and check_simple(A[:-1], A[0] + A[-2], N):
        out.add(A[0] + A[-2] - A[-1])
    if A[1] + A[-1] - A[0] > 0 and check_simple(A[1:], A[1] + A[-1], N):
        out.add(A[1] + A[-1] - A[0])
    value = check_hard(A, A[0] + A[-1], N)
    if value and A[0] + A[-1] - value > 0:
        out.add(A[0] + A[-1] - value)
    return min(out) if len(out) > 0 else -1

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = list(sorted([int(x) for x in input().split()]))
        print(f'Case #{i + 1}: {solve(A)}')

run()
