#!/usr/bin/python3

def solve(S, R, T, W):
    out = 0
    for i, w in enumerate(W):
        if T == 0:
            out += w[0] / (w[1] + S)
        elif W[i][0] <= T * (R + w[1]):
            time = w[0] / (w[1] + R)
            out, T = out + time, T - time
        else:
            out, T = out + T + (w[0] - T * (R + w[1])) / (w[1] + S), 0
    return out

def run():
    T = int(input())
    for i in range(T):
        X, S, R, t, N = (int(x) for x in input().split())
        W = [(w[1] - w[0], w[2])
             for w in ((tuple(int(x) for x in input().split())) for _ in range(N))]
        W.append((X - sum(w[0] for w in W), 0))
        W.sort(key = lambda x: x[1])
        print('Case #{0}: {1:.9f}'.format(i + 1, solve(S, R, t, W)))

run()
