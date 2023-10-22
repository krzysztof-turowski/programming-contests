#!/usr/bin/python3

MAX = 41

def solve(P):
    divisors = []
    for i in range(2, MAX + 1):
        while P % i == 0:
            P //= i
            divisors.append(i)
    if P > 1 or sum(divisors) > 41:
        return -1
    divisors.extend([1] * (MAX - sum(divisors)))
    return str(len(divisors)) + ' ' + ' '.join(str(x) for x in sorted(divisors))

def run():
    T = int(input())
    for i in range(T):
        print(f'Case #{i + 1}: {solve(int(input()))}')

run()
