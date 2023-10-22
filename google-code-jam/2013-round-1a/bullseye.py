#!/usr/bin/python3

def check(k, r, t):
    return k * (2 * k + 2 * r - 1) <= t

def run():
    N = int(input())
    for t in range(N):
        R, T = [int(x) for x in input().split()]
        low, high = 1, T
        while low + 1 != high:
            mid = int((low + high) / 2)
            if check(mid, R, T):
                low = mid
            else:
                high = mid
        print("Case #{0}: {1}".format(t + 1, int(low)))

run()
