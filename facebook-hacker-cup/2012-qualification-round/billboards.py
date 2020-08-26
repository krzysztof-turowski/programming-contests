#!/usr/bin/python

def fit(S, F, W, H):
    if F * max(len(s) for s in S) > W:
        return False
    w, h = -F, F
    for s in S:
        if w + (len(s) + 1) * F <= W:
            w += (len(s) + 1) * F
        else:
            w, h = len(s) * F, h + F
    return h <= H

def solve(S, W, H):
    low, high = 0, H + 1
    while low + 1 < high:
        mid = (low + high) // 2
        if fit(S, mid, W, H):
            low = mid
        else:
            high = mid
    return low

def run():
    T = int(input())
    for i in range(T):
        W, H, *S = input().split()
        print('Case #{0}: {1}'.format(i + 1, solve(S, int(W), int(H))))

run()
