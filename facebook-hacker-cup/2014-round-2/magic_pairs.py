#!/usr/bin/python

def get_last(B, C, index):
    for i in range(index, len(B)):
        if B[i] not in C:
            return i
    return len(B)

def add(D, v):
    if -v in D:
        D.remove(-v)
    else:
        D.add(v)

def solve(B1, B2):
    out, C1, C2, D, i1, i2 = 0, set(), set(), set(), 0, 0
    while i1 < len(B1) and i2 < len(B2):
        C1.add(B1[i1])
        C2.add(B2[i2])
        add(D, B1[i1])
        add(D, -B2[i2])
        j1, j2 = get_last(B1, C1, i1), get_last(B2, C2, i2)
        if len(D) == 0:
            out += (j1 - i1) * (j2 - i2)
        i1, i2 = j1, j2
    return out

def generate(V1, V2, N, M):
    length = max(N, M)
    out1, out2 = [V1[0]] + [0] * (length - 1), [V2[0]] + [0] * (length - 1)
    for i in range(1, length):
        out1[i] = (V1[1] * out1[(i - 1) % N] + V1[2] * out2[(i - 1) % M] + V1[3]) % V1[4]
        out2[i] = (V2[1] * out1[(i - 1) % N] + V2[2] * out2[(i - 1) % M] + V2[3]) % V2[4]
    return out1[:N], out2[:M]

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        V1, V2 = [int(x) for x in input().split()], [int(x) for x in input().split()]
        B1, B2 = generate(V1, V2, N, M)
        print(f'Case #{i + 1}: {solve(B1, B2)}')

run()
