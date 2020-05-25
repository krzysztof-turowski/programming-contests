#!/usr/bin/python

def agree(C, J, N):
    for i in range(N):
        if C[i] == '?' and J[i] == '?':
            C[i], J[i] = '0', '0'
        elif C[i] == '?':
            C[i] = J[i]
        elif J[i] == '?':
            J[i] = C[i]
    return C, J

def find_closest(B, S):
    return (''.join(b if b != '?' else '0' for b in B),
            ''.join(s if s != '?' else '9' for s in S))

def get(A, B, index, v):
    A[index], B[index] = chr(v + 1), chr(v)
    A, B = find_closest(*agree(A, B, index))
    return ''.join(A), ''.join(B)

def solve(C, J):
    outC, outJ = ''.join('9' * len(C)), ''.join('0' * len(J))
    def compare(C, J):
        CJ, outCJ = abs(int(C) - int(J)), abs(int(outC) - int(outJ))
        if CJ < outCJ or (CJ == outCJ and int(C) < int(outC)):
            return C, J
        if CJ == outCJ and int(C) == int(outC) and int(J) < int(outJ):
            return C, J
        return outC, outJ
    for i, (c, j) in enumerate(zip(C, J)):
        if c == '?' and j == '?':
            outC, outJ = compare(*get(C[:], J[:], i, ord('0')))
            outC, outJ = compare(*reversed(get(J[:], C[:], i, ord('0'))))
            C[i], J[i] = '0', '0'
        elif c == '?':
            if j < '9':
                outC, outJ = compare(*get(C[:], J[:], i, ord(j)))
            if j > '0':
                outC, outJ = compare(*reversed(get(J[:], C[:], i, ord(j) - 1)))
            C[i] = j
        elif j == '?':
            if c < '9':
                outC, outJ = compare(*reversed(get(J[:], C[:], i, ord(c))))
            if c > '0':
                outC, outJ = compare(*get(C[:], J[:], i, ord(c) - 1))
            J[i] = c
        elif c > j:
            outC, outJ = compare(*find_closest(*agree(C[:], J[:], i)))
        elif c < j:
            outC, outJ = compare(
                *reversed(find_closest(*agree(J[:], C[:], i))))
    outC, outJ = compare(''.join(C), ''.join(J))
    return outC, outJ

def run():
    T = int(input())
    for i in range(T):
        C, J = input().strip().split()
        print('Case #{0}: {1} {2}'.format(i + 1, *solve(list(C), list(J))))

run()
