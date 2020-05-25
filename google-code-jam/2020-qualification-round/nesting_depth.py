#!/usr/bin/python

def solve(S):
    S, out = '0' + S + '0', ''
    for a, b in zip(S[1:], S):
        if int(a) > int(b):
            out += (int(a) - int(b)) * '(' + a
        else:
            out += (int(b) - int(a)) * ')' + a
    return out[:-1]

def run():
    T = int(input())
    for i in range(T):
        S = input().strip()
        print('Case #{0}: {1}'.format(i + 1, solve(S)))

run()
