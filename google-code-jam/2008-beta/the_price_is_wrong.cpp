#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
typedef vint::iterator vit;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ST first
#define ND second
#define INF 1000000000LL
#define EPS 1e-5

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
  FOREACH(i, A)
    *i = INF;
  A[0] = -1;

  REP(i, SIZE(V))
    if (!V[i]->used) {
      vit it = upper_bound(ALL(A), V[i]->value);
      *it = V[i]->value;
    }

  return lower_bound(ALL(A), INF) - A.begin();
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
    FOREACH(it, V)
      std::cin >> (*it)->value;

    int value = longest_subsequence(V);
    std::vector<Element*> U(V);
    std::sort(ALL(U), Element::compare);

    printf("Case #%d: ", t + 1);
    FOREACH(it, U) {
      (*it)->used = true;
      if (value == longest_subsequence(V)) {
        printf("%s ", (*it)->name.c_str());
      } else {
        (*it)->used = false;
      }
    }
    puts("");

    FOREACH(it, V)
      delete *it;
  }

  return 0;
}
