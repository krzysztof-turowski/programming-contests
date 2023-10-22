#!/usr/bin/python3

import heapq
import itertools

def solve(L, B, N, A):
    time, improvements = 0, []
    for _, a in zip(range(N), itertools.cycle(A)):
        if time > B:
            improvements.append(a)
        elif time + 2 * a > B:
            improvements.append(a - (B - time) // 2)
        time += 2 * a
    return time - sum(heapq.nlargest(L, improvements))

def run():
    T = int(input())
    for i in range(T):
        L, B, N, _, *A = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(L, B, N, A)))

run()
