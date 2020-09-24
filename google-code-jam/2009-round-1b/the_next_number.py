#!/usr/bin/python

def solve(N):
    Ns = [int(x) for x in list(str(N))]
    maximum = 0
    for i in range(len(Ns) - 1, -1, -1):
        if Ns[i] < maximum:
            greater = min(v for v in Ns[i:] if v > Ns[i])
            index = i + Ns[i:].index(greater)
            return (''.join(str(v) for v in Ns[:i]) + str(greater)
                    + ''.join(str(v) for v in sorted(
                        Ns[i:index] + Ns[index + 1:])))
        maximum = max(maximum, Ns[i])
    if min(Ns) <= 1:
        index = i + Ns.index(1)
        return '10' + ''.join(str(v) for v in sorted(
            Ns[:index] + Ns[index + 1:]))
    return '1' + ''.join(str(v) for v in sorted(Ns))

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        print('Case #{0}: {1}'.format(i + 1, solve(N)))

run()
