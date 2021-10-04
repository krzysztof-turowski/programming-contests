#!/usr/bin/python

MOD = 1000000007

def solve(S):
    out, sum_fixed, fixed, unfixed, previous = 0, 0, 0, 0, None
    for s in S:
        if s == previous:
            fixed, unfixed = fixed + unfixed + 1, 0
        elif s == 'F':
            unfixed += 1
        else:
            previous = s
            sum_fixed += fixed
            fixed, unfixed = fixed + unfixed + 1, 0
        out = (out + sum_fixed) % MOD
    return out

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        print('Case #{0}: {1}'.format(i + 1, solve(input().strip())))

run()
