#!/usr/bin/python

import collections
import heapq
import queue

Card = collections.namedtuple('Card', 'cards score turns')
Vertex = collections.namedtuple('Vertex', 'played turns t c1 c2')

def add_vertex(G, Q, v):
    if v not in G:
        Q.put(v)
        G[v] = []
    return G, Q

def build_graph(played, deck):
    T = [i for i, c in enumerate(deck) if c.turns > 0]
    C1 = [i for i, c in enumerate(deck) if c.turns == 0 and c.cards == 1]
    C2 = [i for i, c in enumerate(deck) if c.turns == 0 and c.cards == 2]
    start = Vertex(played, 1, 0, 0, 0)
    G, Q = {start: []}, queue.Queue()
    Q.put(start)
    while not Q.empty():
        v = Q.get()
        if v.turns == 0:
            continue
        if v.t < len(T) and T[v.t] < v.played:
            card = deck[T[v.t]]
            u_t = Vertex(
                min(len(deck), v.played + card.cards),
                min(len(deck), v.turns + card.turns - 1),
                v.t + 1, v.c1, v.c2)
            G[v].append((u_t, card.score))
            G, Q = add_vertex(G, Q, u_t)
        if v.c1 < len(C1) and C1[v.c1] < v.played:
            u_c1 = Vertex(
                min(len(deck), v.played + 1), v.turns - 1, v.t, v.c1 + 1, v.c2)
            G[v].append((u_c1, deck[C1[v.c1]].score))
            G, Q = add_vertex(G, Q, u_c1)
            u_c1_discard = Vertex(v.played, v.turns, v.t, v.c1 + 1, v.c2)
            G[v].append((u_c1_discard, 0))
            G, Q = add_vertex(G, Q, u_c1_discard)
        if v.c2 < len(C2) and C2[v.c2] < v.played:
            u_c2 = Vertex(
                min(len(deck), v.played + 2), v.turns - 1, v.t, v.c1, v.c2 + 1)
            G[v].append((u_c2, deck[C2[v.c2]].score))
            G, Q = add_vertex(G, Q, u_c2)
            u_c2_discard = Vertex(v.played, v.turns, v.t, v.c1, v.c2 + 1)
            G[v].append((u_c2_discard, 0))
            G, Q = add_vertex(G, Q, u_c2_discard)
    return G

def topological_sort(G):
    indegree = collections.defaultdict(int)
    for v in G:
        for u, _ in G[v]:
            indegree[u] += 1
    S, L = {v for v in G if indegree[v] == 0}, []
    while S:
        v = S.pop()
        L.append(v)
        for u, _ in G[v]:
            indegree[u] -= 1
            if indegree[u] == 0:
                S.add(u)
    return L

def longest_path(G, deck):
    L = topological_sort(G)
    C0 = [c.score if c.turns == 0 and c.cards == 0 else 0 for c in deck]
    score, out = {v: 0 for v in L}, 0
    for v in L:
        out = max(out, score[v] + sum(heapq.nlargest(v.turns, C0[:v.played])))
        for u, w in G[v]:
            score[u] = max(score[u], score[v] + w)
    return out

def solve(hand, deck):
    return longest_path(build_graph(len(hand), hand + deck), hand + deck)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        hand = [Card(*(int(x) for x in input().split())) for _ in range(N)]
        M = int(input())
        deck = [Card(*(int(x) for x in input().split())) for _ in range(M)]
        print('Case #{0}: {1}'.format(i + 1, solve(hand, deck)))

run()
