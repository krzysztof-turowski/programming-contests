#!/usr/bin/python

def solve(B, M):
    if M > 2 ** (B - 2):
        return 'IMPOSSIBLE'
    G = [[int(0 < i < j) for j in range(B)] for i in range(B)]
    if M == 2 ** (B - 2):
        G[0] = [0] + [1] * (B - 1)
    else:
        G[0] = [0] + list(
            reversed([int((M & (1 << i)) > 0) for i in range(B - 2)])) + [0]
    return 'POSSIBLE\n' + '\n'.join(''.join(str(x) for x in row) for row in G)

def run():
    T = int(input())
    for i in range(T):
        B, M = input().strip().split(' ')
        print('Case #{0}: {1}'.format(i + 1, solve(int(B), int(M))))

run()
