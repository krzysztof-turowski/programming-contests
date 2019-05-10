#!/usr/bin/python

import sys

MAX, LIMIT = 56, 7
CODES = [4, 1]

def get_input(v):
    day = MAX * v
    return day, [day // i for i in range(1, 7)]

def solve():
    A = [-1] * 6
    for code in CODES:
        day, D = get_input(code)
        print(day)
        sys.stdout.flush()
        ans = int(input().strip())
        for a, d in zip(A, D):
            if a != -1:
                ans -= (a << d)
        for i, d in enumerate(D):
            if A[i] == -1 and d <= MAX:
                A[i] = (ans >> d) % (2 ** LIMIT)
    return ' '.join(str(x) for x in A)

def run():
    T, _ = [int(x) for x in input().split()]
    for _ in range(T):
        print('{0}'.format(solve()))
        sys.stdout.flush()
        if int(input()) == -1:
            return

run()
