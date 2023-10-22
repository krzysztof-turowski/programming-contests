#!/usr/bin/python3

def solve(C):
    return 'Y' if abs(sum(1 if c == 'A' else -1 for c in C)) == 1 else 'N'

def run():
    T = int(input())
    for i in range(T):
        _, C = int(input()), input().strip()
        print('Case #{0}: {1}'.format(i + 1, solve(C)))

run()
