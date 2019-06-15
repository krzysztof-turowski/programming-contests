#!/usr/bin/python

def solve(N):
    if len(N) == 1:
        return int(''.join(N))
    half = (len(N) + 1) // 2
    left, right = N[0:half], N[half:]
    right_value = int(''.join(right))
    if right_value == 0:
        right_value = 10 ** len(right)
        left = list(str(int(''.join(left)) - 1))
    flip = right_value + int(''.join(list(reversed(left)))) + 1
    N[0] = chr(ord(N[0]) - 1)
    no_flip = int(''.join(N)) + 1
    return min(flip, no_flip) + solve(['9'] * (len(N) - 1))

def run():
    T = int(input())
    for i in range(T):
        N = input().strip()
        print('Case #{0}: {1}'.format(i + 1, solve(list(N))))

run()
