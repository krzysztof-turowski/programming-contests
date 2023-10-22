#!/usr/bin/python3

def apply(S, b):
    for i in range(b - 1, len(S), b):
        S[i] = '1' if S[i] == '0' else '0'

def solve(S, B):
    S0, A = S, set()
    for i, s in enumerate(S0, start = 1):
        if s == '1':
            apply(S0, i)
            A.add(i)
    out = 0
    for b in B:
        if b in A:
            A.remove(b)
        else:
            A.add(b)
        out += len(A)
    return out

def run():
    T = int(input())
    for i in range(T):
        _, S = input(), list(input().strip())
        Q = int(input())
        B = [int(input()) for _ in range(Q)]
        print(f'Case #{i + 1}: {solve(S, B)}')

run()
