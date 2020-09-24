#!/usr/bin/python

def solve(X):
    b_pos, o_pos, b_time, o_time = 1, 1, 0, 0
    for c, v in X:
        if c == 'B':
            b_pos, b_time = v, max(o_time + 1, b_time + abs(v - b_pos) + 1)
        else:
            o_pos, o_time = v, max(b_time + 1, o_time + abs(v - o_pos) + 1)
    return max(b_time, o_time)

def run():
    T = int(input())
    for i in range(T):
        L = input().split()
        X = [(c, int(v)) for c, v in zip(L[1::2], L[2::2])]
        print('Case #{0}: {1}'.format(i + 1, solve(X)))

run()
