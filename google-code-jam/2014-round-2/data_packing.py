#!/usr/bin/python3

def solve(X, S):
    out, start, end = 0, 0, len(S) - 1
    while start <= end:
        if S[start] + S[end] <= X:
            out, start, end = out + 1, start + 1, end - 1
        else:
            out, end = out + 1, end - 1
    return out

def run():
    T = int(input())
    for i in range(T):
        _, X = (int(x) for x in input().split())
        S = list(sorted([int(x) for x in input().split()]))
        print('Case #{0}: {1}'.format(i + 1, solve(X, S)))

run()
