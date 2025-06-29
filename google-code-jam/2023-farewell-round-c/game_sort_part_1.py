#!/usr/bin/python

import collections

def decrease(D, c):
    D[c] -= 1
    if D[c] == 0:
        del D[c]

def find_next_best_word(word, D):
    out = []
    for j, c in enumerate(word):
        if not D or max(D) < c:
            break
        best = min((a for a in D if a > c), default = None)
        if best is not None:
            decrease(D, best)
            out.append(word[:j] + best + ''.join(sorted(a * k for a, k in D.items())))
            D[best] = D.get(best, 0) + 1
        if c in D:
            decrease(D, c)
        else:
            break
    else:
        out.append(word + ''.join(sorted(a * k for a, k in D.items())))
    return min(out) if out else None

def solve(S):
    D = [collections.Counter(s) for s in S]
    word = ''.join(sorted(S[0]))
    L = [word]
    for i in range(1, len(S)):
        word = find_next_best_word(word, dict(D[i].items()))
        if word is None:
            return 'IMPOSSIBLE'
        L.append(word)
    return f'POSSIBLE\n{" ".join(L)}'

def run():
    T = int(input())
    for i in range(T):
        _ = int(input())
        print(f'Case #{i + 1}: {solve(input().strip().split())}')

run()
