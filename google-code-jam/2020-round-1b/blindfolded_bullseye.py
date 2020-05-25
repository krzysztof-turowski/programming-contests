#!/usr/bin/python

import sys

def get_input(X, Y):
    print(X, Y)
    sys.stdout.flush()
    return input().strip()

def binary(low, high, point, test):
    while low + 1 < high:
        mid = (low + high) // 2
        value = get_input(*point(mid))
        if value == 'CENTER':
            return None
        low, high = (low, mid) if test(value) else (mid, high)
    return low, high

def solve():
    MAX = 10 ** 9
    P = [
        (0, 0), (-MAX // 2, -MAX // 2), (-MAX // 2, MAX // 2),
        (MAX // 2, -MAX // 2), (MAX // 2, MAX // 2)
    ]
    for x, y in P:
        value = get_input(x, y)
        if value == 'CENTER':
            return
        if value == 'HIT':
            break
    _, x_low = binary(-MAX - 1, x, lambda x: (x, y), lambda v: v == 'HIT')
    if x_low is None:
        return
    x_high, _ = binary(x, MAX + 1, lambda x: (x, y), lambda v: v != 'HIT')
    if x_high is None:
        return
    x_mid = (x_low + x_high) // 2
    _, y_low = binary(-MAX - 1, y, lambda y: (x_mid, y), lambda v: v == 'HIT')
    if y_low is None:
        return
    y_high, _ = binary(y, MAX + 1, lambda y: (x_mid, y), lambda v: v != 'HIT')
    if y_high is None:
        return
    y_mid = (y_low + y_high) // 2
    S = [
        (-1, -1), (0, -1), (1, -1), (-1, 0), (0, 0),
        (1, 0), (-1, 1), (0, 1), (1, 1)
    ]
    for s in S:
        value = get_input(x_mid + s[0], y_mid + s[1])
        if value == 'CENTER':
            break

def run():
    T, _, _ = [int(x) for x in input().split()]
    for _ in range(T):
        solve()

run()
