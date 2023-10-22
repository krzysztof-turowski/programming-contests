#!/usr/bin/python3

def solve(M, A):
    def get_left(a):
        return a[:len(a) // 2]
    def get_right(a):
        return a[len(a) // 2:]
    if len(A) == 0:
        return 0
    out = (
        A[0][0]
        + solve(get_left(M), [get_left(a) for a in A[1:]])
        + solve(get_right(M), [get_right(a) for a in A[1:]]))
    if min(M) != 0:
        M_minus = [m - 1 for m in M]
        out = min(
            out,
            solve(get_left(M_minus), [get_left(a) for a in A[1:]])
            + solve(get_right(M_minus), [get_right(a) for a in A[1:]]))
    return out

def run():
    T = int(input())
    for i in range(T):
        P = int(input())
        M = [int(x) for x in input().split()]
        A = [[int(x) for x in input().split()] for _ in range(P)]
        print('Case #{0}: {1}'.format(i + 1, solve(M, A[::-1])))

run()
