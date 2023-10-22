#!/usr/bin/python3

def solve(E, K):
    W1, W2 = sum(E), sum(a ** 2 for a in E)
    if W1 == 0:
        return 0 if W2 == 0 else 'IMPOSSIBLE'
    if (W2 - W1 ** 2) % (2 * W1) == 0:
        return (W2 - W1 ** 2) // (2 * W1)
    if K < 2:
        return 'IMPOSSIBLE'
    return '{} {}'.format(1 - W1, (W1 ** 2 + W2) // 2 - W1)

def run():
    T = int(input())
    for i in range(T):
        _, K = (int(x) for x in input().split())
        E = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(E, K)))

run()
