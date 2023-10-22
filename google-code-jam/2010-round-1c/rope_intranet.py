#!/usr/bin/python3

def solve(L):
    return sum(sum(1 if q[1] > a[1] else 0 for q in L[:i])
               for i, a in enumerate(L))

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        L = list(sorted(tuple(int(x) for x in input().split())
                        for _ in range(N)))
        print('Case #{0}: {1}'.format(i + 1, solve(L)))

run()
