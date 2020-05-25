#!/usr/bin/python

def solve(J, P, S, K):
    out = str(J * P * min(S, K)) + '\n'
    if S <= K:
        L = [(j, p, s) for j in range(1, J + 1) for p in range(1, P + 1)
             for s in range(1, S + 1)]
    else:
        L = [(j, p, (p + j + shift) % S + 1) for j in range(1, J + 1)
             for p in range(1, P + 1) for shift in range(K)]
    out += '\n'.join(' '.join([str(j), str(p), str(s)]) for j, p, s in L)
    return out

def run():
    T = int(input())
    for i in range(T):
        J, P, S, K = [int(x) for x in input().strip().split(' ')]
        print('Case #{0}: {1}'.format(i + 1, solve(J, P, S, K)))

run()
