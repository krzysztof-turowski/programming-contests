#!/usr/bin/python3

def solve(S):
    visited, out = {S[0]}, [S[0]]
    for a, b in zip(S, S[1:]):
        if a == b:
            continue
        if b in visited:
            return 'IMPOSSIBLE'
        visited.add(b)
        out.append(b)
    return ' '.join(str(x) for x in out)

def run():
    T = int(input())
    for i in range(T):
        _ = input()
        S = [int(x) for x in input().split()]
        print(f'Case #{i + 1}: {solve(S)}')

run()
