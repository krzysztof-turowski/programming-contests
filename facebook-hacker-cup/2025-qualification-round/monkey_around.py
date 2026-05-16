#!/usr/bin/python3

import math

def solve(B):
    lengths, shifts, index = [], [], 0
    while index < len(B):
        if B[index] == 1:
            last = next(
                (i for i, x in enumerate(B[index:], start=index) if i - x != index - 1),
                len(B)) - 1
        else:
            last = next((i for i, x in enumerate(B[index:], start=index) if x == 1)) - 1
        lengths.append(B[last])
        shifts.append(B[index] - 1)
        index += B[last]

    for index in range(len(shifts) - 2, -1, -1):
        if shifts[index] < shifts[index + 1]:
            k = math.ceil((shifts[index + 1] - shifts[index]) / lengths[index])
            shifts[index] += k * lengths[index]
    total = len(lengths) + shifts[0]
    for index in range(0, len(shifts) - 1):
        shifts[index] -= shifts[index + 1]
    return str(total) + '\n' + ''.join(
        (f'1 {l}\n' + '2\n' * s) for l, s in zip(lengths, shifts))
        

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        B = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(B)}', end='')

run()
