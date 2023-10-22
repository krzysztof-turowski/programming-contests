#!/usr/bin/python3

def generate(V, N, VA):
    for _ in range(len(V), N):
        V.append((VA[0] * V[-2] + VA[1] * V[-1] + VA[2]) % VA[3])
    return V

def read_and_generate(N):
    X = [int(x) for x in input().split()]
    XA = tuple(int(x) for x in input().split())
    return generate(X, N, XA)

def solve(S, X, Y):
    min_add = sum(max(0, x - s) for s, x in zip(S, X))
    max_add = sum(max(0, (x + y) - s) for s, x, y in zip(S, X, Y))
    min_remove = sum(max(0, s - (x + y)) for s, x, y in zip(S, X, Y))
    max_remove = sum(max(0, s - x) for s, x in zip(S, X))
    if min_add > max_remove or max_add < min_remove:
        return -1
    return max(min_add, min_remove)

def run():
    T = int(input())
    for t in range(T):
        N, _ = (int(x) for x in input().split())
        S = read_and_generate(N)
        X = read_and_generate(N)
        Y = read_and_generate(N)
        print(f'Case #{t + 1}: {solve(S, X, Y)}')

run()
