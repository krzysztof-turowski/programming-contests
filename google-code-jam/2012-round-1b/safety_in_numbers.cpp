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

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()
#define PART(c, k) c.begin(), c.begin() + (k)

#define ST first
#define ND second
#define INF 1000000000LL
#define INFL 1000000000000000000LL
#define EPS 1e-6

bool check(const vint &scores, const int &v, const int &sum, const double &p) {
  int N = scores.size();
  double score = scores[v] + sum * p, q = 0;
  REP(i, N)
    if (i != v && score > scores[i])
      q += (score - scores[i]) / sum;

  return p + q > 1;
}

double binary_search(
    const vint &scores, const int &v, const int &sum,
    const double &min, const double &max) {
  if (max - min < EPS)
    return max;

  double p = (min + max) / 2;
  return check(scores, v, sum, p / 100)
      ? binary_search(scores, v, sum, min, p) : binary_search(scores, v, sum, p, max);
}

int main() {
  int T, N;

  std::cin >> T;
  REP(t, T) {
    std::cin >> N;
    vint scores(N);
    int sum = 0;
    REP(i, N)
      std::cin >> scores[i], sum += scores[i];
    printf("Case #%d: ", t + 1);
    REP(i, N)
      printf("%.5lf ", binary_search(scores, i, sum, 0.0, 100.0));
    puts("");
  }

  return 0;
}
