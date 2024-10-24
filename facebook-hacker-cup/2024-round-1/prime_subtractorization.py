#!/usr/bin/python3

def get_primes(n):
    primes, is_prime = [], [True] * n
    for i in range(2, n):
        if is_prime[i]:
            primes.append(i)
            for j in range(i * i, n, i):
                is_prime[j] = False
    return primes

MAX = 10000000
PRIMES = get_primes(MAX)

def get_twin_prime(N):
    for p, q in zip(PRIMES, PRIMES[1:]):
        if q > N:
            break
        if p + 2 == q:
            yield p

def solve(N):
    return 1 + len(list(get_twin_prime(N))) if N >= 5 else 0

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        print(f'Case #{i + 1}: {solve(N)}')

run()
