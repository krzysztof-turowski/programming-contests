#!/usr/bin/python

class Cell:
    def __init__(self, value, location, size):
        r, c = location
        R, C = size
        self.value = value
        self.neighbors = [
            (r - 1, c) if r > 0 else None,
            (r + 1, c) if r < R - 1 else None,
            (r, c - 1) if c > 0 else None,
            (r, c + 1) if c < C - 1 else None,
        ]
        self.average, self.eliminated = None, False

    def set_average(self, S):
        neighbors = [S[x[0]][x[1]] for x in self.neighbors if x is not None]
        self.average = (
            sum(x.value for x in neighbors) / len(neighbors) if len(neighbors) > 0 else None)

    def make_visible(self, S):
        for i, j in zip([0, 1, 2, 3], [1, 0, 3, 2]):
            if self.neighbors[i] is not None:
                v = S[self.neighbors[i][0]][self.neighbors[i][1]]
                v.neighbors[j] = self.neighbors[j]
                v.set_average(S)
        return [x for x in self.neighbors if x is not None]

def solve(S, R, C):
    out, total, MAX = 0, 0, R * C
    for i in range(R):
        for j in range(C):
            total += S[i][j].value
            S[i][j].set_average(S)
    candidates = set((i, j) for i in range(R) for j in range(C) if not S[i][j].eliminated)
    for i in range(MAX):
        out += total
        to_remove = [S[i][j] for (i, j) in candidates
                     if S[i][j].average is not None and S[i][j].value < S[i][j].average]
        if not to_remove:
            break
        candidates = set()
        for x in to_remove:
            total, x.eliminated = total - x.value, True
            for y in x.make_visible(S):
                candidates.add(y)
        candidates = set((i, j) for i, j in candidates if not S[i][j].eliminated)
    return out

def run():
    T = int(input())
    for i in range(T):
        R, C = [int(x) for x in input().strip().split()]
        S = [[Cell(int(x), (i, j), (R, C)) for j, x in enumerate(input().split())]
             for i in range(R)]
        print('Case #{0}: {1}'.format(i + 1, solve(S, R, C)))

run()
