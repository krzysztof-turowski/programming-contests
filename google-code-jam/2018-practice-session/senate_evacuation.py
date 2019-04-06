#!/usr/bin/python

import heapq

def solve(P, S, N):
    heapq.heapify(P)
    out = []
    while S > 0:
        value, first = heapq.heappop(P)
        if value + 1 != 0:
            heapq.heappush(P, (value + 1, first))
        if (S == N and N % 2 == 1) or (S == N + 1 and N % 2 == 0):
            out.append(first)
            S -= 1
        else:
            value, second = heapq.heappop(P)
            if value + 1 != 0:
                heapq.heappush(P, (value + 1, second))
            out.append(first + second)
            S -= 2
    return out

def run():
    T = int(input())
    for t in range(T):
        N = int(input())
        P = [(-int(value), chr(index + ord('A')))
             for (value, index) in zip(input().split(), range(N))]
        S = sum([-value for (value, index) in P])
        out = solve(P, S, N)
        print("Case #{0}: {1}".format(t + 1, ' '.join(out)))

run()
