#!/usr/bin/python

def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


def solve(L):
    S = {abs(x - y) for x in L for y in L if x != y}
    T = min(S)
    for s in S:
        T = gcd(T, s)
    return T - (L[0] % T) if L[0] % T != 0 else 0

def run():
    T = int(input())
    for i in range(T):
        L = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(L[1:])))

run()
