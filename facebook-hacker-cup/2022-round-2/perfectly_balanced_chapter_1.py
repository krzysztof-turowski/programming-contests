#!/usr/bin/python

import collections
import copy

def subtract(A, B):
    return {k: v - B[k] for k, v in A.items()}

def compare(A, B):
    return sum(abs(A.get(k, 0) - B.get(k, 0)) for k in A.keys() | B.keys()) <= 1

def solve(S, query):
    D = [collections.defaultdict(int) for _ in range(len(S) + 1)]
    for i, s in enumerate(S, start = 1):
        D[i] = copy.deepcopy(D[i - 1])
        D[i][s] += 1
    out = 0
    for l, r in query:
        if (l + r) % 2 != 0:
            continue
        m = (l + r) // 2
        if compare(subtract(D[m - 1], D[l - 1]), subtract(D[r], D[m - 1])):
            out += 1
        elif compare(subtract(D[m], D[l - 1]), subtract(D[r], D[m])):
            out += 1
    return out

def run():
    T = int(input())
    for t in range(T):
        S = input().strip()
        Q = int(input())
        query = [tuple(int(x) for x in input().split()) for _ in range(Q)]
        print(f'Case #{t + 1}: {solve(S, query)}')

run()
