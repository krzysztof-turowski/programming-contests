#!/usr/bin/python3

def solve(R, C):
    return 'YES' if R > C else 'NO'

def run():
    T = int(input())
    for i in range(T):
        R, C, _, _ = (int(x) for x in input().split())
        print(f'Case #{i + 1}: {solve(R, C)}')

run()
