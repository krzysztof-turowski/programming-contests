#!/usr/bin/python3

def solve(A):
    out = 0
    for i, _ in enumerate(A[:-1]):
        L = len(A[i]) - len(A[i + 1])
        if L >= 0:
            if A[i][:len(A[i + 1])] > A[i + 1]:
                out += L + 1
                A[i + 1] += '0' * (L + 1)
            elif A[i][:len(A[i + 1])] == A[i + 1]:
                end = A[i][len(A[i + 1]):]
                if end == '9' * L:
                    out += L + 1
                    A[i + 1] += '0' * (L + 1)
                else:
                    out += L
                    A[i + 1] += str(int(end) + 1).zfill(L)
            else:
                out += L
                A[i + 1] += '0' * L
    return out

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        A = input().split()
        print('Case #{0}: {1}'.format(i + 1, solve(A)))

run()
