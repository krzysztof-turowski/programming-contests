#!/usr/bin/python

def get_maximum(word, S):
    if len(word) > S:
        return 0
    suffix = len(word)
    for i in range(1, len(word)):
        if word[i:] == word[:-i]:
            suffix = i
            break
    return 1 + (S - len(word)) // suffix

def get_average(word, A, S):
    out = S - len(word) + 1
    for letter in word:
        out *= A[letter]
    return out

def solve(S, word, alphabet, K):
    A = {}
    for letter in alphabet:
        A[letter] = sum(x == letter for x in sorted(alphabet)) / K
    for letter in word:
        if not letter in A:
            return 0
    return get_maximum(word, S) - get_average(word, A, S)

def run():
    T = int(input())
    for t in range(T):
        K, _, S = [int(x) for x in input().split()]
        alphabet, word = input().strip(), input().strip()
        print('Case #{0}: {1:6f}'.format(t + 1, solve(S, word, alphabet, K)))

run()
