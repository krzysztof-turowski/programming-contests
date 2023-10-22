#!/usr/bin/python3

def average(X):
    return min(X) + (max(X) - min(X)) / 2

def solve(X):
    if len(X) == 5:
        return max(average(X[3:]) - average(X[:3]), average(X[2:]) - average(X[:2]))
    return average(X[-2:]) - average(X[:2])

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        X = list(sorted([int(x) for x in input().split()]))
        print(f'Case #{i + 1}: {solve(X):.7f}')

run()
