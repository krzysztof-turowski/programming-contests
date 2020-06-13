#!/usr/bin/python

from collections import defaultdict
import sys

def solve(N):
    visible, sold = defaultdict(int), set()
    for _ in range(N):
        preferences = [int(x) for x in input().split()]
        for p in preferences[1:]:
            visible[p] += 1
        try:
            _, index = min((visible[p], p) for p in preferences[1:]
                           if p not in sold)
            print(index)
            sold.add(index)
        except ValueError:
            print(-1)
        sys.stdout.flush()

def run():
    T = int(input())
    for _ in range(T):
        N = int(input())
        solve(N)

run()
