#!/usr/bin/python

import sys

def print_output(X):
    print(X)
    sys.stdout.flush()

def get_input():
    return int(input().strip())

def solve(N, B):
    count = [0] * N
    for _ in range(N * B):
        v = get_input()
        if v == 9 and any(v == B - 1 for v in count):
            index = count.index(B - 1)
        elif v >= 8 and any(v == B - 2 for v in count):
            index = count.index(B - 2)
        elif any(v < B - 2 for v in count):
            index = count.index(max(v for v in count if v < B - 2))
        else:
            index = count.index(min(count))
        count[index] += 1
        print_output(index + 1)

def run():
    T, N, B, _ = (int(x) for x in input().split())
    for _ in range(T):
        solve(N, B)
    get_input()

run()
