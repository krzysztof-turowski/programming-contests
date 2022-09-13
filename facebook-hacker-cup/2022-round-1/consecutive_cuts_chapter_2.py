#!/usr/bin/python

def strong_prefix_suffix(w, m):
    sB, t = [-1] + [0] * m, -1
    for i in range(1, m + 1):
        while t >= 0 and w[t + 1] != w[i]:
            t = sB[t]
            t = t + 1
        if i == m or w[t + 1] != w[i + 1]:
            sB[i] = t
        else:
            sB[i] = sB[t]
    return sB

def knuth_morris_pratt(t, w, n, m):
    sB = strong_prefix_suffix(w, m)
    i, j = 1, 0
    while i <= n - m + 1:
        while j < m and t[i + j] == w[j + 1]:
            j = j + 1
        if j == m:
            yield i
        i, j = i + j - sB[j], max(0, sB[j])

def solve(A, B, K):
    if K == 0:
        return 'YES' if all(a == b for a, b in zip(A, B)) else 'NO'
    if len(A) == 2 and A[0] != A[1]:
        return 'YES' if (K % 2) != (A[0] == B[0]) else 'NO'
    V = set(knuth_morris_pratt([-1] + A + A, [-1] + B, 2 * len(A), len(B)))
    if K == 1 and len(V) == 2 and min(V) == 1:
        return 'NO'
    return 'YES' if len(V) > 0 else 'NO'

def run():
    T = int(input())
    for t in range(T):
        _, K = (int(x) for x in input().split())
        A = [int(x) for x in input().split()]
        B = [int(x) for x in input().split()]
        print(f'Case #{t + 1}: {solve(A, B, K)}')

run()
