#!/usr/bin/python

def get_tidy(N):
    out = list(str(N))
    for i in range(len(out) - 1):
        if out[i] > out[i + 1]:
            for j in range(i + 1, len(out)):
                out[j] = out[i]
            break
    return int(''.join(out))

def binary_search(N):
    low, high = 0, N + 1
    while low + 1 != high:
        mid = (high + low) // 2
        if get_tidy(mid) > N:
            high = mid
        else:
            low = mid
    return low

def run():
    T = int(input())
    for t in range(T):
        N = int(input())
        print("Case #{0}: {1}".format(t + 1, binary_search(N)))

run()
