#!/usr/bin/python3

from decimal import Decimal

N = int(input())
for t in range(N):
    M, X, Y = [int(x) for x in input().split()]
    S = abs(X) + Y

    if M >= (S + 1) * (S + 2) / 2:
        p = 1.0
    elif M <= (S - 1) * S / 2 or (M < (S + 1) * (S + 2) / 2 and X == 0):
        p = 0.0
    else:
        M = M - (S - 1) * S / 2
        S = min(S, M)

        data = [1] + [0] * S
        for i in range(M):
            data = [1] + [x + y for x, y in zip(data[:-1], data[1:])]
        p = Decimal(sum(data[max(Y + 1, M - S):])) / Decimal(sum(data[M - S:]))
    print("Case #{0}: {1:.7f}".format(t + 1, p))
