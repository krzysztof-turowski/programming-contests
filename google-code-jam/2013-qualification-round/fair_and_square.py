#!/usr/bin/python

from bisect import bisect_left
from bisect import bisect_right

def check(n):
    n = n * n
    return str(n) == str(n)[::-1]

def compute(L, n):
    out = []
    while n > 2:
        n = n - 2
        X = [x for x in L if check(int(x + x[-2::-1]))]
        Y = [x for x in L if check(int(x + x[::-1]))]
        L = [x + str(y) for x in set(X + Y) for y in range(3)]
        out = out + sorted([int(x + x[-2::-1]) * int(x + x[-2::-1]) for x in X]
                           + [int(x + x[::-1]) * int(x + x[::-1]) for x in Y])
    return out

def run():
    L = compute([str(x) for x in range(1, 4)], 53)
    N = int(raw_input())
    for t in range(N):
        A, B = [int(x) for x in raw_input().split()]
        print "Case #{0}: {1}".format(t + 1, bisect_right(L, B) - bisect_left(L, A))

run()
