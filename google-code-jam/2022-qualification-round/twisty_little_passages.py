#!/usr/bin/python

import math
import random
import sys

def read_input():
    return (int(x) for x in input().split())

def print_output(command):
    print(command)
    sys.stdout.flush()

def feige_parameters(N, K):
    def get_tries(v):
        return math.ceil(8 / v), math.ceil(math.sqrt(N) / v ** 2.5)
    low, high = 10 ** -4, 10 ** 1
    while high - low > 10 ** -4:
        mid = (low + high) / 2
        tries, size = get_tries(mid)
        if tries * size + 1 < K:
            high = mid
        else:
            low = mid
    tries, size = get_tries(high)
    return high, tries, size

def feige(N, K):
    _, tries, size = feige_parameters(N, K)
    D = [0] * tries
    for t in range(tries):
        v, D[t] = read_input()
        for i in range(size):
            print_output('T {0}'.format((v + i) % N + 1))
            _, du = read_input()
            D[t] += du
        if t == tries - 1:
            break
        print_output('T {0}'.format(random.randint(1, N)))
    print_output('E {0}'.format(min(math.ceil(d * N / (2 * size)) for d in D)))

def goldreich_parameters(N, K):
    def get_tries(v):
        return math.ceil(
            math.sqrt(N) * (math.log(N, 2) ** 2) * (v ** -5) * -math.log(v, 2))
    low, high = 0.5, 1 - 10 ** -4
    while high - low > 10 ** -4:
        mid = (low + high) / 2
        tries = get_tries(mid)
        if tries + 1 < K // 2:
            high = mid
        else:
            low = mid
    return high, get_tries(high)

def goldreich(N, K):
    eps, K = goldreich_parameters(N, K)
    beta = eps / 20
    t = math.ceil(math.log(N, 1 + beta)) + 1
    S = [[] for _ in range(t)]
    for i in range(K):
        v, dv = read_input()
        S[math.ceil(math.log(dv, 1 + beta))].append(v)
        if i == K - 1:
            break
        print_output('T {0}'.format(random.randint(1, N)))
    L = {i for i, s in enumerate(S)
         if len(s) >= K / t * math.sqrt(eps / (6 * N))}
    out = 0
    for i in L:
        alpha = 0
        for v in S[i]:
            print_output('W')
            _, du = read_input()
            level = math.ceil(math.log(du, 1 + beta))
            if level not in L:
                alpha += 1
        out += (alpha + len(S[i])) * (1 + beta) ** i
    print_output('E {0}'.format(math.ceil(out * N / (2 * K))))

def solve(N, K):
    goldreich(N, K)

def run():
    T = int(input())
    for _ in range(T):
        N, K = read_input()
        solve(N, K)

run()
