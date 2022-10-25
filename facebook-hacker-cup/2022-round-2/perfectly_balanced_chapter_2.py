#!/usr/bin/python

import collections
import hashlib

MOD = 2 ** 89 - 1

def H(k):
    return int(hashlib.sha1(k.to_bytes(88, byteorder = 'big')).hexdigest(), 16) % MOD

class SegmentTree:
    def __init__(self, S):
        self.size = len(S)
        if len(S) == 1:
            self.left, self.right = None, None
            self.value = H(S[0])
        else:
            mid = len(S) // 2
            self.left, self.right = SegmentTree(S[:mid]), SegmentTree(S[mid:])
            self.value = (self.left.value + self.right.value) % MOD

    def update(self, index, s):
        if self.left is None:
            self.value = H(s)
            return
        mid = self.size // 2
        if index < mid:
            previous = self.left.value
            self.left.update(index, s)
            self.value = (self.value - previous + self.left.value) % MOD
        else:
            previous = self.right.value
            self.right.update(index - mid, s)
            self.value = (self.value - previous + self.right.value) % MOD

    def query(self, l, r):
        if l == 0 and r == self.size - 1:
            return self.value
        mid = self.size // 2
        left = self.left.query(l, min(r, mid - 1)) if l < mid else 0
        right = self.right.query(max(0, l - mid), r - mid) if r >= mid else 0
        return (left + right) % MOD

def solve(S, query):
    root = SegmentTree(S)
    R = collections.defaultdict(int)
    for s in S:
        R[H(s)] += 1
    out = 0
    for v, l, r in query:
        if v == 1:
            R[H(S[l - 1])] -= 1
            root.update(l - 1, r)
            S[l - 1] = r
            R[H(r)] += 1
        else:
            if (l + r) % 2 != 0:
                continue
            if l == r:
                out += 1
                continue
            m = (l + r) // 2
            if R[(MOD + root.query(l - 1, m - 1) - root.query(m, r - 1)) % MOD] > 0:
                out += 1
            elif R[(MOD + root.query(m - 1, r - 1) - root.query(l - 1, m - 2)) % MOD] > 0:
                out += 1
    return out

def run():
    T = int(input())
    for t in range(T):
        _ = input()
        S = [int(x) for x in input().split()]
        Q = int(input())
        query = [tuple(int(x) for x in input().split()) for _ in range(Q)]
        print(f'Case #{t + 1}: {solve(S, query)}')

run()
