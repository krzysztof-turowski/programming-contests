#!/usr/bin/python3

def solve(X):
    current = {0: 0}
    for x in X:
        l, h = min(x), max(x)
        current = {
            l : min(v + abs(h - k) + h - l for k, v in current.items()),
            h : min(v + abs(l - k) + h - l for k, v in current.items())}
    return min(current.values())

def run():
    T = int(input())
    for i in range(T):
        N, _ = (int(x) for x in input().split())
        X = [(tuple(int(x) for x in input().split())) for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(X)))

run()
