#!/usr/bin/python3

MAX = 41

def recurse(P, S, M):
    if S < 0:
        return None
    if S == 0 and P == 1:
        return []
    if P == 1:
        return [1] * S
    if P == S:
        return [P]
    out = None
    for i in range(M, 1, -1):
        if P % i == 0:
            divisors = recurse(P // i, S - i, i)
            if divisors is None:
                continue
            divisors.append(i)
            if out is None or len(out) > len(divisors):
                out = divisors
    return out

def solve(P):
    D = recurse(P, MAX, MAX)
    return str(len(D)) + ' ' + ' '.join(str(x) for x in sorted(D)) if D else -1

def run():
    T = int(input())
    for i in range(T):
        print(f'Case #{i + 1}: {solve(int(input()))}')

run()
