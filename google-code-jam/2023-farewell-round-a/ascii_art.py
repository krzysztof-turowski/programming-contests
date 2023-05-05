#!/usr/bin/python

import itertools

def solve(N):
    for i, r in zip(itertools.count(), itertools.accumulate(itertools.count())):
        if N <= r * 26:
            return chr(ord('Z') - (r * 26 - N) // i)
    raise StopIteration

def run():
    T = int(input())
    for i in range(T):
        print(f'Case #{i + 1}: {solve(int(input()))}')

run()
