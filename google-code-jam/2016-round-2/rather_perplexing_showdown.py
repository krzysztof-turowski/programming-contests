#!/usr/bin/python

def solve(P, R, S, A):
    if P == 1 and R == 0 and S == 0:
        return True, 'P'
    if R == 1 and P == 0 and S == 0:
        return True, 'R'
    if S == 1 and R == 0 and P == 0:
        return True, 'S'
    if 2 * max(R, P, S) > R + P + S:
        return False, 'IMPOSSIBLE'
    A_new = {
        'P': min(A['P'] + A['R'], A['R'] + A['P']),
        'R': min(A['R'] + A['S'], A['S'] + A['R']),
        'S': min(A['S'] + A['P'], A['P'] + A['S'])}
    PR = (R + P - S) // 2
    possible, out = solve(PR, R - PR, P - PR, A_new)
    if possible:
        B = {
            'P': 'PR' if A['P'] < A['R'] else 'RP',
            'R': 'RS' if A['R'] < A['S'] else 'SR',
            'S': 'SP' if A['S'] < A['P'] else 'PS'}
        out = ''.join(B[c] for c in out)
    return possible, out

def run():
    T = int(input())
    for i in range(T):
        _, R, P, S = (int(x) for x in input().split())
        A = {'P': 'P', 'R': 'R', 'S': 'S'}
        print('Case #{0}: {1}'.format(i + 1, solve(P, R, S, A)[1]))

run()
