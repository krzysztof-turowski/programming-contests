#!/usr/bin/python3

MOD = 10 ** 9 + 7
SIZE = 10 ** 6

def get_factorial(size):
    out = [1] * size
    for i in range(2, size):
        out[i] = (out[i - 1] * i) % MOD
    return out

def get_inverse_factorial(size, last):
    out = [1] * size
    out[-1] = pow(last, MOD - 2, MOD)
    for i in range(size - 1, 1, -1):
        out[i - 1] = (out[i] * i) % MOD
    return out

F = get_factorial(SIZE)
invF = get_inverse_factorial(SIZE, F[-1])

def catalan(n):
    return (F[2 * n] * invF[n] * invF[n] * pow(n + 1, MOD - 2, MOD)) % MOD

def binomial(n, k):
    return (F[n] * invF[n - k] * invF[k]) % MOD

def solve(M, K):
    coeff = catalan(K - 1) * pow(catalan(M - 1), MOD - 2, MOD)
    return coeff * binomial(M - 2, 2 * K - 2) * pow(2, M - 2 * K, MOD) % MOD

def run():
    T = int(input())
    for i in range(T):
        M, K = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(M, K)))

run()
