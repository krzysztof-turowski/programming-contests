#!/usr/bin/python3

def solve(M, R, T):
    out = []
    for c in T:
        out.append(c)
        while len(out) > 1 and (out[-1], out[-2]) in M:
            out[-2:] = M[(out[-1], out[-2])]
        for v in out[:-1]:
            if (v, out[-1]) in R:
                out = []
                break
    return '[' + ', '.join(out) + ']'

def run():
    T = int(input())
    for i in range(T):
        L = input().split()
        C, merge = int(L[0]), {}
        for v in L[1:C + 1]:
            merge[(v[0], v[1])] = v[2]
            merge[(v[1], v[0])] = v[2]
        D, replace = int(L[C + 1]), set()
        for v in L[C + 2:C + D + 2]:
            replace.add((v[0], v[1]))
            replace.add((v[1], v[0]))
        print('Case #{0}: {1}'.format(i + 1, solve(merge, replace, L[-1])))

run()
