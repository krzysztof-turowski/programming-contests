#!/usr/bin/python3

def get_primes(n):
    primes, is_prime = [], [True] * n
    for i in range(2, n):
        if is_prime[i]:
            primes.append(i)
            for j in range(i * i, n, i):
                is_prime[j] = False
    return primes

MAX = 30000
PRIMES_MAX = 500
PRIMES = get_primes(PRIMES_MAX)

def factorize(n):
    out = [0] * PRIMES_MAX
    for i in PRIMES:
        v = 0
        while n % i == 0:
            n, v = n // i, v + 1
        if v > 0:
            out[i] = v
    if n > 1:
        return None
    return out

def check(P, S):
    if S is None:
        return False
    for p, s in zip(P, S):
        if p < s:
            return False
    return True

def solve(P, total):
    for out in range(total - 2, max(total - MAX, 1), -1):
        F = factorize(out)
        if check(P, F) and sum(p * v for p, v in enumerate(F)) == total - out:
            return out
    return 0

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        P, total = [0] * PRIMES_MAX, 0
        for _ in range(N):
            p, n = (int(x) for x in input().split())
            P[p], total = n, total + n * p
        print('Case #{0}: {1}'.format(i + 1, solve(P, total)))

run()
