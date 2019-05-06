#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Node {
  Node *left = NULL, *right = NULL, *parent = NULL;

 public:
  int size = 0, key;
  bool retained = true;

  Node(const int &low, const int &high, Node *parent_v) : parent(parent_v) {
    key = (low + high) / 2, size = 1;
    if (low < key) {
      left = new Node(low, key - 1, this), size += left->size;
    }
    if (key < high) {
      right = new Node(key + 1, high, this), size += right->size;
    }
  }

  Node* get(const int &offset) {
    int left_size = (left ? left->size : 0);
    if (offset == left_size && retained) {
      return this;
    }
    if (offset < left_size) {
      return left->get(offset);
    }
    return right->get(offset - left_size - retained);
  }

  void remove() {
    size--;
    if (parent != NULL) {
      parent->remove();
    }
  }

  ~Node() {
    if (left) {
      delete left;
    }
    if (right) {
      delete right;
    }
  }
};

std::vector<int> solve(const int &K, const std::vector<int> &D) {
  Node *root = new Node(1, K, NULL);
  std::vector<int> out(D.size());
  for (int i = 0, offset = 0; i < K; i++) {
    offset = (offset + i) % root->size;
    Node *node = root->get(offset);
    node->retained = false;
    for (int j = 0; j < D.size(); j++) {
      if (D[j] == node->key) {
        out[j] = i + 1;
      }
    }
    node->remove();
  }
  delete root;
  return out;
}

int main() {
  int T, K, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> K >> N;
    std::vector<int> D(N);
    for (int i = 0; i < N; i++) {
      std::cin >> D[i];
    }
    std::vector<int> V = solve(K, D);
    printf("Case #%d:", t + 1);
    for (const auto &v : V) {
      printf(" %d", v);
    }
    printf("\n");
  }
  return 0;
}
