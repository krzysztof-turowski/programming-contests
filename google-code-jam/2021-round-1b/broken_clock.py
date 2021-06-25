#!/usr/bin/python

import itertools

MIN, SEC, NANO = 60, 60, 10 ** 9
MAX = 12 * 3600 * 10 ** 9

def extended_gcd(a, b):
    if a == 0:
        return (0, 1)
    y, x = extended_gcd(b % a, a)
    return (x - (b // a) * y, y)

def invert(a):
    x, _ = extended_gcd(a, MAX)
    return x % MAX

def check(h, m, s):
    a, b, c = (m - h) % MAX, (s - h) % MAX, (s - m) % MAX
    na, nb = (a * invert(11)) % MAX, (b * invert(719)) % MAX
    return na if na == nb or (708 * na) % MAX == c else None

def solve(A):
    nanoseconds = next(
        check(h, m, s) for h, m, s in itertools.permutations(A)
        if check(h, m, s) is not None)
    hours = nanoseconds // (MIN * SEC * NANO)
    nanoseconds -= hours * (MIN * SEC * NANO)
    minutes = nanoseconds // (SEC * NANO)
    nanoseconds -= minutes * (SEC * NANO)
    seconds = nanoseconds // NANO
    nanoseconds -= seconds * NANO
    return hours, minutes, seconds, nanoseconds

def run():
    T = int(input())
    for i in range(T):
        A = [int(x) for x in input().split()]
        print('Case #{0}: {1} {2} {3} {4}'.format(i + 1, *solve(A)))

run()
