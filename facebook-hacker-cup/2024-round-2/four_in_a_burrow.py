#!/usr/bin/python

import collections

DIRECTIONS = [(1, 1), (0, 1), (1, 0), (-1, 1)]

def find_line(A, s, i, move):
    for d in DIRECTIONS:
        left, right = 0, 0
        for v in range(1, 4):
            x, y = s[i] - 1 + v * d[0], i + v * d[1]
            if 0 <= y <= 6 and 0 <= x < s[y] and A[x][y] == move:
                left += 1
            else:
                break
        for v in range(1, 4):
            x, y = s[i] - 1 - v * d[0], i - v * d[1]
            if 0 <= y <= 6 and 0 <= x < s[y] and A[x][y] == move:
                right += 1
            else:
                break
        if left + right + 1 >= 4:
            return True
    return False

def test_finish(A, s, i, move):
    return all(x == 6 for x in s)

def dfs(A, q_start, test, fast):
    state = []
    Q, processed = collections.deque([q_start]), set()
    while Q:
        q = Q.popleft()
        if q in processed:
            continue
        v = 'F' if sum(q) % 2 else 'C'
        for i in range(7):
            if q[i] == 6 or A[q[i]][i] != v:
                continue
            q_prim = list(q)
            q_prim[i] += 1
            if test(A, q_prim, i, v):
                state.append((v, tuple(q_prim)))
                if fast:
                    return state
            else:
                Q.append(tuple(q_prim))
        processed.add(q)
    return state

def solve(A):
    possible_wins, wins = dfs(A, (0,) * 7, find_line, False), set()
    for v_start, q_start in possible_wins:
        if v_start not in wins and dfs(A, q_start, test_finish, True):
            wins.add(v_start)
            if len(wins) == 2:
                return '?'
    return min(wins) if len(wins) == 1 else '0'


def run():
    T = int(input())
    for i in range(T):
        _ = input()
        A = list(reversed([input().strip() for _ in range(6)]))
        print(f'Case #{i + 1}: {solve(A)}')

run()
