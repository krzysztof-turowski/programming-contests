#!/usr/bin/python3

def checksum(A):
    result = 1
    for a in A:
        result = (31 * result + a) % 1000003
    return result

def simulate(A, S, index):
    if len(A) == 1:
        return A, index
    N = len(A) // 2
    left, index = simulate(A[:N], S, index)
    right, index = simulate(A[N:], S, index)
    i, l, r = 0, 0, 0
    while l < len(left) and r < len(right):
        if S[index] == 1:
            A[i], i, l = left[l], i + 1, l + 1
        else:
            A[i], i, r = right[r], i + 1, r + 1
        index += 1
    return A[:i] + left[l:] + right[r:], index

def solve(N, S):
    A, _ = simulate(list(range(N)), S, 0)
    out = [0] * N
    for i, a in enumerate(A, start = 1):
        out[a] = i
    return checksum(out)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        S = [int(x) for x in input()]
        print('Case #{0}: {1}'.format(i + 1, solve(N, S)))

run()
