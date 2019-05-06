#!/usr/bin/python

MOD = 2 * 3 * 5 * 7

def solve(D):
    values = []
    for index, _ in enumerate(D):
        v = sum((10 ** offset) * int(value) for offset, value in enumerate(D[index::-1]))
        values.append({v % MOD: 1})
        for i in range(index):
            v = sum((10 ** offset) * int(value) for offset, value in enumerate(D[index:i:-1]))
            for key, value in values[i].items():
                values[index][(key + v) % MOD] = values[index].get((key + v) % MOD, 0) + value
                values[index][(key - v) % MOD] = values[index].get((key - v) % MOD, 0) + value
    return sum(value for key, value in values[-1].items()
               if key % 2 == 0 or key % 3 == 0 or key % 5 == 0 or key % 7 == 0)

def run():
    T = int(input())
    for t in range(T):
        D = input().strip()
        print("Case #{0}: {1}".format(t + 1, solve(D)))

run()
