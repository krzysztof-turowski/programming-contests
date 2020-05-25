#!/usr/bin/python

import heapq
import string

def solve(P):
    out, L = [], list(zip(P, string.ascii_uppercase))
    heapq.heapify(L)
    while len(L) > 2 or L[1][0] != L[0][0]:
        out.append(L[0][1])
        if L[0][0] < -1:
            heapq.heapreplace(L, (L[0][0] + 1, L[0][1]))
        else:
            heapq.heappop(L)
    out.append(' '.join([L[0][1] + L[1][1]] * (-L[1][0])))
    return ' '.join(out)

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        P = [-int(x) for x in input().strip().split(' ')]
        print('Case #{0}: {1}'.format(i + 1, solve(P)))

run()
