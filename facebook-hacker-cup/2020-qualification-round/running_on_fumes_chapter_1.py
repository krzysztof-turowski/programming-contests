#!/usr/bin/python

import math

class Heap:
    def __init__(self, M):
        self.L, self.I = [None] * (M + 1), {}

    def _swap(self, a, b):
        self.I[self.L[a][1]], self.I[self.L[b][1]] = b, a
        self.L[a], self.L[b] = self.L[b], self.L[a]


    def _sift_up(self, a):
        parent = (a - 1) // 2
        while a > 0 and self.L[a] < self.L[parent]:
            self._swap(a, parent)
            a, parent = parent, (parent - 1) // 2

    def _sift_down(self, a):
        child = 2 * a + 1
        while child < len(self.I):
            if child + 1 < len(self.I) and self.L[child] > self.L[child + 1]:
                child += 1
            if self.L[child] < self.L[a]:
                self._swap(a, child)
                a, child = child, 2 * child + 1
            else:
                break

    def get_cheapest(self):
        if len(self.I) == 0:
            return -1
        return self.L[0][0]

    def add_to_queue(self, index, cost):
        self.L[len(self.I)] = (cost, index)
        self.I[index] = len(self.I)
        self._sift_up(self.I[index])

    def remove(self, index):
        if index not in self.I:
            return
        position = self.I[index]
        self.L[position] = (-math.inf, self.L[position][1])
        self._sift_up(position)
        self._swap(0, len(self.I) - 1)
        del self.I[self.L[len(self.I) - 1][1]]
        self._sift_down(0)

def solve(C, M):
    cost, Q = [None] * len(C), Heap(M)
    cost[0] = 0
    Q.add_to_queue(0, 0)
    for i, c in enumerate(C[1:], 1):
        if c != 0 and Q.get_cheapest() >= 0:
            cost[i] = Q.get_cheapest() + c
            Q.add_to_queue(i, cost[i])
        else:
            cost[i] = -1
        Q.remove(i - M)
    return min((c for c in cost[-M - 1:] if c != -1), default = -1)

def naive(C, M):
    cost = [None] * len(C)
    cost[0] = 0
    for i, c in enumerate(C[1:], 1):
        v = min((c for c in cost[max(0, i - M):i] if c != -1), default = -1)
        if c != 0 and v >= 0:
            cost[i] = v + c
        else:
            cost[i] = -1
    return min((c for c in cost[-M - 1:] if c != -1), default = -1)

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        C = [int(input()) for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(C, M)))

run()
