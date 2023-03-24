#!/usr/bin/python

import collections
import math

MOD = 1000000007

class Client:
    def __init__(self):
        self.A, self.B, self.X, self.Y = (int(x) for x in input().split())

def merge(A, B, K):
    return sorted(A[:K] + B[:K], reverse = True)[:K]

def solve(clients, K):
    events = sorted(
        ([(c.B, c.Y, 's', i) for i, c in enumerate(clients)]
         + [(c.A, c.X, 'b', i) for i, c in enumerate(clients)]),
        reverse = True)
    P = collections.defaultdict(list)
    day, V = math.inf, [0]
    for d, price, mode, index in events:
        if d != day:
            day, V = d, [0]
        if mode == 's':
            P[index] = [max(v - price, 0) for v in V]
        else:
            V = merge(V, [p + price for p in P[index]], K)
    out = [0]
    for p in P.values():
        out = merge(out, p, K)
    return sum(out) % MOD

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        clients = [Client() for _ in range(N)]
        print(f'Case #{i + 1}: {solve(clients, K)}')

run()
