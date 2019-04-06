#!/usr/bin/python

T = int(input())
for t in range(T):
    N = int(input())
    A = [int(x) for x in input().split()]
    A[::2], A[1::2] = sorted(A[::2]), sorted(A[1::2])
    print("Case #{0}: {1}".format(
        t + 1, next((index for (index, a, b) in zip(range(N), A, A[1:]) if a > b), "OK")))
