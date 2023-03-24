#!/usr/bin/python

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

def swap(L, R, D):
    fours = min(L[2], R[0], D // 4)
    D -= fours * 4
    twos = min(max(min(L[1], R[0] - fours), min(L[2] - fours, R[1])), D // 2)
    D -= twos * 2
    return fours + twos if D == 0 else -1

def solve(A, U):
    F = {v: Fenwick(len(A)) for v in [1, 2, 3]}
    for i, v in enumerate(A, start = 1):
        F[v].update(i, 1)
    out = 0
    for x, y, z in U:
        F[A[x - 1]].update(x, -1)
        F[y].update(x, 1)
        A[x - 1] = y
        half = {k: f.count(z) for k, f in F.items()}
        total = {k: f.count(len(A)) for k, f in F.items()}
        left = sum(k * v for k, v in half.items())
        right = sum(k * v for k, v in total.items()) - left
        if (left + right) % 2 == 0:
            L = tuple(v for v in half.values())
            R = tuple(total[k] - half[k] for k in total)
            if left > right:
                out += swap(L, R, left - right)
            elif right > left:
                out += swap(R, L, right - left)
        else:
            out -= 1
    return out

def run():
    T = int(input())
    for i in range(T):
        _, M = (int(x) for x in input().split())
        A = [int(x) for x in input().split()]
        U = [tuple(int(x) for x in input().split()) for _ in range(M)]
        print(f'Case #{i + 1}: {solve(A, U)}')

run()
