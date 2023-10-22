#!/usr/bin/python3

SHIFT = 5
INF = 10 ** 4

def solve(S, D, L):
    A = {v : { 0 : 0 } for v in range(SHIFT)}
    for i, _ in enumerate(S):
        for length in range(1, L + 1):
            if i + length > len(S):
                continue
            for v in range(SHIFT):
                if (i + length) not in A[v]:
                    A[v][i + length] = INF
            if S[i:i + length] in D:
                for v in range(SHIFT):
                    A[max(v - length, 0)][i + length] = min(
                        A[v][i], A[max(v - length, 0)][i + length])
            for first_wildcard in range(length):
                W = list(S[i:i + length])
                W[first_wildcard] = '*'
                if ''.join(W) in D:
                    v = max(0, first_wildcard + SHIFT - length)
                    for w in range(v, SHIFT):
                        A[w][i + length] = min(
                            min(A[x][i] for x in range(min(SHIFT, first_wildcard + 1))) + 1,
                            A[w][i + length])
            for second_wildcard in range(length):
                if second_wildcard < SHIFT:
                    continue
                for first_wildcard in range(second_wildcard - SHIFT + 1):
                    W = list(S[i:i + length])
                    W[first_wildcard], W[second_wildcard] = '*', '*'
                    if ''.join(W) in D:
                        v = max(0, second_wildcard + SHIFT - length)
                        for w in range(v, SHIFT):
                            A[w][i + length] = min(
                                min(A[x][i] for x in range(min(SHIFT, first_wildcard + 1))) + 2,
                                A[w][i + length])
    return min(A[x][len(S)] for x in range(SHIFT))

def get_dictionary():
    D, L = set(), 0
    with open('garbled_email_dictionary.txt') as dictionary:
        for line in dictionary.readlines():
            word = list(line.strip())
            D.add(''.join(word))
            L = max(L, len(word))
            for i, _ in enumerate(word):
                first_word = [c if index != i else '*' for index, c in enumerate(word)]
                D.add(''.join(first_word))
                for j in range(i + SHIFT, len(word)):
                    second_word = [c if index != j else '*' for index, c in enumerate(first_word)]
                    D.add(''.join(second_word))
    return D, L

def run():
    D, L = get_dictionary()
    T = int(input())
    for t in range(T):
        print("Case #{0}: {1}".format(t + 1, solve(input().strip(), D, L)))

run()
