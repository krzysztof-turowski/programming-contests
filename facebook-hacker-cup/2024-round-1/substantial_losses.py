#!/usr/bin/python3

MOD = 998244353

def solve(W, G, L):
    return ((W - G) * (2 * L + 1)) % MOD

def run():
    T = int(input())
    for i in range(T):
        W, G, L = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(W, G, L)}')

run()
