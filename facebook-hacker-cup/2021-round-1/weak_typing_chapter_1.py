#!/usr/bin/python

def solve(S):
    out, previous = -1, None
    for s in S:
        if s not in ('F', previous):
            out, previous = out + 1, s
    return max(out, 0)

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        print('Case #{0}: {1}'.format(i + 1, solve(input().strip())))

run()
