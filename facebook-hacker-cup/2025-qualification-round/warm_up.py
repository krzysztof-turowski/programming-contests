#!/usr/bin/python3

def solve(A, B):
    if any(a > b for a, b in zip(A, B)):
        return -1
    if not (set(B) <= set(A)):
        return -1
    if all(a == b for a, b in zip(A, B)):
        return 0

    target = {a: i for i, a in enumerate(A, start=1)}
    initial = sorted((b, i) for i, (a, b) in enumerate(zip(A, B), start=1) if a != b)
    out = [(i, target[b]) for b, i in initial]
    return str(len(out)) + '\n' + '\n'.join(f'{b} {a}' for a, b in out)
        

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = [int(x) for x in input().split()]
        B = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(A, B)}')

run()
