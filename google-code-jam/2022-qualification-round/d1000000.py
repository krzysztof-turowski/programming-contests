#!/usr/bin/python3

def solve(S):
    index = 0
    for s in S:
        if s > index:
            index += 1
    return index

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        S = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(sorted(S))))

run()
