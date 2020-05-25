#!/usr/bin/python

def check(X, Y, out):
    x, y = 0, 0
    for i, c in enumerate(out):
        if c == 'N':
            y += 2 ** i
        elif c == 'S':
            y -= 2 ** i
        elif c == 'E':
            x += 2 ** i
        elif c == 'W':
            x -= 2 ** i
    assert X == x
    assert Y == y

def solve(X, Y):
    def half(x):
        return x // 2 if x > 0 else (x + (-x % 2)) // 2
    def reverse(c):
        M = {'S': 'N', 'N': 'S', 'W': 'E', 'E': 'W'}
        return M[c]
    out, X_out, Y_out = '', X, Y
    while X_out != 0 or Y_out != 0:
        if (X_out + Y_out) % 2 == 0:
            return 'IMPOSSIBLE'
        if X_out % 2 != 0:
            out += 'E' if X_out > 0 else 'W'
        else:
            out += 'N' if Y_out > 0 else 'S'
        X_out, Y_out = half(X_out), half(Y_out)
        if (X_out != 0 or Y_out != 0) and (X_out + Y_out) % 2 == 0:
            if out[-1] in ['E', 'W']:
                X_out = X_out + 1 if out[-1] == 'E' else X_out - 1
            else:
                Y_out = Y_out + 1 if out[-1] == 'N' else Y_out - 1
            out = out[:-1] + reverse(out[-1])
    check(X, Y, out)
    return out


def run():
    T = int(input())
    for i in range(T):
        X, Y = [int(x) for x in input().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(X, Y)))

run()
