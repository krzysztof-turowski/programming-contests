#!/usr/bin/python

def find(L):
    for j, y in enumerate(L[1:]):
        if y == L[j]:
            continue
        for k, z in enumerate(L[j + 2:]):
            if (z != L[j + k + 1] and z == L[j] and L[0] == L[j + k + 1]):
                return j + 1, k + 1, True
    return None, None, False

def fix(L):
    a = min(i for i, x in enumerate(L) if x != L[0])
    return a, len(L) - a

def solve(R, S):
    L = [r for _ in range(S) for r in range(1, R + 1)]
    out = []
    while True:
        a, b, found = find(L)
        if not found:
            break
        L = L[a:a + b] + L[0:a] + L[a + b:]
        # print(L, a, b)
        out.append((a, b))
    if L[0] != 1:
        a, b = fix(L)
        L = L[a:a + b] + L[0:a] + L[a + b:]
        # print(L, a, b)
        out.append((a, b))
    return str(len(out)) + '\n' + '\n'.join(
        str(a) + ' ' + str(b) for a, b in out)

def run():
    T = int(input())
    for i in range(T):
        R, S = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(R, S)))

run()
