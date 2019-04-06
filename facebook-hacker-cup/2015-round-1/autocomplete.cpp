#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
  #define _USE_MATH_DEFINES
#endif

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

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef vint::iterator vit;
typedef std::vector<double> vdouble;
typedef vdouble::iterator vdit;
typedef std::vector<ldouble> vldouble;
typedef std::vector<std::string> vstring;
typedef std::vector<llong> vllong;
typedef std::vector<vint> graph;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ADD_EDGE(g, u, v) g[u].push_back(v), g[v].push_back(u)

#define ST first
#define ND second
#define INF 1000000000
#define INFL 1000000000000000000LL
#define MOD 1000000007L
#define EPS 1e-5
#define MAX 100000

struct node {
  int children;
  node* child[26];

  node() : children(0) {
    REP(i, 26)
      child[i] = 0;
  }

  ~node() {
    REP(i, 26)
      if (child[i])
        delete child[i];
  }
};

void insert(node *A, std::string &data, const int &position) {
  A->children++;

  if (position == SIZE(data))
    return;

  int p = data[position] - 'a';
  if (!A->child[p])
    A->child[p] = new node();
  insert(A->child[p], data, position + 1);
}

int find(node *A, std::string &data, const int &position) {
  if (position == SIZE(data) || A->children == 1)
    return std::max(position, 1);

  int p = data[position] - 'a';
  if (!A->child[p])
    assert(0);
  return find(A->child[p], data, position + 1);
}

int solve() {
  node *root = new node;

  int N;
  std::cin >> N;

  vstring data(N);
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
  REP(t, T)
    printf("Case #%d: %d\n", t + 1, solve());

  return 0;
}
