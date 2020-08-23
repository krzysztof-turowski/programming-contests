import math

class TrieNode:
    def __init__(self, d):
        self.children, self.depth, self.end, self.size = {}, d, False, 0

def insert(root, w):
    node = root
    for i, c in enumerate(w, 1):
        node.size += 1
        if c not in node.children:
            node.children[c] = TrieNode(i)
        node = node.children[c]
    node.size += 1
    node.end = True

def simplify(root):
    index, L = 0, [root]
    while index < len(L):
        L.extend(L[index].children.values())
        index += 1
    for node in L:
        if node.size == 1 and not node.end:
            node.children, node.end = {}, True

def merge(parent, child):
    for k1 in range(len(parent.F) - 1, -1, -1):
        for k2 in range(k1 + 1):
            parent.F[k1] = min(
                parent.F[k1], parent.F[k1 - k2] + child.F[k2])

def build(root, K):
    index, L = 0, [root]
    while index < len(L):
        L.extend(L[index].children.values())
        index += 1
    for node in L[::-1]:
        node.F = [0] + [math.inf] * K
        for child in node.children.values():
            merge(node, child)
        if node.end:
            node.F = [0, 0] + [v + node.depth for v in node.F[1:-1]]
        node.F[1] = node.depth

def solve(W, K):
    root = TrieNode('')
    for w in W:
        insert(root, w)
    simplify(root)
    build(root, K)
    return root.F[K]

def run():
    T = int(input())
    for i in range(T):
        N, K = (int(x) for x in input().split())
        W = [input().strip() for _ in range(N)]
        print('Case #{0}: {1}'.format(i + 1, solve(W, K)))

run()
