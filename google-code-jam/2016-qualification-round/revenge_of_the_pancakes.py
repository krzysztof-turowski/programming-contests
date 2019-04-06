#!/usr/bin/python

def solve(A):
    return sum([x != y for x, y in zip(A[1:], A[:-1])]) + (A[-1] == '-')

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(i + 1, solve(input())))

run()
