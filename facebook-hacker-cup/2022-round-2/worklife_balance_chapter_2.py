#!/usr/bin/python3

class Fenwick:
    def __init__(self, n):
        self.data = [0] * (n + 1)

    def count(self, index):
        out = 0
        while index > 0:
            out += self.data[index]
            index -= index & (-index)
        return out

    def update(self, index, value):
        while index < len(self.data):
            self.data[index] += value
            index += index & (-index)

def add(F, index, value, N):
    F[value].update(index, 1 if value == 1 else index)
    F[-value].update(N + 1 - index, 1 if value == 1 else N + 1 - index)

def subtract(F, index, value, N):
    F[value].update(index, -1 if value == 1 else -index)
    F[-value].update(N + 1 - index, -1 if value == 1 else index - N - 1)

def binary_search(low, high, test):
    while low + 1 < high:
        mid = (low + high) // 2
        low, high = (low, mid) if test(mid) else (mid, high)
    return high

def swap(F1, F2, Z, N):
    L = F1.count(Z)
    R = N - Z - (F1.count(N) - L)
    D = (N - Z + R) - (2 * Z - L)
    if D == 0:
        return 0
    if D < 0:
        D, L, R = -D, R, L
    twos = min(R, L, D // 2)
    if twos < D // 2:
        return -1
    s = binary_search(-1, Z - 1, lambda x: F1.count(x + 1) > L - twos)
    threshold = Z - F1.count(s + 1)
    t = binary_search(s, N, lambda x: x - F1.count(x) > threshold)
    return F2.count(t) - F2.count(s) - (s + 1 + Z) * (Z - s) // 2

def solve(A, U, N):
    F = {v: Fenwick(N) for v in [-2, -1, 1, 2]}
    for i, v in enumerate(A, start = 1):
        add(F, i, v, N)
    out, total = 0, sum(A)
    for x, y, z in U:
        subtract(F, x, A[x - 1], N)
        add(F, x, y, N)
        A[x - 1], total = y, total + y - A[x - 1]
        if total % 2 == 0:
            if 2 * z - F[1].count(z) <= total // 2:
                out += swap(F[1], F[2], z, N)
            else:
                out += swap(F[-1], F[-2], N - z, N)
        else:
            out -= 1
    return out

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        A = [int(x) for x in input().split()]
        U = [tuple(int(x) for x in input().split()) for _ in range(M)]
        print(f'Case #{i + 1}: {solve(A, U, N)}')

run()
