#!/usr/bin/python

def solve(X, V, K, B, T):
    opt = [(B - x) / v for x, v in zip(X, V)]
    A = list(a for a in opt)
    for i in range(len(A) - 2, -1, -1):
        A[i] = max(A[i], A[i + 1])
    if sum(1 if a <= T else 0 for a in opt) >= K:
        out, index, Q, passed = 0, len(X) - 1, 0, 0
        while passed < K:
            if opt[index] > T:
                Q += 1
            else:
                if A[index] > T:
                    out += Q
                passed += 1
            index -= 1
        return out
    return 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        _, K, B, T = (int(x) for x in input().split())
        X = [int(x) for x in input().split()]
        V = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(X, V, K, B, T)))

run()
