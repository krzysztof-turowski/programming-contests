#!/usr/bin/python3

def solve(I, O, N):
    out = [['N' for _ in range(N)] for _ in range(N)]
    for i in range(N):
        out[i][i] = 'Y'
    for i in range(1, N):
        for j in range(N):
            if (j + i < N and out[j][j + i - 1] == 'Y'
                    and O[j + i - 1] == 'Y' and I[j + i] == 'Y'):
                out[j][j + i] = 'Y'
            if (j - i >= 0 and out[j][j - i + 1] == 'Y'
                    and O[j - i + 1] == 'Y' and I[j - i] == 'Y'):
                out[j][j - i] = 'Y'
    return '\n'.join(''.join(row) for row in out)

def run():
    T = int(input())
    for i in range(T):
        _, I, O = int(input()), input().strip(), input().strip()
        print('Case #{0}: \n{1}'.format(i + 1, solve(I, O, len(I))))

run()
