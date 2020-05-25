#!/usr/bin/python

def match(t, words):
    if not t.startswith(words[0]):
        return False
    if not t[::-1].startswith(words[-1][::-1]):
        return False
    t = t[len(words[0]):len(t) - len(words[-1])]
    for w in words[1:-1]:
        index = t.find(w)
        if index == -1 or index + len(w) > len(t):
            return False
        t = t[index + len(w):]
    return True

def merge(t, w):
    if t.startswith(w):
        return t, True
    if w.startswith(t):
        return w, True
    return None, False

def solve(M):
    M = sorted(M, key = len)
    if len(M[0]) == 1:
        for words in M:
            if not match(M[0][0], words):
                return '*'
        return M[0][0]
    start, end = '', ''
    for words in M:
        start, possible_start = merge(start, words[0])
        end, possible_end = merge(end, words[-1][::-1])
        if not possible_start or not possible_end:
            return '*'
    return start + ''.join(''.join(words[1:-1]) for words in M) + end[::-1]

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        M = [input().strip().split('*') for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(M)))

run()
