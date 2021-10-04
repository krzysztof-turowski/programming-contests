#!/usr/bin/python

def get_values(B, transpose = False):
    values = [sum(1 for c in b if c == '.') for b in B if 'O' not in b]
    first = [(b.find('.'), i) if transpose else (i, b.find('.'))
             for i, b in enumerate(B) if 'O' not in b]
    return list(zip(values, first))

def solve(B, N):
    BT = [''.join(b[i] for b in B) for i in range(N)]
    values = get_values(B) + get_values(BT, True)
    if not values:
        return 'Impossible'
    best = min(values)[0]
    if best > 1:
        count = sum(1 for v in values if v[0] == best)
    else:
        count = len(set(v[1] for v in values if v[0] == 1))
    return str(best) + ' ' + str(count)

def run():
    T = int(input())
    for i in range(T):
        N = int(input())
        B = [input().strip() for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(B, N)))

run()
