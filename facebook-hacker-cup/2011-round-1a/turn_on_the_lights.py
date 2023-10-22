#!/usr/bin/python3

import copy
import math

def count_ones(a):
    out = 0
    while a > 0:
        if a % 2 == 1:
            out += 1
        a //= 2
    return out

MAX = 2 ** 18
ONES = {i: count_ones(i) for i in range(MAX)}

def solve(A, R, C):
    row = 2 ** C - 1
    def press(B, index, mask):
        B[index] ^= mask ^ ((mask << 1) & row) ^ (mask >> 1)
        if index > 0:
            B[index - 1] ^= mask
        if index < R - 1:
            B[index + 1] ^= mask

    out = math.inf
    for i in range(2 ** C):
        B, value = copy.deepcopy(A), ONES[i]
        press(B, 0, i)
        for j, _ in enumerate(B[:-1]):
            value += ONES[B[j]]
            press(B, j + 1, B[j])
            if value >= out:
                break
        if B[-1] == 0:
            out = min(out, value)
    return out if out != math.inf else -1

def run():
    T = int(input())
    for i in range(T):
        R, C = (int(x) for x in input().split())
        A = [sum(2 ** i * (x == '.') for i, x in enumerate(input()))
             for _ in range(R)]
        print('Case #{0}: {1}'.format(i + 1, solve(A, R, C)))

run()
