#!/usr/bin/python

def solve(A):
    out = ['*'] * len(A)
    C, J = 0, 0
    for e, i in sorted((e, i) for i, e in enumerate(A)):
        if e[0] >= C:
            C, out[i] = e[1], 'C'
        elif e[0] >= J:
            J, out[i] = e[1], 'J'
        else:
            return 'IMPOSSIBLE'
    return ''.join(out)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        A = [[int(x) for x in input().strip().split()] for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(A)))

run()
