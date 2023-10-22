#!/usr/bin/python3

def get_probability(P, K):
    out = [1.0]
    for p in P:
        left = [v * (1 - p) for v in out] + [0.0]
        right = [0.0] + [v * p for v in out]
        out = [u + v for u, v in zip(left, right)]
    return out[K // 2]

def solve(P, K):
    return max(get_probability(P[:i] + P[len(P) - K + i:], K)
               for i in range(K + 1))

def run():
    T = int(input())
    for i in range(T):
        _, K = (int(x) for x in input().split())
        P = list(sorted(float(x) for x in input().split()))
        print('Case #{0}: {1:.10f}'.format(i + 1, solve(P, K)))

run()
