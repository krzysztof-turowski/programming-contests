#!/usr/bin/python3

import collections

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

def counter(A, B, N):
    D = collections.defaultdict(int)
    for a in A + B:
        D[a] += 1
    for k, v in D.items():
        if v % 2 == 1:
            return set()
        D[k] = v // 2
    for a in A:
        D[a] -= 1
        if D[a] == 0:
            del D[a]
    out = set()
    if len(D) == 0:
        out.add(1)
        out.add(N + 1)
    for i in range(N):
        if A[i] != B[i]:
            D[B[i]] -= 1
            D[A[i]] += 1
            if D[B[i]] == 0:
                del D[B[i]]
            if D[A[i]] == 0:
                del D[A[i]]
        if len(D) == 0:
            out.add(i + 2)
            out.add(N + i + 2)
    return out

def palindrome(A, B, v, N):
    total = A + B + A + B + A
    left, right = total[v:v + N], total[v + N:v + 2 * N]
    return left == right[::-1]

def solve(A, B, N):
    C = ''.join('L' if a < b else ('G' if a > b else 'E') for a, b in zip(A + B, B + A))
    L_pattern, G_pattern = '#' + 'L' * (N // 2), '#' + 'G' * (N // 2)
    L_found = set(
        (v + 2 * N - 1) % (2 * N)
        for v in knuth_morris_pratt('#' + C + C, L_pattern, 3 * N, N // 2))
    G_found = set(
        (v + 2 * N - (N + 1) // 2 - 1) % (2 * N)
        for v in knuth_morris_pratt('#' + C + C, G_pattern, 3 * N, N // 2))
    for v in L_found & G_found:
        if palindrome(A, B, v, N):
            return v
    return -1

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        A = [int(x) for x in input().split()]
        B = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(A, B, N)}')

run()
