#!/usr/bin/python

import collections
import functools
import math

Student = collections.namedtuple('Student', 'answers score')

def get_student(data):
    return Student(data[0], int(data[1]))

@functools.lru_cache(maxsize = None)
def binomial(n, m):
    if m in (0, n):
        return 1
    return binomial(n - 1, m) + binomial(n - 1, m - 1)

def invert(c, b):
    return 'T' if (c == 'T') ^ b else 'F'

def get_answers(A, i):
    test = sum(a.answers[i] == 'T' for a in A)
    return ''.join(invert(a.answers[i], test < len(A) / 2) for a in A)

def solve(A, Q):
    A += [A[0]] * (3 - len(A))
    D = collections.defaultdict(int)
    for i in range(Q):
        D[get_answers(A, i)] += 1
    check = []
    for ttt in range(D['TTT'] + 1):
        ttf = (A[0].score + A[1].score - 2 * ttt - D['TFT'] - D['FTT']) // 2
        tft = (A[0].score + A[2].score - 2 * ttt - D['TTF'] - D['FTT']) // 2
        ftt = (A[1].score + A[2].score - 2 * ttt - D['TTF'] - D['TFT']) // 2
        if (0 <= ttf <= D['TTF'] and 0 <= tft <= D['TFT'] and 0 <= ftt <= D['FTT']):
            check.append({'TTT': ttt, 'TTF': ttf, 'TFT': tft, 'FTT': ftt})
    total, T = 0, {k: 0 for k in D}
    for C in check:
        value = math.prod(binomial(D[k], C[k]) for k in D)
        total += value
        T = {k: v + value * C[k] for k, v in T.items()}
    out = ''
    for i in range(Q):
        a = get_answers(A, i)
        out += ('T' if (A[0].answers[i] != a[0]) ^ (T[a] / total >= D[a] / 2) else 'F')
    num = sum(max(T[k], total * D[k] - T[k]) for k in D)
    d = math.gcd(num, total)
    return out + f' {num // d}/{total // d}'

def run():
    T = int(input())
    for t in range(T):
        N, Q = (int(x) for x in input().split())
        A = [get_student(input().split()) for _ in range(N)]
        print(f'Case #{t + 1}: {solve(A, Q)}')

run()
