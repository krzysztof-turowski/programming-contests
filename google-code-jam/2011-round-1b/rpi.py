#!/usr/bin/python

def solve(B):
    wins = [sum(1 if c == '1' else 0 for c in row) for row in B]
    alls = [sum(1 if c != '.' else 0 for c in row) for row in B]
    owp = [sum((wins[j] - 1) / (alls[j] - 1) if c == '0'
               else wins[j] / (alls[j] - 1)
               for j, c in enumerate(row) if c != '.') / alls[i]
           for i, row in enumerate(B)]
    oowp = [sum(owp[j] for j, c in enumerate(row) if c != '.') / alls[i]
            for i, row in enumerate(B)]
    rpi = [0.25 * w / a + 0.5 * x + 0.25 * y
           for w, a, x, y in zip(wins, alls, owp, oowp)]
    return '\n'.join('{:.9f}'.format(r) for r in rpi)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        B = [input() for _ in range(N)]
        print('Case #{0}:\n{1}'.format(i + 1, solve(B)))

run()
