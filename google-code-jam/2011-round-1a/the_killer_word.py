#!/usr/bin/python

import collections

def get_words(W, L, index, pattern):
    def match(a, b):
        for u, v in zip(a, b):
            if u in L[index + 1:] and v != '-':
                return False
            if u in L[:index + 1] and u != v:
                return False
        return True

    if len(W) == 1:
        return 0, W[0]
    contains = [w for w in W if L[index] in w]
    if contains:
        score, out = 1, None
        other = [w for w in W if L[index] not in w]
        if other:
            value = get_words(other, L, index + 1, pattern)
            score, out = value[0] - 1, value[1]
        next_patterns = {
            ''.join(c if c == L[index] else p for c, p in zip(w, pattern))
            for w in contains}
        for next_pattern in next_patterns:
            next_words = [w for w in W if match(w, next_pattern)]
            value = get_words(next_words, L, index + 1, next_pattern)
            if value[0] < score:
                score, out = value[0], value[1]
            elif value[0] == score and W.index(value[1]) < W.index(out):
                out = value[1]
        return score, out
    return get_words(W, L, index + 1, pattern)

def solve(W, L):
    D = collections.defaultdict(list)
    for w in W:
        D[len(w)].append(w)
    out = [min((get_words(words, line, 0, '-' * k) for k, words in D.items()),
               key = lambda x: (x[0], W.index(x[1])))
           for line in L]
    return ' '.join(v[1] for v in out)

def run():
    T = int(input())
    for i in range(T):
        N, M = (int(x) for x in input().split())
        W, L = [input() for _ in range(N)], [input() for _ in range(M)]
        print('Case #{0}: {1}'.format(i + 1, solve(W, L)))

run()
