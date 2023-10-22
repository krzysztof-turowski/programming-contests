#!/usr/bin/python3

def check(p1, p2, p3, A):
    x1, y1, x2, y2, x3, y3 = *p1, *p2, *p3
    x, y = max(x1, x2, x3) - min(x1, x2, x3), max(y1, y2, y3) - min(y1, y2, y3)
    assert 2 * x * y == A + (
        (x2 - x1) * (y2 - y1) + (x3 - x1) * (y3 - y1) + (x2 - x3) * (y3 - y2))

def solve(N, M, A):
    if A > M * N:
        return 'IMPOSSIBLE'
    if A == M * N:
        return ' '.join(str(x) for x in (0, 0, N, 0, 0, M))
    x, y = (N - A % N) % N, (A + N - 1) // N
    check((0, 0), (N, 1), (x, y), A)
    return ' '.join(str(x) for x in (0, 0, N, 1, x, y))

def run():
    T = int(input())
    for i in range(T):
        N, M, A = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, M, A)))

run()
