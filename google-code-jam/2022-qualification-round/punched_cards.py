#!/usr/bin/python

import copy

def solve(R, C):
    odd = ['+'] + (['-', '+'] * C)
    even = ['|'] + (['.', '|'] * C)
    B = [odd, even] * R + [odd]
    B[0], B[1] = copy.deepcopy(B[0]), copy.deepcopy(B[1])
    B[0][0], B[0][1], B[1][0] = '.', '.', '.'
    return '\n'.join(''.join(b) for b in B)

def run():
    T = int(input())
    for i in range(T):
        R, C = (int(x) for x in input().split())
        print('Case #{0}:\n{1}'.format(i + 1, solve(R, C)))

run()
