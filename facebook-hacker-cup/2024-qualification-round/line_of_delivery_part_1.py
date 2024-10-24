#!/usr/bin/python3

import bisect

def solve(E, G):
    E = list(sorted(E))
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
