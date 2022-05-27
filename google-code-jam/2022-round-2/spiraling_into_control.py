#!/usr/bin/python

def solve(N, K):
    if K < N - 1:
        return 'IMPOSSIBLE'
    x, y = N, 5 * N - 6
    D = {4 * N - 6: (1, 4 * N - 4), y - x - 2: (x + 1, y)}
    for skip in range(N - 1, 1, -1):
        for _ in range(2):
            x, y = x + skip, y + skip - 2
            D[y - x - 2] = (x + 1, y)
    del D[0]

    position, gain, L = 1, N * N - 1 - K, []
    for d in D.items():
        if d[1][0] >= position and d[0] <= gain:
            position, gain = d[1][1], gain - d[0]
            L.append(d[1])
    if gain > 0:
        return 'IMPOSSIBLE'
    return '{}\n'.format(len(L)) + '\n'.join(' '.join(str(x) for x in p) for p in L)

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, K)))

run()
