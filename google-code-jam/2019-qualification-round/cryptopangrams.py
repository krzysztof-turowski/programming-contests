#!/usr/bin/python

def gcd(x, y):
    while(y):
        x, y = y, x % y
    return x

def solve(V):
    T = [0] * (len(V) + 1)
    for i in range(len(V) - 1):
        if V[i] != V[i + 1]:
            T[i + 1] = gcd(V[i], V[i + 1])
            for j in range(i, -1, -1):
                T[j] = V[j] // T[j + 1]
            for j in range(i + 2, len(T)):
                T[j] = V[j - 1] // T[j - 1]
            break
    L = {value:chr(letter) for value, letter in zip(sorted(set(T)), range(ord('A'), ord('Z') + 1))}
    return ''.join([L[t] for t in T])

def run():
    T = int(input())
    for i in range(T):
        _, _ = [int(x) for x in input().split()]
        V = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(V)))

run()
