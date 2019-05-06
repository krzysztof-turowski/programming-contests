#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

const llong MOD = 1000000007L;

class Node {
  llong key, sum;
  Node *left = NULL, *right = NULL;

 public:
  explicit Node(const llong &k) : key(k), sum(0L) { }

  ~Node() {
    if (left != NULL) {
      delete left;
    }
    if (right != NULL) {
      delete right;
    }
  }

  static Node* create(const std::vector<llong> &keys, const int &first, const int &last) {
    int mid = (first + last) / 2;
    Node *root = new Node(keys[mid]);
    if (first < mid) {
      root->left = create(keys, first, mid - 1);
    }
    if (mid < last) {
      root->right = create(keys, mid + 1, last);
    }
    return root;
  }

  void insert(const llong &k, const llong &v) {
    if (k == key) {
      sum = (sum + v) % MOD;
      return;
    }
    if (k < key) {
      left->insert(k, v);
      sum = (sum + v) % MOD;
    } else {
      right->insert(k, v);
    }
  }

  llong get_smaller(const llong &k) {
    if (key < k) {
      return (sum + (right ? right->get_smaller(k) : 0L)) % MOD;
    }
    return left ? left->get_smaller(k) : 0L;
  }

  llong get_total() {
    return (sum + (right ? right->get_total() : 0L)) % MOD;
  }

  void print() {
    if (left != NULL) {
      left->print();
    }
    std::cout << key << ":" << sum << " ";
    if (right != NULL) {
      right->print();
    }
  }
};

std::vector<llong> generate_input(
    std::vector<llong> &A, const int &N, const int &M,
    const llong &X, const llong &Y, const llong &Z) {
  std::vector<llong> B;
  for (int i = 0; i < N; i++) {
    B.push_back(A[i % M]);
    A[i % M] = (X * A[i % M] + Y * (i + 1)) % Z;
  }
  return B;
}

llong solve(const std::vector<llong> &B) {
  std::vector<llong> S(B);
  std::sort(S.begin(), S.end());
  Node *T = Node::create(S, 0, S.size() - 1);
  for (int i = 0; i < B.size(); i++) {
    T->insert(B[i], T->get_smaller(B[i]) + 1);
  }
  llong out = T->get_total();
  delete T;
  return out;
}

int main() {
  int T, N, M;
  llong X, Y, Z;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M >> X >> Y >> Z;
    std::vector<llong> A(M);
    for (int i = 0; i < M; i++) {
      std::cin >> A[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(generate_input(A, N, M, X, Y, Z)));
  }
  return 0;
}
