#!/usr/bin/python3

import collections
import copy

def apply(A, B, C, i, k):
    if B[k - i] >= 0 and C[i] >= 0:
        A[k] = max(A[k], B[k - i] + C[i])

def compute_costs(v, parent, G, C, MAX):
    single, none = [C[v - 1]] * MAX, [0] * MAX
    even, odd = [-1] * MAX, [-1] * MAX
    for u in G[v]:
        if u == parent:
            continue
        not_taken, with_edge, without_edge = compute_costs(u, v, G, C, MAX)
        prev_single, prev_none = copy.deepcopy(single), copy.deepcopy(none)
        prev_even, prev_odd = copy.deepcopy(even), copy.deepcopy(odd)
        for k in range(MAX - 1, -1, -1):
            for i in range(k + 1):
                apply(none, prev_none, not_taken, i, k)
                apply(none, prev_none, without_edge, i, k)
                apply(single, prev_single, not_taken, i, k)
                apply(single, prev_single, without_edge, i, k)
                apply(odd, prev_odd, not_taken, i, k)
                apply(odd, prev_odd, without_edge, i, k)
                apply(odd, prev_even, with_edge, i, k)
                apply(odd, prev_single, with_edge, i, k)
                apply(even, prev_even, not_taken, i, k)
                apply(even, prev_even, without_edge, i, k)
                apply(even, prev_odd, with_edge, i, k)
    for k in range(MAX - 1, 0, -1):
        odd[k] = max(odd[k], even[k - 1], single[k - 1])
        even[k] = max(even[k], odd[k - 1], (single[k - 2] if k > 1 else -1))
    return none, odd, even

def solve(G, C, K):
    if K == 0:
        return C[0]
    return compute_costs(1, None, G, C, 2 * K + 1)[2][2 * K]

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        C = [int(x) for x in input().split()]
        G = collections.defaultdict(list)
        for _ in range(1, N):
            u, v = (int(x) for x in input().split())
            G[u].append(v)
            G[v].append(u)
        print('Case #{0}: {1}'.format(i + 1, solve(G, C, K)))

run()
