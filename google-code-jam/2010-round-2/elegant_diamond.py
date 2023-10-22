#!/usr/bin/python3

def transpose(L, N):
    out = [[] for _ in L]
    for row in L:
        for i, v in zip(range(N - len(row), N + len(row) - 1, 2), row):
            out[i].append(v)
    return out

def get_symmetries(R, N, extend):
    def is_symmetric(A):
        for a, b in zip(A, A[::-1]):
            if a != b:
                return False
        return True
    return {i for i in range(N) if i >= len(R) or is_symmetric(extend(R, i))}

def solve(L, N):
    def apply(S, f):
        return min(set.intersection(*(get_symmetries(row, N, f) for row in S)))
    left = lambda R, i: R[len(R) - i:][::-1] + R
    right = lambda R, i: R + R[:i][::-1]
    L_rev = transpose(L, N)
    horizontal_left, horizontal_right = apply(L, left), apply(L, right)
    vertical_left, vertical_right = apply(L_rev, left), apply(L_rev, right)
    size = min(horizontal_left, horizontal_right) + min(
        vertical_left, vertical_right)
    return (N + size) ** 2 - N ** 2

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        L = [[int(x) for x in input().strip().split()]
             for _ in range(2 * N - 1)]
        print('Case #{0}: {1}'.format(i + 1, solve(L, N)))

run()
