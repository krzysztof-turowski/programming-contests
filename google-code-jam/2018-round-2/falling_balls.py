#!/usr/bin/python

def solve(A, B):
    if B[0] == 0 or B[-1] == 0:
        return "IMPOSSIBLE", ""
    out = []
    while sum([abs(a - b) for (a, b) in zip(A, B)]) > 0:
        row = ['.'] * len(A)
        LA, LB = A[0], B[0]
        for i in range(1, len(A) - 1):
            if LB > LA:
                row[i] = '/'
            LA, LB = LA + A[i], LB + B[i]
            if LB < LA:
                row[i] = '\\'
        X = A
        for i, _ in enumerate(A):
            A[i] = ((X[i] if row[i] == '.' else 0)
                    + (X[i - 1] if (i > 0 and row[i - 1] == '\\') else 0)
                    + (X[i + 1] if (i < len(A) - 1 and row[i + 1] == '/') else 0))
        out.append(''.join(row))
    out.append('.' * len(A))
    return len(out), '\n' + '\n'.join(out)

def run():
    T = int(input())
    for t in range(T):
        _ = int(input())
        B = [int(x) for x in input().split()]
        print('Case #{0}: {1} {2}'.format(t + 1, *solve([1] * len(B), B)))

run()
