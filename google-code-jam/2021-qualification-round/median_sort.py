#!/usr/bin/python3

import sys

def get_input(*A):
    print(' '.join(str(a) for a in A))
    sys.stdout.flush()
    return int(input().strip())

def order_three(a, b, c):
    median = get_input(a, b, c)
    if median == a:
        return [b, a, c]
    if median == b:
        return [a, b, c]
    return [a, c, b]

def insert(L, start, end, i):
    while start + 1 < end:
        assert end - start >= 3
        a, b = start + (end - start) // 3, start + 2 * (end - start) // 3
        median = get_input(L[a], i, L[b])
        if median == L[a]:
            end = a + 1 if a - start == 2 else a
        elif median == L[b]:
            start = b - 1 if end - b == 2 else b
        else:
            start, end = (a - 1, b) if b - a == 2 else (a, b)
    return L[:start + 1] + [i] + L[end:]

def solve(N):
    L = order_three(*range(1, 4))
    for i in range(4, N + 1):
        L = insert(L, -1, len(L), i)
    return get_input(*L)

def run():
    T, N, _ = (int(x) for x in input().split())
    for _ in range(T):
        if solve(N) == -1:
            return

run()
