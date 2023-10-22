#!/usr/bin/python3

import decimal
import functools

@functools.lru_cache(maxsize = 1)
def generate():
    BIN, MAX = {(0, 0): 1}, 400
    for a in range(1, MAX + 1):
        BIN[(a, 0)], BIN[(a, a)] = decimal.Decimal(1), decimal.Decimal(1)
        for b in range(1, a):
            BIN[(a, b)] = decimal.Decimal(
                BIN[(a - 1, b)] + BIN[(a - 1, b - 1)])
    for a in range(MAX + 1):
        for b in range(a + 1, MAX + 1):
            BIN[(a, b)] = decimal.Decimal(0)
    return BIN

def solve(C, N):
    BIN = generate()
    return BIN[(C, N)] * sum(
        (-1 if j % 2 == 0 else 1) * BIN[(C, j)] / (
            BIN[(C, N)] - BIN[(C - j, N)])
        for j in range(1, C + 1))

def run():
    T = int(input())
    for i in range(T):
        C, N = (int(x) for x in input().split())
        print('Case #{0}: {1:.6f}'.format(i + 1, solve(C, N)))

run()
