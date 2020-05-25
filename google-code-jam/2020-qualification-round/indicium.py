#!/usr/bin/python

def find_triple(N, K):
    for a in range(1, N + 1):
        for b in range(1, N + 1):
            for c in range(1, b):
                if a != b and a != c and K == a * (N - 2) + b + c:
                    return [a, b, c]
    return None

def get_matrix(N, row):
    row += row
    return [row[N - i:2 * N - i] for i in range(N)]

def first_fit(N, M):
    for i in range(N):
        for j in range(N):
            if M[i][(i + j) % N] == '*':
                M[i][(i + j) % N] = next(
                    x for x in range(1, N + 1) if x not in (
                        [M[i][k] for k in range(N)] + [M[k][(i + j) % N] for k in range(N)]))

def substitute(N, M, a, b):
    for i in range(N):
        for j in range(N):
            if M[i][j] == a:
                M[i][j] = b

def swap_magic_third(M):
    M[-3][0], M[-1][0], M[-3][-2], M[-1][-2] = M[-1][0], M[-3][0], M[-1][-2], M[-3][-2]

def swap_last_rows(M):
    M[-1], M[-2] = M[-2], M[-1]

def test(N, K, M):
    assert sum(M[i][i] for i in range(N)) == K
    L = list(range(1, N + 1))
    for i in range(N):
        assert sorted(M[i]) == L
        assert sorted([M[j][i] for j in range(N)]) == L

def solve(N, K):
    if K in (N + 1, N * N - 1) or (N == 3 and K in (5, 7)):
        return 'IMPOSSIBLE'
    if K % N == 0:
        M = get_matrix(N, [(K // N + i) % N for i in range(N)])
        substitute(N, M, 0, N)
    elif K == N + 2:
        M = get_matrix(N, [1, 2] + ['*'] * (N - 2))
        swap_magic_third(M)
        swap_last_rows(M)
        first_fit(N, M)
    elif K == N * N - 2:
        M = get_matrix(N, [N, N - 1] + ['*'] * (N - 2))
        swap_magic_third(M)
        swap_last_rows(M)
        first_fit(N, M)
    elif N == 4 and K == 10:
        M = get_matrix(N, [2, 3] + ['*'] * (N - 2))
        swap_magic_third(M)
        swap_last_rows(M)
        first_fit(N, M)
    else:
        v = find_triple(N, K)
        M = get_matrix(N, v[0:2] + [i for i in range(1, N + 1) if i not in v] + v[2:])
        substitute(N, M, v[1], '*')
        substitute(N, M, v[2], v[1])
        substitute(N, M, '*', v[2])
        swap_last_rows(M)
    test(N, K, M)
    out = 'POSSIBLE'
    out += '\n' + '\n'.join(' '.join(str(x) for x in row) for row in M)
    return out

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        print('Case #{0}: {1}'.format(i + 1, solve(N, K)))

run()
