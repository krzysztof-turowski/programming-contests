#!/usr/bin/python3

class Node:
    def __init__(self):
        self.children = {}

    def insert(self, path):
        if len(path) == 0:
            return
        if path[0] not in self.children:
            self.children[path[0]] = Node()
        self.children[path[0]].insert(path[1:])

    def count(self):
        return 1 + sum(v.count() for v in self.children.values())

def solve(existing, new):
    T = Node()
    for word in existing:
        T.insert(word.split('/')[1:])
    previous = T.count()
    for word in new:
        T.insert(word.split('/')[1:])
    return T.count() - previous

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        existing = [input() for _ in range(N)]
        new = [input() for _ in range(M)]
        print('Case #{0}: {1}'.format(i + 1, solve(existing, new)))

run()
