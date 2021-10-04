#!/usr/bin/python3

import collections
import itertools
import random

TINY, SMALL, LARGE = 25, 100, 2000

def find_collision(L, indices):
    lists = {}
    for d in range(1, len(indices) + 1):
        for s in itertools.combinations(indices, d):
            total = sum(L[e] for e in s)
            if total in lists:
                return True, list(s), list(lists[total])
            lists[total] = s
    return False, None, None

def solve_tiny(L, indices, K):
    A, B = [], []
    while len(indices) > K:
        _, A_tiny, B_tiny = find_collision(L, list(indices)[:TINY])
        A, B = A + A_tiny, B + B_tiny
        indices -= set(A_tiny + B_tiny)
    return A, B

def solve_small(L, indices, K):
    def random_subset(S):
        return set(filter(lambda x: random.randrange(2), S))
    A, B, lists = [], [], {}
    while len(indices) > max(K, SMALL):
        s = random_subset(indices)
        total = sum(L[e] for e in s)
        if total not in lists:
            lists[total] = s
            continue
        if lists[total] == s:
            continue
        product = lists[total].intersection(s)
        A_small, B_small = list(lists[total] - product), list(s - product)
        lists.clear()
        indices -= set(A_small + B_small)
        A, B = A + A_small, B + B_small
    if len(indices) > K:
        A_tiny, B_tiny = solve_tiny(L, indices, K)
        A, B = A + A_tiny, B + B_tiny
    return A, B

def solve_large(L, indices, K):
    def remove(X, Y, to_remove):
        for index in to_remove:
            other_index = X[-1]
            if index != other_index:
                Y[index], Y[other_index] = Y[other_index], Y[index]
                X[Y[index]], X[Y[other_index]] = X[Y[other_index]], X[Y[index]]
            del Y[index]
            X.pop()
        return X, Y
    A, B = [], []
    pairs, reverse_indices = {}, {v: i for i, v in enumerate(indices)}
    while len(indices) > max(K, LARGE):
        a, b = sorted(random.sample(indices, k = 2))
        total = L[a] + L[b]
        if total not in pairs:
            pairs[total] = (a, b)
            continue
        if pairs[total] == (a, b):
            continue
        c, d = pairs[total]
        if c not in reverse_indices or d not in reverse_indices:
            pairs[total] = (a, b)
            continue
        A, B = A + [a, b], B + [c, d]
        indices, reverse_indices = remove(indices, reverse_indices, [a, b, c, d])
    if len(indices) > K:
        A_small, B_small = solve_small(L, set(indices), K)
        A, B = A + A_small, B + B_small
    return A, B

def remove_duplicates(L):
    D = collections.defaultdict(list)
    for i, k in enumerate(L):
        D[k].append(i)
    A, B, indices = [], [], []
    for k, v in D.items():
        for a, b in zip(v[::2], v[1::2]):
            A.append(a)
            B.append(b)
        if len(v) % 2 != 0:
            indices.append(v[-1])
    return A, B, indices

def solve(L, K):
    if len(L) < TINY:
        found, A, B = find_collision(L, list(range(len(L))))
        if not found:
            return 'Impossible'
        return '\n'.join(
            ('Possible', ' '.join(str(e + 1) for e in A), ' '.join(str(e + 1) for e in B)))
    A, B, indices = remove_duplicates(L)
    if len(indices) > K:
        A_large, B_large = solve_large(L, indices, K)
        A, B = A + A_large, B + B_large
    return '\n'.join(
        ('Possible', ' '.join(str(e + 1) for e in A), ' '.join(str(e + 1) for e in B)))

def run():
    T = int(input())
    for i in range(T):
        _, K = (int(x) for x in input().split())
        L = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(L, K)))

run()
