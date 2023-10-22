#!/usr/bin/python3

import itertools

N = [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]
R = [(-1, 0), (0, -1), (0, 1), (1, 0)]
B = [(-1, -1), (-1, 1), (1, -1), (1, 1)]

def contains(p):
    return all(1 <= v <= 16 for v in p)

def add(p, shift, multiply = 1):
    return tuple(u + v * multiply for u, v in zip(p, shift))

def check_once(position, moves, X):
    out = set()
    for shift in moves:
        other = add(position, shift)
        if contains(other) and other in X:
            out.add(other)
    return out

def check_line(position, moves, X):
    out = set()
    for shift in moves:
        for i in itertools.count(start = 1):
            other = add(position, shift, i)
            if not contains(other):
                break
            if other in X:
                out.add(other)
                break
    return out

def solve(X):
    out = set()
    for position, figure in X.items():
        if figure == 'K':
            out |= check_once(position, R + B, X)
        if figure in ('R', 'Q'):
            out |= check_line(position, R, X)
        if figure in ('B', 'Q', 'A'):
            out |= check_line(position, B, X)
        if figure in ('N', 'A'):
            out |= check_once(position, N, X)
        if figure == 'S':
            out |= check_line(position, N, X)
        if figure == 'E':
            for other in X:
                if position != other:
                    out.add(other)
    return len(out)

def run():
    T = int(input())
    for i in range(T):
        M, X = int(input()), {}
        for _ in range(M):
            name, x, y = input().split()
            X[(int(x), int(y))] = name
        _ = input()
        print('Case #{0}: {1}'.format(i + 1, solve(X)))

run()
