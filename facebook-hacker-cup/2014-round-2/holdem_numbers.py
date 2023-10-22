#!/usr/bin/python3

import scipy.special

def count(v, c, taken):
    return max(0, v - sum(1 for u in c if u <= v) - taken)

def get_wins(c, N):
    out = 0
    DP = [[0] * 4 for _ in range(N + 1)]
    DP[N][0] = 1
    for i in range(N, 0, -1):
        for k in range(4):
            DP[i - 1][k] = DP[i][k]
        if i in c or i + 1 >= sum(c):
            continue
        limit = sum(c) - i
        if i > max(c):
            limit -= 1
        if limit < i:
            for k in range(3):
                DP[i - 1][k + 1] += DP[i][k] * count(limit, c, k)
        else:
            for k in range(4):
                if DP[i][k] == 0:
                    continue
                out += (DP[i][k] * int(scipy.special.binom(count(i, c, k), (3 - k) * 2))
                        * int(scipy.special.factorial2((3 - k) * 2 - 1)))
            break
    return out

def solve(C, N):
    out = ''
    for c in C:
        wins = get_wins(c, N)
        total = 15 * int(scipy.special.binom(N - 2, 6))
        out += 'B' if 4 * wins > total else 'F'
    return out

def run():
    T = int(input())
    for i in range(T):
        N, H = (int(x) for x in input().split())
        C = [tuple(int(x) for x in input().split()) for _ in range(H)]
        print(f'Case #{i + 1}: {solve(C, N)}')

run()
