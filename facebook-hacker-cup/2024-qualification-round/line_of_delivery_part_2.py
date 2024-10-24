#!/usr/bin/python3

import bisect
import random

MAX = 2 ** 32

class Node:
    def __init__(self, k):
        self.left = self.right = None
        self.key, self.priority, self.size, self.shift = k, random.randrange(MAX), 1, 0

def rotate_left(x):
    y = x.right
    x_shift, y_shift = x.shift, y.shift
    y.shift, y.key = min(x_shift, y_shift), y.key - (x_shift + y_shift - min(x_shift, y_shift))
    x.shift = x_shift - min(x_shift, y_shift)
    if y.right:
        y.right.shift += (x_shift + y_shift - min(x_shift, y_shift))
    if y.left:
        y.left.shift += y_shift
    y.size, x.size = x.size, x.size - 1 - (y.right.size if y.right else 0)
    y.left, x.right = x, y.left
    return y

def rotate_right(y):
    x = y.left
    x_shift, y_shift = x.shift, y.shift
    x.shift, x.key = min(x_shift, y_shift), x.key - (x_shift + y_shift - min(x_shift, y_shift))
    y.shift = y_shift - min(x_shift, y_shift)
    if x.left:
        x.left.shift += (x_shift + y_shift - min(x_shift, y_shift))
    if x.right:
        x.right.shift += x_shift
    x.size, y.size = y.size, y.size - 1 - (x.left.size if x.left else 0)
    x.right, y.left = y, x.right
    return x

def insert(root, k):
    if not root:
        return Node(k)
    root.size += 1
    left_size = (root.left.size if root.left else 0)
    if k >= root.key - root.shift - left_size:
        if root.left:
            root.left.shift += 1
        root.key -= 1
        root.right = insert(root.right, k + root.shift + left_size + 1)
        if root.right.priority > root.priority:
            root = rotate_left(root)
    else:
        root.left = insert(root.left, k + root.shift)
        if root.left.priority > root.priority:
            root = rotate_right(root)
    return root

def get_values(root, shift):
    if not root:
        return []
    left = get_values(root.left, shift + root.shift)
    right = get_values(root.right, shift + root.shift)
    return left + [root.key - shift - root.shift] + right

def solve(E, G):
    root = None
    for e in E:
        root = insert(root, e)
    E = get_values(root, 0)
    index = bisect.bisect(E, G)
    if index == len(E) or (index > 0 and G - E[index - 1] < E[index] - G):
        index = index - 1
    return f'{len(E) - index} {abs(G - E[index])}'

def run():
    T = int(input())
    for i in range(T):
        N, G = (int(x) for x in input().split())
        E = [int(input()) for _ in range(N)]
        print(f'Case #{i + 1}: {solve(E, G)}')

run()
