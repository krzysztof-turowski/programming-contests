#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

class Node {
  Node *parent = NULL;
  int rank = 0;
 public:
  Node* find() {
    return parent == NULL ? this : parent->find();
  }

  static void join(Node *x, Node *y) {
    Node *x_root = x->find(), *y_root = y->find();
    if (x_root == y_root) {
      return;
    }
    if (x_root->rank > y_root->rank) {
      y_root->parent = x_root;
    } else if (x_root->rank < y_root->rank) {
      x_root->parent = y_root;
    } else {
      y_root->parent = x_root, x_root->rank++;
    }
  }
};

int solve(const llong &A, const llong &B, const llong &P) {
  std::vector<Node> V(B - A + 1);
  std::vector<bool> primes(B - A + 1, true);
  for (int i = 2; i < primes.size(); i++) {
    if (primes[i]) {
      for (llong j = i; i * j < primes.size(); j++) {
        primes[i * j] = false;
      }
      if (i >= P) {
        llong v = (A % i == 0) ? A : (A - (A % i) + i);
        for (int j = 1; v + i * j <= B; j++) {
          Node::join(&V[v - A], &V[v + i * j - A]);
        }
        std::set<Node*> R;
      }
    }
  }
  std::set<Node*> R;
  for (auto &v : V) {
    R.insert(v.find());
  }
  return R.size();
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    llong A, B, P;
    std::cin >> A >> B >> P;
    printf("Case #%d: %d\n", t + 1, solve(A, B, P));
  }
  return 0;
}
