#!/usr/bin/python3

def solve(B, position = 0):
    if not B:
        return 0
    first = min(i for i, v in enumerate(B) if v <= position)
    return first + solve(B[:first] + B[first + 1:], position + 1)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        B = [max((i for i, c in enumerate(input().strip()) if c == '1'),
                 default = -1) for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(B)))

run()
