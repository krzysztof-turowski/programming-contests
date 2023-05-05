#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    std::string input, output, left, right;
    std::cin >> input >> left >> right;

    int base = 1, value = 0;
    FORD(i, input.size() - 1, 0) {
      value += left.find(input[i]) * base, base *= left.size();
    }
    while (value) {
      output.push_back(right[value % right.size()]), value /= right.size();
    }
    std::reverse(output.begin(), output.end());
    printf("Case #%d: %s\n", t + 1, output.c_str());
  }

  return 0;
}
