#!/usr/bin/python

import collections

MOD = 1000000007

def solve(A):
    A, out = [0] + A + [0], 1
    D = [[collections.defaultdict(int) for _ in A] for _ in A]
    D[0][len(A) - 1][0] = 1
    for length in range(len(A) - 1, 0, -1):
        for left in range(len(A) - length):
            right = left + length
            for k in range(len(A) - 1):
                if k not in D[left][right]:
                    continue
                C = set()
                for index in range(left + 1, right):
                    if (A[index] not in C and
                        and max(k + 1, A[left], A[right]) <= A[index]):
                        C.add(A[index])
                        D[index][right][k + 1] += (
                            D[left][right][k] * (A[index] - k))
                C = set()
                for index in range(right - 1, left, -1):
                    if (A[index] not in C and
                        max(k + 1, A[left] + 1, A[right]) <= A[index]):
                        C.add(A[index])
                        D[left][index][k + 1] += (
                            D[left][right][k] * (A[index] - k))

    for left, vl in enumerate(A):
        for right, vr in enumerate(A[left:], start = left):
            if vl > vr:
                out += sum(D[left][right].values())
    return out % MOD

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(A)))

run()
