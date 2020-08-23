#!/usr/bin/python

import math

def solve(L, N):
    length = N if len(L) == 1 else math.ceil(
        math.log((N + 1) * (len(L) - 1) + 1, len(L)) - 1)
    index = 0 if len(L) == 1 else N - (len(L) ** length - 1) // (len(L) - 1)
    word = []
    for _ in range(length):
        word.append(index % len(L))
        index //= len(L)
    return ''.join(L[i] for i in word[::-1])

def run():
    T = int(input())
    for i in range(T):
        L, N = input().split()
        print('Case #{0}: {1}'.format(i + 1, solve(L, int(N))))

run()
