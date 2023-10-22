#!/usr/bin/python3

def solve(A):
    out = 0
    while A:
        _, index = min((v, i) for i, v in enumerate(A))
        out += min(index, len(A) - 1 - index)
        A = A[:index] + A[index + 1:]
    return out

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        A = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(A)))

run()
