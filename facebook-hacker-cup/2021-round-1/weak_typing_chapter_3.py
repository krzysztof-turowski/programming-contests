#!/usr/bin/python3

MOD = 1000000007

class Representation:
    def __init__(self, c = 'F'):
        self.length, self.pairs, self.L, self.R, self.out = 1, 0, 0, 0, 0
        self.I1, self.I2 = (None, None), (None, None)
        if c != 'F':
            self.I1, self.I2 = (1, c), (1, c)

def merge(s1, s2):
    r = Representation()
    r.length, r.pairs = (s1.length + s2.length) % MOD, (s1.pairs + s2.pairs) % MOD
    if s1.I1[1] or s2.I1[1]:
        r.I1 = s1.I1 if s1.I1[0] is not None else ((s1.length + s2.I1[0]) % MOD, s2.I1[1])
        r.I2 = ((s1.length + s2.I2[0]) % MOD, s2.I2[1]) if s2.I2[0] is not None else s1.I2
    r.L, r.R = s1.L + s2.L + s2.pairs * s1.length, s1.R + s2.R + s1.pairs * s2.length
    r.out = s1.out + s2.out + s1.L * s2.length + s2.R * s1.length
    if s1.I2[1] and s2.I1[1] and s1.I2[1] != s2.I1[1]:
        r.pairs, r.L, r.R = r.pairs + 1, r.L + s1.I2[0], r.R + s2.length + 1 - s2.I1[0]
        r.out += s1.I2[0] * (s2.length + 1 - s2.I1[0])
    r.L, r.R, r.out = r.L % MOD, r.R % MOD, r.out % MOD
    return r

def solve(S):
    r = Representation(S[0])
    for s in S[1:]:
        r = merge(r, r if s == '.' else Representation(s))
    return r.out

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        print(f'Case #{i + 1}: {solve(input().strip())}')

run()
