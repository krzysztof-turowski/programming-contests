#!/usr/bin/python

def check(R, B, X, T):
    V = sorted([max(0, min(M, (T - P) // S)) for (M, S, P) in X], reverse = True)
    return sum(V[:R]) >= B

def solve(R, B, X):
    low, high = 0, 10 ** 30
    while low < high - 1:
        mid = (low + high) // 2
        if check(R, B, X, mid):
            high = mid
        else:
            low = mid
    return high

def run():
    T = int(input())
    for t in range(T):
        R, B, C = (int(x) for x in input().split())
        X = [[int(x) for x in input().split()] for _ in range(C)]
        print('Case #{0}: {1}'.format(t + 1, solve(R, B, X)))

run()
