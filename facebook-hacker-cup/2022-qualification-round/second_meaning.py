#!/usr/bin/python

import itertools

MAX = 9

def generate(N):
    return (''.join(s) for _, s in zip(
        range(N), itertools.product('.-', repeat = MAX)))

def solve(N, C):
    first = '-' if C[0] == '.' else '.'
    return '\n' + '\n'.join(first + s for s in generate(N - 1))

def run():
    T = int(input())
    for t in range(T):
        N, C = int(input()), input().strip()
        print(f'Case #{t + 1}: {solve(N, C)}')

run()
