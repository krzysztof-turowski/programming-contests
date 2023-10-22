#!/usr/bin/python3

import functools

@functools.lru_cache(maxsize = None)
def solve_recursive(V):
    L = [max(sum(V) - 1, 0)]
    if len(V) == 1:
        D = {(2,): 1}
    elif len(V) == 2:
        D = {(1, 1): 1, (3, 0): 2, (0, 3): 2}
    else:
        D = {(0, 2, 0): 1, (1, 0, 1): 1, (2, 1, 0): 2, (0, 1, 2): 2,
             (4, 0, 0): 3, (0, 0, 4): 3}
    for U, c in D.items():
        if all(v >= u for u, v in zip(U, V)):
            L.append(c + solve_recursive(tuple(v - u for u, v in zip(U, V))))
    return min(L)

def solve(G, P):
    D = {i: sum(1 if g % P == i else 0 for g in G) for i in range(1, P)}
    return len(G) - solve_recursive(tuple(D.values()))

def run():
    T = int(input())
    for i in range(T):
        _, P = (int(x) for x in input().split())
        G = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(G, P)))

run()
