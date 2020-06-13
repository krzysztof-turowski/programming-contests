#!/usr/bin/python

def solve(X):
    C = sum(x[1] - x[0] for x in X if x[2] == 'C')
    J = sum(x[1] - x[0] for x in X if x[2] == 'J')
    X.append((X[0][0] + 1440, X[0][1] + 1440, X[0][2]))
    same_C = sorted([y[0] - x[1] for x, y in zip(X, X[1:])
                     if x[2] == 'C' and y[2] == 'C'], reverse = True)
    same_J = sorted([y[0] - x[1] for x, y in zip(X, X[1:])
                     if x[2] == 'J' and y[2] == 'J'], reverse = True)
    return sum(x[2] != y[2] for x, y in zip(X, X[1:])) \
        + 2 * next(
            (i for i, _ in enumerate(same_C) if C + sum(same_C[i:]) <= 720),
            len(same_C)) \
        + 2 * next(
            (i for i, _ in enumerate(same_J) if J + sum(same_J[i:]) <= 720),
            len(same_J))

def run():
    T = int(input())
    for i in range(T):
        C, J = [int(x) for x in input().split()]
        X = [[int(x) for x in input().split()] + ['C' if i < C else 'J']
             for i in range(C + J)]
        print('Case #{0}: {1}'.format(i + 1, solve(sorted(X))))

run()
