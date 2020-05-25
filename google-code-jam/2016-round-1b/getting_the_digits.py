#!/usr/bin/python

from collections import defaultdict

def solve(S):
    names = [
        'ZERO', 'ONE', 'TWO', 'THREE', 'FOUR', 'FIVE', 'SIX',
        'SEVEN', 'EIGHT', 'NINE'
    ]
    order = [
        { 'Z': 0, 'W': 2, 'U': 4, 'X': 6, 'G': 8 },
        { 'O': 1, 'T': 3, 'F': 5, 'S': 7 },
        { 'I': 9 }
    ]
    A, out = defaultdict(int), ''
    for letter in S:
        A[letter] += 1
    for row in order:
        for letter, index in row.items():
            if letter in A:
                value = A[letter]
                out += ''.join(str(index) * value)
                for other in names[index]:
                    A[other] -= value
                del A[letter]
    return ''.join(sorted(out))

def run():
    T = int(input())
    for i in range(T):
        S = input().strip()
        print('Case #{0}: {1}'.format(i + 1, solve(S)))

run()
