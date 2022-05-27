#!/usr/bin/python

def solve(S):
    index = [0] * len(S)
    for i, s in enumerate(S):
        index[i] = index[i - 1]
        while index[i] < len(S) and S[index[i]] == s:
            index[i] += 1
    return ''.join(s + s if index[i] < len(S) and s < S[index[i]] else s
                   for i, s in enumerate(S))

def run():
    T = int(input())
    for i in range(T):
        S = input().strip()
        print('Case #{0}: {1}'.format(i + 1, solve(S)))

run()
