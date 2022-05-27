#!/usr/bin/python

class Node:
    def __init__(self, value, parent):
        self.value, self.parent = value, (parent >= 0)
        self.children = []
        self.best, self.other = self.value, 0

    def set_value(self):
        best = min(v.best for v in self.children)
        self.other = sum(v.best + v.other for v in self.children) - best
        self.best = max(best, self.value)

    def get_value(self):
        if self.children:
            self.set_value()
        return self.best + self.other if not self.parent else 0

def solve(F, P):
    G = [Node(f, p) for f, p in zip(F, P)]
    for i, p in enumerate(P):
        if p >= 0:
            G[p].children.append(G[i])
    return sum(v.get_value() for v in G[::-1])

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        F = [int(x) for x in input().split()]
        P = [int(x) - 1 for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(F, P)))

run()
