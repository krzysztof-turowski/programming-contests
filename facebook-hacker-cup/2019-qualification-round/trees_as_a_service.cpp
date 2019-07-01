#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>

typedef int64_t llong;

struct triple {
  int X, Y, Z;
};

class disjoint_set_union {
  std::vector<int> S, R;

 public:
  explicit disjoint_set_union(const int &n) {
    S.resize(n), R.resize(n, 0);
    for (int i = 0; i < n; i++) {
      S[i] = i;
    }
  }

  int find(const int &x) {
    if (S[x] != x) {
      S[x] = find(S[x]);
    }
    return S[x];
  }

  void join(const int &x, const int &y) {
    int x_root = find(x), y_root = find(y);
    if (x_root != y_root) {
      S[y_root] = x_root;
      if (R[x_root] < R[y_root]) {
        R[x_root] = R[y_root] + 1;
      }
    }
  }

  void print() {
    for (const auto &v : S) {
      std::cout << v + 1 << " ";
    }
    std::cout << std::endl;
  }
};

void fill(std::vector<int> &parents) {
  int index =
      std::find_if(parents.begin(), parents.end(), [](const int &v) -> bool { return v == -1; })
          - parents.begin();
  for (int i = index + 1; i < parents.size(); i++) {
    if (parents[i] == -1) {
      parents[i] = index;
    }
  }
}

void check(const std::vector<triple> &LCA, const std::vector<int> &parents) {
  for (const auto &lca : LCA) {
    std::stack<int> P, Q;
    int p = lca.X, q = lca.Y;
    while (p != -1) {
      P.push(p), p = parents[p];
    }
    while (q != -1) {
      Q.push(q), q = parents[q];
    }
    int last = -1;
    while (!P.empty() && !Q.empty() && P.top() == Q.top()) {
      last = P.top(), P.pop(), Q.pop();
    }
    assert(lca.Z == last);
  }
}

bool check_conditions(
    const int &root, const std::vector<triple> &LCA,
    disjoint_set_union &S, std::map<int, std::vector<triple>> &LCAs) {
  for (const auto &lca : LCA) {
    if (lca.X == root || lca.Y == root) {
      if (lca.Z != root) {
        return false;
      }
    } else if (lca.Z != root) {
      S.join(lca.Z, lca.X), S.join(lca.Z, lca.Y);
    }
  }
  for (const auto &lca : LCA) {
    if (lca.Z == root && lca.X != root && lca.Y != root) {
      if (S.find(lca.X) == S.find(lca.Y)) {
        return false;
      }
    }
    if (lca.Z != root) {
      LCAs[S.find(lca.Z)].push_back(lca);
    }
  }
  return true;
}

bool construct_tree(const std::vector<triple> &LCA, std::vector<int> &parents) {
  std::set<int> roots;
  for (const auto &lca : LCA) {
    roots.insert(lca.Z);
  }
  for (const auto &lca : LCA) {
    if (lca.X != lca.Z && roots.count(lca.X)) {
      roots.erase(lca.X);
    }
    if (lca.Y != lca.Z && roots.count(lca.Y)) {
      roots.erase(lca.Y);
    }
  }
  for (const auto &root : roots) {
    disjoint_set_union S(parents.size());
    std::map<int, std::vector<triple>> LCAs;
    if (check_conditions(root, LCA, S, LCAs)) {
      for (const auto &lca : LCA) {
        if (lca.X != root) {
          parents[lca.X] = root;
        }
        if (lca.Y != root) {
          parents[lca.Y] = root;
        }
        if (lca.Z != root) {
          parents[lca.Z] = root;
        }
      }
      for (const auto lcas : LCAs) {
        if (!construct_tree(lcas.second, parents)) {
          return false;
        }
      }
      return true;
    }
  }
  return false;
}

std::string solve(const int &N, const std::vector<triple> &LCA) {
  for (int i = 0; i < N; i++) {
    std::vector<int> parents(N, -1);
    if (construct_tree(LCA, parents)) {
      fill(parents);
      check(LCA, parents);
      std::stringstream S;
      for (const auto &v : parents) {
        S << v + 1 << " ";
      }
      std::string out = S.str();
      return out.substr(0, out.size() - 1);
    }
  }
  return "Impossible";
}

int main() {
  int T, N, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M;
    std::vector<triple> LCA(M);
    for (int i = 0; i < M; i++) {
      std::cin >> LCA[i].X >> LCA[i].Y >> LCA[i].Z;
      LCA[i].X--, LCA[i].Y--, LCA[i].Z--;
    }
    printf("Case #%d: %s\n", t + 1, solve(N, LCA).c_str());
  }
  return 0;
}
