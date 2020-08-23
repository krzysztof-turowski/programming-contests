#!/usr/bin/python

import math

def check(L, R, N = 1):
    while max(L, R) >= N:
        if L >= R:
            L -= N
        else:
            R -= N
        N += 1
    return N - 1, L, R

def solve(L, R):
    N = 1 + int(math.sqrt(8 * abs(R - L) + 1) / 2 - 0.5)
    if L >= R:
        L -= N * (N - 1) // 2
    else:
        R -= N * (N - 1) // 2
    if R > L and R >= N:
        R, N = R - N, N + 1
    if L >= R:
        N2a = int(math.sqrt(4 * L + (N - 1) ** 2) / 2 - (N - 1) / 2)
        N2b = int(math.sqrt(4 * R + N ** 2) / 2 - N / 2)
        N2 = max(min(N2a, N2b) - 1, 0)
        L, R, N = L - N2 ** 2 - N2 * (N - 1), R - N2 ** 2 - N2 * N, N + 2 * N2
    return check(L, R, N)

def run():
    T = int(input())
    for i in range(T):
        L, R = (int(x) for x in input().split())
        print('Case #{0}: {1} {2} {3}'.format(i + 1, *solve(L, R)))

run()
