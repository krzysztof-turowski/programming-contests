#!/usr/bin/python

import bisect

def generate_peaks():
    for k in range(1, 10):
        for d in range(1, 11 - k):
            yield int(''.join(str(s) for s in range(d, d + k))
                      + ''.join(str(s) for s in range(d + k - 2, d - 1, -1)))

PEAKS = list(generate_peaks())

def solve(A, B, M):
    left, right = bisect.bisect_left(PEAKS, A), bisect.bisect_right(PEAKS, B)
    return sum(1 for p in PEAKS[left:right] if p % M == 0)

def run():
    T = int(input())
    for i in range(T):
        A, B, M = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(A, B, M)}')

run()
