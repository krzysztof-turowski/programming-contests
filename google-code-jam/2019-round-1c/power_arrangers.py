#!/usr/bin/python

import sys

L, MAX = 5, 120

def get_input(v):
    day = MAX * v
    return day, [day // i for i in range(1, 7)]

def solve():
    A = [True] * (MAX - 1)
    out = ''
    for offset in range(L - 1):
        S = {}
        for index, value in enumerate(A):
            if value:
                print(index * L + offset + 1)
                sys.stdout.flush()
                ans = ord(input().strip()) - ord('A')
                S[ans] = S.get(ans, []) + [index]
        key = min(S, key = lambda x: len(S.get(x)))
        if offset == L - 2:
            other_key = next(x for x in range(L) if chr(x + ord('A')) not in out and x != key)
            out += chr(other_key + ord('A')) + chr(key + ord('A'))
        else:
            out += chr(key + ord('A'))
        for index, value in enumerate(A):
            if index not in S[key]:
                A[index] = False
    return out

def run():
    T, _ = [int(x) for x in input().split()]
    for _ in range(T):
        print('{0}'.format(solve()))
        sys.stdout.flush()
        if input().strip() == 'N':
            return

run()
