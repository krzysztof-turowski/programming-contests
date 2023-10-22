#!/usr/bin/python3

import math

def solve_first(R, C, N):
    out, remaining = (2 * R * C - R - C), R * C - N
    fours = (R - 2) * (C - 2) // 2
    if fours >= remaining:
        return out - 4 * remaining
    remaining, out = remaining - fours, out - 4 * fours
    threes = ((C - 2 if R % 2 == 0 else 2 * math.ceil((C - 2) / 2))
              + (R - 2 if C % 2 == 0 else 2 * math.ceil((R - 2) / 2)))
    if threes >= remaining:
        return out - 3 * remaining
    remaining, out = remaining - threes, out - 3 * threes
    return out - 2 * remaining

def solve_second(R, C, N):
    out, remaining = (2 * R * C - R - C), R * C - N
    fours = math.ceil((R - 2) * (C - 2) / 2)
    if fours >= remaining:
        return out - 4 * remaining
    remaining, out = remaining - fours, out - 4 * fours
    threes = ((C - 2 if R % 2 == 0 else 2 * ((C - 2) // 2))
              + (R - 2 if C % 2 == 0 else 2 * ((R - 2) // 2)))
    if threes >= remaining:
        return out - 3 * remaining
    remaining, out = remaining - threes, out - 3 * threes
    return out - 2 * remaining

def solve(R, C, N):
    if math.ceil(R * C / 2) >= N:
        return 0
    if R == 1:
        return 2 * N - C - 1
    return min(solve_first(R, C, N), solve_second(R, C, N))

def run():
    T = int(input())
    for i in range(T):
        R, C, N = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(min(R, C), max(R, C), N)))

run()
