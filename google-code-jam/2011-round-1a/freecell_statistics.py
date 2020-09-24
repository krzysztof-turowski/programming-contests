#!/usr/bin/python

def solve(N, PD, PG):
    if (PD < 100 and PG == 100) or (PD > 0 and PG == 0):
        return 'Broken'
    return next(
        ('Possible' for D in range(1, N + 1) if D * PD % 100 == 0), 'Broken')

def run():
    T = int(input())
    for i in range(T):
        N, PD, PG = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, PD, PG)))

run()
