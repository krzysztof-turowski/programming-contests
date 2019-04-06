#!/usr/bin/python

def get_max_speed(K, S, D):
    return D * S / (D - K)

def run():
    T = int(input())
    for t in range(T):
        D, N = [int(x) for x in input().split()]
        out = 10 ** 18
        for _ in range(N):
            K, S = [int(x) for x in input().split()]
            out = min(get_max_speed(K, S, D), out)
        print("Case #{0}: {1:.7f}".format(t + 1, out))

run()
