#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

const int INF = 1000000000;

struct Element {
  std::string name;
  int value;
  bool used;

  explicit Element(const std::string &name) : name(name), used(false) { }

  static bool compare(const Element *a, const Element *b) {
    return a->name < b->name;
  }
};

int longest_subsequence(const std::vector<Element*> &V) {
  vint A(SIZE(V) + 1);
  for (auto it = A.begin(); it != A.end(); ++it) {
    *it = INF;
  }
  A[0] = -1;

  REP(i, SIZE(V)) {
    if (!V[i]->used) {
      auto it = std::upper_bound(A.begin(), A.end(), V[i]->value);
      *it = V[i]->value;
    }
  }
  return std::lower_bound(A.begin(), A.end(), INF) - A.begin();
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    std::vector<Element*> V;
    std::string name;

    std::cin.ignore(1);
    while (std::cin.peek() != '\n') {
      std::cin >> name;
      V.push_back(new Element(name));
    }
    for (auto it : V) {
      std::cin >> it->value;
    }
    int value = longest_subsequence(V);
    std::vector<Element*> U(V);
    std::sort(U.begin(), U.end(), Element::compare);

    printf("Case #%d: ", t + 1);
    for (auto it : U) {
      it->used = true;
      if (value == longest_subsequence(V)) {
        printf("%s ", it->name.c_str());
      } else {
        it->used = false;
      }
    }
    puts("");

    for (auto it : V) {
      delete it;
    }
  }

  return 0;
}
