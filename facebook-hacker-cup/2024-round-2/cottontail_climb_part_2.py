#!/usr/bin/python

import bisect
import collections
import itertools

def generate_hills():
    Q = collections.deque((str(x), 1, x) for x in range(1, 10))
    up, down = collections.defaultdict(list), collections.defaultdict(list)
    while Q:
        q, l, d = Q.popleft()
        up[l].append((q, d))
        if l < 8:
            Q.extend((q + str(x), l + 1, x) for x in range(d % 10, 10))
    for k, v in up.items():
        down[k] = list(sorted((x[::-1], d) for x, d in v))
    return up, down

def generate_mountains():
    yield from list(range(1, 10)) + [
        int(a[0] + str(d) + b[0]) for da, la in UPHILLS.items() for a in la
        for d in range(a[1] + 1, 10) for b in DOWNHILLS[da] if b[1] < d]

UPHILLS, DOWNHILLS = generate_hills()
MOUNTAINS = list(generate_mountains())

def solve(A, B, M):
    left, right = bisect.bisect_left(MOUNTAINS, A), bisect.bisect_right(MOUNTAINS, B)
    return sum(1 for p in MOUNTAINS[left:right] if p % M == 0)
        

def run():
    T = int(input())
    for i in range(T):
        A, B, M = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(A, B, M)}')

run()
