#!/usr/bin/python3

VOWELS = {"A", "E", "I", "O", "U"}

def check(s, c):
    if s == c:
        return 0
    return 2 if (s in VOWELS) == (c in VOWELS) else 1

def solve(S):
    return min(sum(check(s, chr(c)) for s in S)
               for c in range(ord('A'), ord('Z') + 1))

def run():
    T = int(input())
    for i in range(T):
        S = input().strip()
        print('Case #{0}: {1}'.format(i + 1, solve(S)))

run()
