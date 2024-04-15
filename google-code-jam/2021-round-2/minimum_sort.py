#!/usr/bin/python

import sys

def get_input(command):
    print(command)
    sys.stdout.flush()
    return int(input())

def solve(N):
    for i in range(N - 1):
        position = get_input(f'M {i + 1} {N}')
        if position != i + 1:
            get_input(f'S {i + 1} {position}')
    get_input('D')

def run():
    T, N = [int(x) for x in input().split()]
    for _ in range(T):
        solve(N)

run()
