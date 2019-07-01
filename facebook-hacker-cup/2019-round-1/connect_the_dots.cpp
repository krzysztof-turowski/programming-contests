#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

const llong INF = 10000000000000LL;

std::random_device seed;
std::mt19937 generator(seed());
std::uniform_int_distribution<llong> distribution(1LL, INF);

class Node {
  llong key, priority;
  Node *left = NULL, *right = NULL;
  int smaller, equal;

 public:
  explicit Node(const llong &k) : key(k), smaller(0), equal(1) {
    priority = distribution(generator);
  }

  ~Node() {
    if (left != NULL) {
      delete left;
    }
    if (right != NULL) {
      delete right;
    }
  }

  Node* insert(const llong &k) {
    if (k == key) {
      equal++;
      return this;
    }
    if (k < key) {
      smaller++;
      if (left == NULL) {
        left = new Node(k);
      } else {
        left = left->insert(k);
      }
      if (priority < left->priority) {
        Node *x = this->left, *T2 = x->right;
        this->left = T2, x->right = this;
        this->smaller -= (x->smaller + x->equal);
        return x;
      }
    } else {
      if (right == NULL) {
        right = new Node(k);
      } else {
        right = right->insert(k);
      }
      if (priority < right->priority) {
        Node *y = right, *T2 = y->left;
        this->right = T2, y->left = this;
        y->smaller += (this->smaller + this->equal);
        return y;
      }
    }
    return this;
  }

  void erase(const llong &k) {
    if (k == key) {
      equal--;
      return;
    }
    if (k < key) {
      smaller--;
      left->erase(k);
    } else {
      right->erase(k);
    }
  }

  llong upper_bound(const llong &k) {
    if (key == k) {
      return smaller + equal;
    }
    if (k < key) {
      return left ? left->upper_bound(k) : 0;
    } else {
      return smaller + equal + (right ? right->upper_bound(k) : 0);
    }
  }

  llong get_nth_element(const int &index) {
    if (smaller >= index) {
      return left->get_nth_element(index);
    }
    if (smaller + equal < index) {
      return right->get_nth_element(index - smaller - equal);
    }
    return key;
  }

  int get_size() {
    return equal + (left ? left->get_size() : 0) + (right ? right->get_size() : 0);
  }

  void check() {
    assert(smaller == (left ? left->get_size() : 0));
    if (left) {
      assert(left->key < key);
      left->check();
    }
    if (right) {
      assert(right->key > key);
      right->check();
    }
  }
};

class Treap {
  Node *root = NULL;

 public:
  ~Treap() {
    if (root) {
      delete root;
    }
  }

  void insert(const llong &k) {
    if (root) {
      root = root->insert(k);
    } else {
      root = new Node(k);
    }
  }

  void erase(const llong &k) {
    root->erase(k);
  }

  llong upper_bound(const llong &k) {
    return root->upper_bound(k);
  }

  llong get_nth_element(const int &index) {
    return root->get_nth_element(index);
  }

  void check() {
    root->check();
  }
};

llong solve(std::vector<std::pair<llong, llong>> &P, const int &H, const int &V) {
  std::sort(P.begin(), P.end(), [](const auto &a, const auto &b) -> bool {
    return a.first < b.first || (a.first == b.first && a.second > b.second);
  });

  Treap left, right;
  for (int i = 0; i < P.size(); i++) {
    right.insert(P[i].second);
  }
  llong out = INF;
  for (int left_size = 0, right_size = P.size(); right_size >= 0; left_size++, right_size--) {
    if (left_size > 0) {
      right.erase(P[left_size - 1].second), left.insert(P[left_size - 1].second);
    }
    int left_min = left_size > 0 ? left_size - left.upper_bound(P[left_size - 1].second) : 0;
    if (left_min <= H && right_size <= V) {
      llong right_max = right_size > 0 ? right.get_nth_element(right_size) : 0;
      llong left_max = left_size <= H ? 0 : left.get_nth_element(left_size - H);
      out = std::min(
          out, (left_size > 0 ? P[left_size - 1].first : 0) + std::max(right_max, left_max));
    }
  }
  return out;
}

std::vector<std::pair<llong, llong>> generate_data(
    const llong &X1, const llong &X2, const llong &Ax, const llong &Bx,
    const llong &Cx, const llong &Dx, const llong &Y1, const llong &Y2, const llong &Ay,
    const llong &By, const llong &Cy, const llong &Dy, const int &N) {
  std::vector<std::pair<llong, llong>> out{{X1, Y1}, {X2, Y2}};
  for (int i = 2; i < N; i++) {
    out.push_back(std::make_pair(
        ((Ax * out[i - 2].first) % Dx + (Bx * out[i - 1].first) % Dx + Cx) % Dx + 1,
        ((Ay * out[i - 2].second) % Dy + (By * out[i - 1].second) % Dy + Cy) % Dy + 1));
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N, H, V;
    llong X1, X2, Ax, Bx, Cx, Dx, Y1, Y2, Ay, By, Cy, Dy;
    std::cin >> N >> H >> V;
    std::cin >> X1 >> X2 >> Ax >> Bx >> Cx >> Dx;
    std::cin >> Y1 >> Y2 >> Ay >> By >> Cy >> Dy;
    if (H + V < N) {
      printf("Case #%d: -1\n", t + 1);
      continue;
    }
    std::vector<std::pair<llong, llong>> Q =
        generate_data(X1, X2, Ax, Bx, Cx, Dx, Y1, Y2, Ay, By, Cy, Dy, N);
    printf("Case #%d: %lld\n", t + 1, solve(Q, H, V));
  }
  return 0;
}
