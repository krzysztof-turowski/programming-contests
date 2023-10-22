#!/usr/bin/python3

def solve(R, C, S):
    if min(R, C) == 1:
        total = sum(1 for row in S for v in row if v == '^')
        if total != 0:
            return 'Impossible'
    else:
        S = [row.replace('.','^') for row in S]
    return 'Possible\n' + '\n'.join(S)

def run():
    T = int(input())
    for t in range(T):
        R, C = (int(x) for x in input().split())
        S = [input().strip() for _ in range(R)]
        print(f'Case #{t + 1}: {solve(R, C, S)}')

run()
