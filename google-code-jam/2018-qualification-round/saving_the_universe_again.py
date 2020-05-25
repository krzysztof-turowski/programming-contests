#!/usr/bin/python

def find_last_move(Id):
    for i in range(len(Id) - 1, 0, -1):
        if Id[i] > 1:
            return i
    return 0

def move_all_max(Id, index):
    return evaluate([1 if i == index else x for (i, x) in zip(range(len(Id)), Id)])

def move_all_once(Id, index):
    return evaluate([x - 1 if i == index else x for (i, x) in zip(range(len(Id)), Id)])

def move_one(Id, index):
    return evaluate([x - 1 if i == index else (x + 1 if i == index + 1 else x)
                     for (i, x) in zip(range(len(Id)), Id)])

def evaluate(Id):
    return sum([2 ** (sum(Id[:(index + 1)]) - index - 1) for index in range(len(Id))])

def solve(P, D):
    I = [index for (index, value) in zip(range(len(P)), P) if value == 'S']
    if not I:
        return 0
    Id = [I[0] + 1] + [second - first for (first, second) in zip(I, I[1:])]
    S = 0
    if evaluate([1] * len(Id)) > D:
        return "IMPOSSIBLE"
    if evaluate(Id) <= D:
        return 0
    while True:
        index = find_last_move(Id)
        if move_all_max(Id, index) > D:
            S += (Id[index] - 1) * (len(Id) - index)
            Id[index] = 1 if index > 0 else 0
        elif move_all_once(Id, index) > D:
            S += (len(Id) - index)
            Id[index] -= 1
        elif move_one(Id, index) > D:
            S += 1
            Id[index] -= 1
            Id[index + 1] += 1
        else:
            return S + 1

def run():
    T = int(input())
    for t in range(T):
        D, P = input().split()
        print("Case #{0}: {1}".format(t + 1, solve(P, int(D))))

run()
