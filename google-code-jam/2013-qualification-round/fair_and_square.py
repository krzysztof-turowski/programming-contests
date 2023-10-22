#!/usr/bin/python3

def bisect(L, v):
    low, high = -1, len(L)
    while low + 1 != high:
        mid = int((low + high) / 2)
        if L[mid] < v:
            low = mid
        else:
            high = mid
    return low

def check(n):
    return str(n * n) == str(n * n)[::-1]

def compute(L, n):
    out = []
    while n > 2:
        n = n - 2
        X = [x for x in L if check(int(x + x[-2::-1]))]
        Y = [x for x in L if check(int(x + x[::-1]))]
        L = [x + str(y) for x in set(X + Y) for y in range(3)]
        out = out + sorted([int(x + x[-2::-1]) * int(x + x[-2::-1]) for x in X]
                           + [int(x + x[::-1]) * int(x + x[::-1]) for x in Y])
    return out

def run():
    L = compute([str(x) for x in range(1, 4)], 53)
    N = int(input())
    for t in range(N):
        A, B = [int(x) for x in input().split()]
        print("Case #{0}: {1}".format(t + 1, bisect(L, B + 1) - bisect(L, A)))

run()
