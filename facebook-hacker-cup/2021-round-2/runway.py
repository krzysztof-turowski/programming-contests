#!/usr/bin/python3

import collections
import copy

MAX = 1000

def read_dictionary(L):
    out = collections.defaultdict(int)
    for e in L:
        out[int(e)] += 1
    return out

def solve(S):
    out, before_original = 0, copy.deepcopy(S[0])
    for before, after in zip(S, S[1:]):
        after_original = collections.defaultdict(int)
        for k in before:
            changing = max(before[k] - after.get(k, 0), 0)
            if changing < before_original[k]:
                after_original[k] = before_original[k] - changing
            out += max(changing - before_original[k], 0)
        before_original = after_original
    return out

def run():
    T = int(input())
    for i in range(T):
        M, _ = (int(x) for x in input().split())
        S = [read_dictionary(input().split()) for _ in range(M + 1)]
        print('Case #{0}: {1}'.format(i + 1, solve(S)))

run()
