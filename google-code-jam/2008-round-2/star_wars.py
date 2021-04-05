#!/usr/bin/python

import collections

Ship = collections.namedtuple('Ship', 'x y z p')

MAX, EPS = 10e6, 10e-9

def fit(S, value):
    A = max(s.x + s.y + s.z - s.p * value for s in S)
    B = min(s.x + s.y + s.z + s.p * value for s in S)
    C = max(s.x + s.y - s.z - s.p * value for s in S)
    D = min(s.x + s.y - s.z + s.p * value for s in S)
    E = max(s.x - s.y + s.z - s.p * value for s in S)
    F = min(s.x - s.y + s.z + s.p * value for s in S)
    G = max(-s.x + s.y + s.z - s.p * value for s in S)
    H = min(-s.x + s.y + s.z + s.p * value for s in S)
    if A > B or C > D or E > F or G > H:
        return False
    if A - H > B - G or C + E > D + F:
        return False
    if B - G < C + E or D + F < A - H:
        return False
    return True

def solve(S):
    low, high = 0, MAX
    while low + EPS < high:
        mid = (low + high) / 2
        if fit(S, mid):
            high = mid
        else:
            low = mid
    return low

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        S = [Ship(*(int(x) for x in input().split())) for _ in range(N)]
        print('Case #{0}: {1:.6f}'.format(i + 1, solve(S)))

run()
