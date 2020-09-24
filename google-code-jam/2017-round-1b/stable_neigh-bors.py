#!/usr/bin/python

def solve(R, O, Y, G, B, V):
    if O == B and V == 0 and Y == 0 and G == 0 and R == 0:
        return 'OB' * B
    if V == Y and O == 0 and B == 0 and G == 0 and R == 0:
        return 'VY' * Y
    if G == R and O == 0 and B == 0 and V == 0 and Y == 0:
        return 'GR' * R
    if O >= max(B, 1) or V >= max(Y, 1) or G >= max(R, 1):
        return 'IMPOSSIBLE'
    R, Y, B = R - G, Y - V, B - O
    if R > Y + B or Y > R + B or B > R + Y:
        return 'IMPOSSIBLE'
    out = (''.join('RY' if i < Y else 'R' for i in range(R)) if R >= Y else
           ''.join('YR' if i < R else 'Y' for i in range(Y)))
    out = ''.join('B' + c if i < B else c for i, c in enumerate(reversed(out)))
    return ''.join('B' + 'OB' * O if i == out.find('B') else (
        'Y' + 'VY' * V if i == out.find('Y') else (
            'R' + 'GR' * G if i == out.find('R') else c))
                   for i, c in enumerate(out))

def run():
    T = int(input())
    for i in range(T):
        L = [int(x) for x in input().strip().split()]
        print('Case #{0}: {1}'.format(i + 1, solve(*L[1:])))

run()
