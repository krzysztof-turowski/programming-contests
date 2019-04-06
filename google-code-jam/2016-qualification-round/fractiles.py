#!/usr/bin/python

import math
import itertools
import functools

def solve(K, C, S):
    return (
        ' '.join([str(1 + functools.reduce(lambda x, y: x * K + y, L))
                  for L in itertools.zip_longest(*[iter(range(K))] * C, fillvalue = 0)])
        if math.ceil(K / C) <= S else "IMPOSSIBLE")

def run():
    T = int(input())
    for i in range(T):
        K, C, S = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(K, C, S)))

run()
