#!/usr/bin/python

def process(string):
    buffer = None
    for s in string:
        if s == ')':
            yield ''.join(buffer)
            buffer = None
        elif s == '(':
            buffer = []
        elif buffer is not None:
            buffer.append(s)
        else:
            yield s

def solve(string, token):
    for s, t in zip(string, token):
        if t not in s:
            return 0
    return 1

def run():
    _, D, T = (int(x) for x in input().split())
    tokens = [input() for _ in range(D)]
    for i in range(T):
        s = list(process(input()))
        print('Case #{0}: {1}'.format(
            i + 1, sum(solve(s, token) for token in tokens)))

run()
