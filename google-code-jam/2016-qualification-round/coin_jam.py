#!/usr/bin/python

import random

PRIMES = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }

def generate(N):
    out, r = ['1'] * N, random.getrandbits(N - 2)
    for i in range(1, N - 1):
        out[i] = '1' if r % 2 == 1 else '0'
        r //= 2
    return int(''.join(out))

def test_prime(value):
    for p in PRIMES:
        if value % p == 0 and value // p > 1:
            return p
    return None

def check(value, N):
    D = []
    for d in range(2, 11):
        base_d = sum(int(v) * (d ** (N - 1 - i)) for i, v in enumerate(list(str(value))))
        divisor = test_prime(base_d)
        if divisor is None:
            return False, None
        D.append(divisor)
    return True, D

def solve(N, J):
    L = {}
    while len(L) < J:
        value = generate(N)
        if value in L:
            continue
        jamcoin, divisors = check(value, N)
        if jamcoin:
            L[value] = divisors
    return [' '.join(str(x) for x in [k] + v) for k, v in L.items()]

def run():
    _ = input()
    N, J = [int(x) for x in input().split()]
    print("Case #{0}:\n{1}".format(1, '\n'.join(solve(N, J))))

run()
