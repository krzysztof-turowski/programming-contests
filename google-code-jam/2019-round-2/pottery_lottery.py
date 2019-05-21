#!/usr/bin/python

import random
import sys

DAYS, URNS = 100, 20
THROW, ROUNDS, THRESHOLD = [8, 8, 4, 2, 1], 4, 2

def throw(urns):
    for urn in urns:
        if int(input()) == -1:
            sys.exit()
        print(urn, 100)
        sys.stdout.flush()

def read(urn):
    if int(input()) == -1:
        sys.exit()
    print(urn, 0)
    sys.stdout.flush()
    return next(int(x) for x in input().split())

def solve():
    throw(range(1, URNS + 1))
    candidates = set(range(1, URNS + 1))
    throw(random.sample(candidates, THROW[0]) * THRESHOLD)
    for i in range(1, ROUNDS + 1):
        checked = [read(urn) if urn in candidates else None for urn in range(1, URNS + 1)]
        queue = sorted([(i + 1, v) for i, v in enumerate(checked) if v is not None],
                       key = lambda x: x[1])
        candidates = set(index for index, _ in queue[:THROW[i]])
        throw([index for index, _ in queue[THROW[i]:2 * THROW[i]]] * THRESHOLD)

def run():
    T = int(input())
    for _ in range(T):
        solve()

run()
