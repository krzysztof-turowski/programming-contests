#!/usr/bin/python

import collections
import re

def compare(S_1, S_2):
    c_1, c_2 = min(S_1.keys()), max(S_2.keys())
    if c_1 > c_2:
        return True
    if c_1 < c_2:
        return False
    if len(S_1) > 1 or S_1[c_1] > S_2[c_1]:
        return True
    return False

def split(S, P):
    if P >= len(S):
        return list(S)
    return list(S[:P - 1]) + [S[P - 1:]]

def solve_2(S):
    S_1, S_2 = collections.defaultdict(int), collections.Counter(S)
    for i, c in enumerate(S[:-1], start = 1):
        S_1[c], S_2[c] = S_1[c] + 1, S_2[c] - 1
        if S_2[c] == 0:
            del S_2[c]
        if compare(S_1, S_2):
            return (S[:i], S[i:])
    return None

def solve_3(S):
    S_1 = collections.defaultdict(int)
    for i, c in enumerate(S[:-2], start = 1):
        S_1[c] += 1
        if compare(S_1, {S[i]: 1}):
            return (S[:i], S[i], S[i + 1:])
    S_2, S_3 = {}, collections.Counter(S[1:])
    for i, c in enumerate(S[1:-1], start = 1):
        S_2, S_3[c] = {c: S_2.get(c, 0) + 1}, S_3[c] - 1
        if S_3[c] == 0:
            del S_3[c]
        if compare(S_2, S_3):
            return (S[:i], S[i], S[i + 1:])
    return None

def solve(S, P):
    if P == len(S):
        return f'POSSIBLE\n{" ".join(S)}' if ''.join(sorted(S)) != S else 'IMPOSSIBLE'
    if P == 2:
        out = solve_2(S)
        return f'POSSIBLE\n{" ".join(out)}' if out else 'IMPOSSIBLE'
    if P == 3:
        out = solve_3(S)
        return f'POSSIBLE\n{" ".join(out)}' if out else 'IMPOSSIBLE'
    index = next((i for i, (a, b) in enumerate(zip(S, S[1:])) if a > b), None)
    if index:
        last = split(S[index + 2:], P - 3 if index > 0 else P - 2)
        first = split(S[:index], P - len(last) - 2)
        return f'POSSIBLE\n{" ".join(first + [S[index], S[index + 1]] + last)}'
    match = re.search(r'(\w)\1{2}', S)
    if match:
        index = match.start(0)
        last = split(S[index + 3:], P - 3 if index > 0 else P - 2)
        first = split(S[:index], P - len(last) - 2)
        return f'POSSIBLE\n{" ".join(first + [S[index:index + 2], S[index + 2]] + last)}'
    return 'IMPOSSIBLE'


def run():
    T = int(input())
    for i in range(T):
        P, S = input().strip().split()
        print(f'Case #{i + 1}: {solve(S, int(P))}')

run()
