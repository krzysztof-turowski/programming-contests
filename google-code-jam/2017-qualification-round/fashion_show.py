#!/usr/bin/python

def rooks(P, N):
    R, C = set(), set()
    for i in range(N):
        for j in range(N):
            if P[i][j] != '.':
                R.add(i)
                C.add(j)
    R = [i for i in range(N) if i not in R]
    C = [i for i in range(N) if i not in C]
    for i, j in zip(R, C):
        P[i][j] = 'x'
    return P

def bishops(P, N):
    def get_range(x):
        return (range(-x, x + 1, 2) if x < N
                else range(x - 2 * N + 2, 2 * N - x - 1, 2))
    R, C = set(), set()
    for i in range(2 * N - 1):
        for j in range(N):
            if 0 <= i - j <= N - 1 and P[j][i - j] != '.':
                R.add(i)
                C.add(2 * j - i)
    E = {i: set(x for x in get_range(i) if x not in C)
         for i in range(2 * N - 1) if i not in R}
    while len(E) > 0:
        i, v = min(E.items(), key = lambda x: len(x[1]))
        del E[i]
        if not v:
            continue
        j = min(v)
        P[(i + j) // 2][(i - j) // 2] = '+'
        for e in E:
            E[e] -= {j}
    return P

def solve(P, N):
    R, B = [['.'] * N for _ in range(N)], [['.'] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if P[i][j] == 'o':
                B[i][j], R[i][j] = 'x', '+'
            elif P[i][j] == '+':
                B[i][j] = '+'
            if P[i][j] == 'x':
                R[i][j] = 'x'
    R, B = rooks(R, N), bishops(B, N)
    score, out = 0, []
    for i in range(N):
        for j in range(N):
            score += (R[i][j] != '.') + (B[i][j] != '.')
            if R[i][j] != '.' and B[i][j] != '.' and P[i][j] != 'o':
                out.append(('o', i + 1, j + 1))
            elif R[i][j] != '.' and P[i][j] == '.':
                out.append(('x', i + 1, j + 1))
            elif B[i][j] != '.' and P[i][j] == '.':
                out.append(('+', i + 1, j + 1))
    return ('{0} {1}'.format(score, len(out))
            + ('\n' if len(out) > 0 else '')
            + '\n'.join(' '.join(str(x) for x in row) for row in out))

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        P = [['.'] * N for _ in range(N)]
        for _ in range(M):
            t, r, c = input().split()
            P[int(r) - 1][int(c) - 1] = t
        print('Case #{0}: {1}'.format(i + 1, solve(P, N)))

run()
