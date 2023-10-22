#!/usr/bin/python3

import math
import scipy.signal

def generate(A, N, P):
    out, a, b = [0] * P, A[0], A[1]
    out[A[0]] += 1
    out[A[1]] += 1
    for _ in range(N - 2):
        c = (a * A[2] + b * A[3] + A[4]) % P
        a, b, out[c] = b, c, out[c] + 1
    return out

def get_primes(P):
    for i in range(2, math.ceil(math.sqrt(P))):
        if P % i == 0:
            while P % i == 0:
                P //= i
            yield i
    if P > 1:
        yield P

def get_primitive_root(P):
    divisors = [(P - 1) // v for v in get_primes(P - 1)]
    for i in range(2, P):
        for d in divisors:
            if pow(i, d, P) == 1:
                break
        else:
            return i

def get_logarithms(P):
    out, g = {}, get_primitive_root(P)
    v = 1
    for i in range(P - 1):
        out[v], v = i, (v * g) % P
    return out

def map_to_logarithm(A, D, P):
    out = [0] * (P - 1)
    for i, a in enumerate(A[1:], start = 1):
        out[D[i]] = a
    return out

def solve(P, L, A, B):
    D = get_logarithms(P)
    V = list(scipy.signal.convolve(
        map_to_logarithm(A, D, P), map_to_logarithm(B, D, P)))
    V = [a + b for a, b in zip(V, V[P - 1:] + [0])]
    return (A[0] * sum(B) + B[0] * sum(A) - A[0] * B[0]
            + sum(V[D[i]] for i in range(1, L)))

def run():
    T = int(input())
    for i in range(T):
        P, L = (int(x) for x in input().split())
        N, *A = [int(x) for x in input().split()]
        M, *B = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(
            i + 1, solve(P, L, generate(A, N, P), generate(B, M, P))))

run()
