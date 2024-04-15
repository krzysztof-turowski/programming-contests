#!/usr/bin/python3

import functools

MOD = 1000000007

@functools.cache
def binomial(a, b):
    if a < b:
        return 0
    if b in (0, a):
        return 1
    return binomial(a - 1, b) + binomial(a - 1, b - 1)

class TrieNode:
    def __init__(self):
        self.children, self.tries = {}, 0

def insert(root, w, L):
    node = root
    for c in w:
        if c not in node.children:
            node.children[c] = TrieNode()
            L.append(node.children[c])
        node = node.children[c]
    node.tries = 1

def count_splits(parent, children):
    DP = [0] + [1] * parent
    for i in range(1, parent + 1):
        for k in children:
            DP[i] = (DP[i] * binomial(i, k)) % MOD
        for k in range(1, i):
            DP[i] = (DP[i] - (DP[k] * binomial(i, k)) % MOD) % MOD
    return DP[parent]

def solve(S, N):
    T = TrieNode()
    L = [T]
    for w in S:
        insert(T, w, L)
    X, Y = 0, 1
    for node in L[::-1]:
        children = [v.tries for v in node.children.values()] + [node.tries]
        node.tries = min(sum(children), N)
        X, Y = X + node.tries, (Y * count_splits(node.tries, children)) % MOD
    return f'{X} {Y}'

def run():
    T = int(input())
    for i in range(T):
        M, N = (int(x) for x in input().split())
        S = [input().strip() for x in range(M)]
        print(f'Case #{i + 1}: {solve(S, N)}')

run()
