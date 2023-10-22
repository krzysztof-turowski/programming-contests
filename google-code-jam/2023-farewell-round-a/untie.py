#!/usr/bin/python3

def get_runs(C):
    start = 0
    for i, c in enumerate(C):
        if c != C[start]:
            yield i - start
            start = i
    yield len(C) - start

def solve(C):
    d = next((i for i, c in enumerate(C) if c != C[0]), None)
    if d is None:
        return (len(C) + 1) // 2
    return sum(x // 2 for x in get_runs(C[d:] + C[:d]))

def run():
    T = int(input())
    for i in range(T):
        print(f'Case #{i + 1}: {solve(input().strip())}')

run()
