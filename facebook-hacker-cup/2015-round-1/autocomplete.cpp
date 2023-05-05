#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

struct node {
  int children;
  node* child[26];

  node() : children(0) {
    REP(i, 26) {
      child[i] = 0;
    }
  }

  ~node() {
    REP(i, 26) {
      if (child[i]) {
        delete child[i];
      }
    }
  }
};

void insert(node *A, std::string &data, const int &position) {
  A->children++;
  if (position == data.size()) {
    return;
  }
  int p = data[position] - 'a';
  if (!A->child[p]) {
    A->child[p] = new node();
  }
  insert(A->child[p], data, position + 1);
}

int find(node *A, std::string &data, const int &position) {
  if (position == data.size() || A->children == 1) {
    return std::max(position, 1);
  }
  return find(A->child[data[position] - 'a'], data, position + 1);
}

int solve() {
  node *root = new node;
  int N;
  std::cin >> N;
  std::vector<std::string> data(N);
  int out = 0;
  REP(i, N) {
    std::cin >> data[i];
    insert(root, data[i], 0);
    out += find(root, data[i], 0);
  }
  delete root;
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %d\n", t + 1, solve());
  }
  return 0;
}
