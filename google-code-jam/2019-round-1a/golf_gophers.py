#!/usr/bin/python

import sys

HOLES = 18

def get_input(v):
    return ' '.join([str(v)] * HOLES)

def extended_gcd(a, b):
    if a == 0:
        return (0, 1)
    y, x = extended_gcd(b % a, a)
    return (x - (b // a) * y, y)

def invert(a, m):
    x, _ = extended_gcd(a, m)
    return x % m

def chinese_remainder(P, L):
    product = 1
    for p in P:
        product *= p
    products = [product / p for p in P]
    inverse = [invert(x % p, p) for (x, p) in zip(products, P)]
    return int(sum(i * l * p for (i, l, p) in zip(inverse, L, products))) % product

def solve():
    P, L = [16, 9, 5, 7, 11, 13, 17], []
    for p in P:
        print(get_input(p))
        sys.stdout.flush()
        L.append(sum(int(x) for x in input().split()))
    return chinese_remainder(P, L)

def run():
    T, _, _ = [int(x) for x in input().split()]
    for _ in range(T):
        print('{0}'.format(solve()))
        sys.stdout.flush()
        if int(input()) == -1:
            return

run()
