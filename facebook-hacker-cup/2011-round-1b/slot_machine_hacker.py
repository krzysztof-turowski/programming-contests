#!/usr/bin/python

MOD = 1000
MAX_MOD = 10000001

def get_random_number(secret):
    return (secret * 5402147 + 54321) % 10000001

def solve(L):
    V = {i * MOD + L[0] for i in range(MAX_MOD // MOD + 1)}
    for u in L[1:]:
        V = {get_random_number(v) for v in V if get_random_number(v) % MOD == u}
    if len(V) == 0:
        return 'Wrong machine'
    if len(V) > 1:
        return 'Not enough observations'
    U, state = [], min(V)
    for _ in range(10):
        state = get_random_number(state)
        U.append(state % MOD)
    return ' '.join(str(u) for u in U)

def run():
    T = int(input())
    for i in range(T):
        _, *L = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(L)))

run()
