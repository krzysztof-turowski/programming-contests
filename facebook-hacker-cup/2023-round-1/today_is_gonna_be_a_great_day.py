#!/usr/bin/python3

MAX = 1000000007

def convert(t):
    return (MAX - t[0], -t[1])

class SegmentTree:
    def __init__(self, l, r, A):
        self.left, self.right, self.lazy = l, r, False
        if l == r:
            self.children, self.minimum, self.maximum = [], (A[l], l), (A[r], -r)
            return
        mid = (self.left + self.right) // 2
        self.children = [SegmentTree(l, mid, A), SegmentTree(mid + 1, r, A)]
        self.minimum = min(child.minimum for child in self.children)
        self.maximum = max(child.maximum for child in self.children)

    def tag(self):
        self.minimum, self.maximum = convert(self.maximum), convert(self.minimum)
        self.lazy ^= True

    def push(self):
        if self.lazy:
            for child in self.children:
                child.tag()
            self.lazy = False

    def update(self, l, r):
        if l <= self.left and self.right <= r:
            self.tag()
            return
        self.push()
        mid = (self.left + self.right) // 2
        if l <= mid:
            self.children[0].update(l, min(mid, r))
        if r > mid:
            self.children[1].update(max(mid + 1, l), r)
        self.minimum = min(child.minimum for child in self.children)
        self.maximum = max(child.maximum for child in self.children)

def solve(A, LR):
    T, out = SegmentTree(0, len(A) - 1, A), 0
    for l, r in LR:
        T.update(l, r)
        out += 1 - T.maximum[1]
    return out

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = [int(x) for x in input().split()]
        Q = int(input())
        LR = [tuple(int(x) - 1 for x in input().split()) for _ in range(Q)]
        print(f'Case #{i + 1}: {solve(A, LR)}')

run()
