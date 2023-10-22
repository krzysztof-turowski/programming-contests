#!/usr/bin/python3

import itertools

def solve(A):
    return 1 + len(A) + sum(a * (a - 1) // 2 for a in A) + sum(
        (a + 1) * (b + 1) for a, b in itertools.combinations(A, 2))

def run():
    T = int(input())
    for i in range(T):
        A = [int(x) for x in input().split()[1:]]
        print(f'Case #{i + 1}: {solve(A)}')

run()
