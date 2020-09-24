#!/usr/bin/python

def solve(start, end, Q, D):
    if start > end:
        return 0
    if (start, end) not in D:
        D[(start, end)] = min(
            (end - start + solve(start, k - 1, Q, D) + solve(k + 1, end, Q, D)
             for k in Q if start <= k <= end),
            default = 0)
    return D[(start, end)]

def run():
    T = int(input())
    for i in range(T):
        P, _ = (int(x) for x in input().split())
        Q = {int(x) for x in input().split()}
        print('Case #{0}: {1}'.format(i + 1, solve(1, P, Q, {})))

run()
