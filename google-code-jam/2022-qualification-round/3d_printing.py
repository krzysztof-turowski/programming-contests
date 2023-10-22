#!/usr/bin/python3

PRINTERS = 3
LIMIT = 10 ** 6

def solve(C):
    def get_min(index):
        return min(C[i][index] for i in range(PRINTERS))
    bound = [get_min(index) for index, _ in enumerate(C[0])]
    if sum(bound) < LIMIT:
        return 'IMPOSSIBLE'
    out = [0] * len(bound)
    for i, b in enumerate(bound):
        if sum(out) < LIMIT:
            out[i] = min(LIMIT - sum(out), b)
    return ' '.join(str(v) for v in out)

def run():
    T = int(input())
    for i in range(T):
        C = [[int(x) for x in input().split()] for _ in range(PRINTERS)]
        print('Case #{0}: {1}'.format(i + 1, solve(C)))

run()
