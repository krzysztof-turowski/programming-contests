#!/usr/bin/python3

import collections

def solve(D):
    bound, out = 0, 0
    while len(D) > 0:
        v = min(D[0], D[-1])
        if v == D[0]:
            D.popleft()
        else:
            D.pop()
        if v >= bound:
            bound, out = v, out + 1
    return out

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        D = collections.deque(int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(D)))

run()
