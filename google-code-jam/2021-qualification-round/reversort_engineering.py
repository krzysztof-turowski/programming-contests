#!/usr/bin/python

def solve(N, C):
    P, L = [], list(range(1, N + 1))
    if C > N * (N + 1) // 2 - 1 or C < N - 1:
        return 'IMPOSSIBLE'
    C -= (N - 1)
    for i in range(N - 1):
        j = min(i + C, N - 1)
        P.append((i, j + 1))
        C -= (j - i)
    for a, b in reversed(P):
        L[a:b] = reversed(L[a:b])
    return ' '.join(str(x) for x in L)

def run():
    T = int(input())
    for i in range(T):
        N, C = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, C)))

run()
