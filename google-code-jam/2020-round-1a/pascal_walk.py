#!/usr/bin/python

import scipy.special

def check(pairs, N):
    for u, v in zip(pairs, pairs[1:]):
        assert ((u[0] == v[0] and u[1] + 1 == v[1])
                or (u[0] == v[0] and u[1] - 1 == v[1])
                or (u[0] + 1 == v[0] and u[1] == 1 and v[1] == 1)
                or (u[0] + 1 == v[0] and u[0] == u[1] and v[0] == v[1]))
    assert sum(scipy.special.binom(r - 1, k - 1) for r, k in pairs) == N

def get_binary(N):
    S, index = set(), 1
    while N > 0:
        if N % 2 == 1:
            S.add(index)
        N, index = N // 2, index + 1
    return S

def solve(N):
    S, left, pairs, remaining = get_binary(N - 32) if N >= 32 else set(), True, [], N
    maximum = max(S) + 33 if S else 33
    for r in range(1, maximum):
        if remaining <= 0:
            break
        if r in S:
            if left:
                pairs += [(r, i) for i in range(1, r + 1)]
            else:
                pairs += [(r, i) for i in range(r, 0, -1)]
            left, remaining = not left, remaining - 2 ** (r - 1)
        else:
            if left:
                pairs.append((r, 1))
            else:
                pairs.append((r, r))
            remaining -= 1
    check(pairs, N)
    out = '\n'.join(str(x) + ' ' + str(y) for (x, y) in pairs)
    return out

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        print('Case #{0}:\n{1}'.format(i + 1, solve(N)))

run()
