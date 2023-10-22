#!/usr/bin/python3

import math

def get_sequences(A, K):
    out, size, previous = {}, 0, math.inf
    for a in A:
        if abs(previous - a) >= K:
            previous, size = a, size + 1
        out[a] = size
    return out

def solve(A, K):
    S = list(sorted(set(A)))
    L, R = get_sequences(S, K), get_sequences(S[::-1], K)
    return ' '.join(str(L[a] + R[a] - 1) for a in A)

def run():
    T = int(input())
    for i in range(T):
        _, K = (int(x) for x in input().split())
        A = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(A, K)}')

run()
