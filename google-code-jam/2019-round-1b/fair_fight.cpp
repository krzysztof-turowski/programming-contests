#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define INF 1000000

using llong = int64_t;

class FenwickTree {
  std::vector<int> R, F_min, F_max;

 public:
  explicit FenwickTree(const std::vector<int> &V)
      : R(V), F_min(V.size() + 2, -INF), F_max(V.size() + 2, -INF) {
    for (int i = F_min.size() - 2; i >= 1; i--) {
      F_min[i] = std::max(F_min[i], V[i - 1]);
      F_min[i - (i & -i)] = std::max(F_min[i - (i & -i)], F_min[i]);
    }
    for (int i = 1; i < F_max.size() - 1; i++) {
      F_max[i] = std::max(F_max[i], V[i - 1]);
      F_max[i + (i & -i)] = std::max(F_max[i + (i & -i)], F_max[i]);
    }
  }

  int get_maximum(const int &left, const int &right) const {
    int out = -INF, current = left + 1;
    while (current + (current & -current) <= right + 1) {
      out = std::max(out, F_min[current]);
      current = current + (current & -current);
    }
    current = right + 1;
    while (current - (current & -current) >= left + 1) {
      out = std::max(out, F_max[current]);
      current = current - (current & -current);
    }
    return std::max(out, R[current - 1]);
  }

  int get_size() const {
    return R.size();
  }
};

int binary_search_left(const int &index, const FenwickTree &C, const int &value) {
  int low = -1, high = index;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (C.get_maximum(mid, index) <= value) {
      high = mid;
    } else {
      low = mid;
    }
  }
  if (high == index && C.get_maximum(index, index) > value) {
    return -1;
  }
  return high;
}

int binary_search_right(const int &index, const FenwickTree &C, const int &value) {
  int low = index, high = C.get_size();
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (C.get_maximum(index, mid) <= value) {
      low = mid;
    } else {
      high = mid;
    }
  }
  if (low == index && C.get_maximum(index, index) > value) {
    return -1;
  }
  return low;
}

llong solve(const std::vector<int> &C, const std::vector<int> &D, const int &K) {
  llong out = 0;
  FenwickTree C_query(C), D_query(D);
  for (int i = 0; i < C.size(); i++) {
    int L1 = i > 0 ? binary_search_left(i - 1, C_query, C[i] - 1) : -1;
    if (L1 == -1) {
      L1 = i;
    }
    int R1 = binary_search_right(i, C_query, C[i]);
    int L2 = binary_search_left(i, D_query, C[i] + K);
    int R2 = binary_search_right(i, D_query, C[i] + K);
    int L3 = binary_search_left(i, D_query, C[i] - K - 1);
    int R3 = binary_search_right(i, D_query, C[i] - K - 1);
    if (L2 != -1 || R2 != -1) {
      L2 = L2 != -1 ? L2 : i, R2 = R2 != -1 ? R2 : i;
      out += static_cast<llong>(i - std::max(L1, L2) + 1) * (std::min(R1, R2) - i + 1);
    }
    if (L3 != -1 || R3 != -1) {
      L3 = L3 != -1 ? L3 : i, R3 = R3 != -1 ? R3 : i;
      out -= static_cast<llong>(i - std::max(L1, L3) + 1) * (std::min(R1, R3) - i + 1);
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N, K;
    std::cin >> N >> K;
    std::vector<int> C(N), D(N);
    for (int i = 0; i < N; i++) {
      std::cin >> C[i];
    }
    for (int i = 0; i < N; i++) {
      std::cin >> D[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(C, D, K));
  }
  return 0;
}
