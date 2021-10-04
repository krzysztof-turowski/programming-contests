#!/usr/bin/python

def build(start, count):
    if count < 2 or start == '':
        return None
    return ''.join(str(start + i) for i in range(count))

def solve(N):
    out, L = [], len(N)
    for K in range(1, L // 2 + 2):
        if L / K <= 9:
            out.append(build(int(N[:K]), L // K))
            out.append(build(int(N[:K]) + 1, L // K))
        out += [
            build(int('1' + '0' * (K - 1)), count)
            for count in range((L + 1) // (K + 1), (L + 1) // K + 2)]
        out += [
            build(int('9' * (K - 1) + str(D)), count)
            for count in range(L // (K + 1), L // K + 2) for D in range(10)]
    return min(int(v) for v in out if v is not None and int(v) > int(N))

def run():
    T = int(input())
    for i in range(T):
        print('Case #{0}: {1}'.format(i + 1, solve(input().strip())))

run()
