#!/usr/bin/python

MOD = 4207849484

def solve(M, S):
    D = [1] + [0] * len(S)
    for i, s in enumerate(S):
        if s == '0':
            continue
        for j in range(i, len(S)):
            if int(S[i:j + 1]) <= M:
                D[j + 1] += D[i]
    return D[-1] % MOD

def run():
    T = int(input())
    for i in range(T):
        M, S = int(input()), input()
        print('Case #{0}: {1}'.format(i + 1, solve(M, S)))

run()
