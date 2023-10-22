#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <map>

using llong = int64_t;
using ldouble = long double;
using pint = std::pair<int, int>;
using vdouble = std::vector<double>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

const int INF = 1000000000;

struct Element {
  int dest, length, index;

  Element(const int &dest_v, const int &length_v, const int &index_v)
      : dest(dest), length(length), index(index) { }
};

bool compare(const pint &i, const pint &j) {
  if (j.second) {
    return true;
  }
  if (i.second) {
    return false;
  }
  return i.first < j.first;
}

bool check(const pint &i) {
  return i.first < INF;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    std::vector<std::vector<Element>> V;
    std::map<std::string, int> C;
    int M, K = 1, length;
    std::string start, a, b;

    std::cin >> M >> start, C[start] = 0;
    REP(i, M) {
      std::cin >> a >> b >> length;
      int &x = C[a], &y = C[b];
      if (x == 0 && a != start) {
        x = K++;
      }
      if (y == 0 && b != start) {
        y = K++;
      }
      V.resize(K);
      V[x].push_back(Element(y, length, i));
    }

    std::vector<pint> U(K);
    U[0] = std::make_pair(0, false);
    FOR(i, 1, K - 1) {
      U[i] = std::make_pair(INF, false);
    }
    std::vector<std::list<std::list<int>>> L(K);
    L[0].resize(1);

    REP(i, K) {
      int pos = std::min_element(U.begin(), U.end(), compare) - U.begin();

      U[pos].second = true;
      if (U[pos].first >= INF) {
        break;
      }
      for (auto it : V[pos]) {
        length = U[pos].first + it.length;
        if (length < U[it.dest].first) {
          L[it.dest].clear();
          for (const auto &jt : L[pos]) {
            std::list<int> l(jt);
            l.push_back(it.index);
            L[it.dest].push_back(l);
          }
          U[it.dest].first = length;
        } else if (length == U[it.dest].first) {
          for (const auto &jt : L[pos]) {
            std::list<int> l(jt);
            l.push_back(it.index);
            L[it.dest].push_back(l);
          }
        }
      }
    }

    vdouble E(M);
    double base = 1.0 / (std::count_if(U.begin(), U.end(), check) - 1);

    FOR(i, 1, K - 1) {
      double value = base / L[i].size();
      for (const auto &jt : L[i]) {
        for (auto kt : jt) {
          E[kt] += value;
        }
      }
    }

    printf("Case #%d: ", t + 1);
    for (auto it : E) {
      printf("%.6lf ", it);
    }
    puts("");
  }

  return 0;
}
