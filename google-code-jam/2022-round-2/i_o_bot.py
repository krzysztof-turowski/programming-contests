#!/usr/bin/python3

import collections

def get_total_cost(B, C):
    cost = [0, 0]
    count, prefix = [0, 0], [0, 0]
    lookup = collections.defaultdict(lambda: (0, (0, 0)))
    for i, (x, shape) in enumerate(B, 1):
        count[shape], prefix[shape] = count[shape] + 1, prefix[shape] + x
        cost_j, prefix_j = lookup[count[0] - count[1]]
        cost.append(min(
            cost[-2] + 2 * x + (C if shape == B[i - 1][1] else 0),
            cost_j + 2 * prefix[shape] - 2 * prefix_j[shape]))
        lookup[count[0] - count[1]] = (cost[-1], prefix[:])
    return cost[-1]

def solve(B, C):
    B_plus = sorted([(x, shape) for x, shape in B if x > 0])
    B_minus = sorted([(-x, shape) for x, shape in B if x < 0])
    return get_total_cost(B_plus, C) + get_total_cost(B_minus, C)

def run():
    T = int(input())
    for t in range(T):
        N, C = (int(x) for x in input().split())
        B = [tuple(int(x) for x in input().split()) for _ in range(N)]
        print(f'Case #{t + 1}: {solve(B, C)}')

run()
