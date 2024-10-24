#!/usr/bin/python3

import enum

MOD = 998244353

class Element(enum.Enum):
    ONE = 1
    TWO = 2
    SIX = 6
    NINE = 9
    FIFTEEN = 15

def uncorrupt(E):
    V, index = [None] * len(E), len(E) - 1
    while index >= 0:
        if E[index] != '?':
            index -= 1
        elif index == len(E) - 1 or (index < len(E) - 2 and E[index + 2] == '0'):
            if index > 0 and E[index - 1] == '?':
                V[index - 1], index = Element.FIFTEEN, index - 2
            elif E[index - 1] == '2':
                V[index], index = Element.SIX, index - 1
            else:
                V[index], index = Element.NINE, index - 1
        elif E[index + 1] in ('7', '8', '9'):
            V[index], index = Element.ONE, index - 1
        else:
            V[index], index = Element.TWO, index - 1
    return V

def get_kth(E, V, K):
    values = []
    for v in V[::-1]:
        if v is not None:
            values.append((K % v.value, v))
            K //= v.value
    S, index = [None] * len(E), 0
    while index < len(E):
        if E[index] == '?':
            v, m = values.pop()
            if m == Element.FIFTEEN and v <= 5:
                S[index], S[index + 1], index = '2', str(6 - v), index + 2
            elif m == Element.FIFTEEN:
                S[index], S[index + 1], index = '1', str(15 - v), index + 2
            else:
                S[index], index = str(m.value - v), index + 1
        else:
            S[index], index = E[index], index + 1
    return ''.join(S)

def count(S):
    F = [0] * len(S) + [1]
    for i in range(len(S) - 1, -1, -1):
        if S[i] == '0':
            continue
        if i < len(S) - 1 and 10 <= 10 * int(S[i]) + int(S[i + 1]) <= 26:
            F[i] = (F[i + 1] + F[i + 2]) % MOD
        else:
            F[i] = F[i + 1]
    return F[0]

def solve(E, K):
    V = uncorrupt(E)
    S = get_kth(E, V, K - 1)
    return f'{S} {count(S)}'

def run():
    T = int(input())
    for i in range(T):
        E, K = input().split()
        print(f'Case #{i + 1}: {solve(E, int(K))}')

run()
