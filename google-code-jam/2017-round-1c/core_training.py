#!/usr/bin/python

def get_probability(P, K):
    out = [1.0]
    for p in P:
        left = [v * (1 - p) for v in out] + [0.0]
        right = [0.0] + [v * p for v in out]
        out = [u + v for u, v in zip(left, right)]
    return sum(out[K:])

def increment_probability(P, Q, U):
    for i in range(len(P) - 1, 0, -1):
        diff = min(U, (P[i - 1] - P[i]) * (len(P) - i))
        for j in range(i, len(P)):
            P[j] += diff / (len(P) - i)
        U -= diff
    for i, v in enumerate(Q):
        diff = min(1.0 - v, U)
        Q[i], U = Q[i] + diff, U - diff
    return P[1:] + Q

def solve(P, U, K):
    out, P = 0, list(sorted(P, reverse = True))
    for i, _ in enumerate(P, start = 1):
        Q = increment_probability([1.0] + P[:i], P[i:], U)
        value = get_probability(Q, K)
        out = max(out, value)
    return out

def run():
    T = int(input())
    for i in range(T):
        _, K = (int(x) for x in input().split())
        U = float(input())
        P = [float(x) for x in input().split()]
        print('Case #{0}: {1:.10f}'.format(i + 1, solve(P, U, K)))

run()
