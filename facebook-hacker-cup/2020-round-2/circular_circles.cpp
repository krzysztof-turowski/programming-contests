#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define llong int64

llong MOD = 1000000007;

std::vector<int> read_and_generate(int K, int N, int M) {
  std::vector<int> out(K);
  for (int i = 0; i < K; i++) {
    std::cin >> out[i];
  }
  llong A, B, C;
  std::cin >> A >> B >> C;
  for (int i = K; i < N; i++) {
    out.push_back((A * out[i - 2] + B * out[i - 1] + C) % M);
  }
  return out;
}

llong solve(
    std::vector<int> &X, std::vector<int> &Y, std::vector<int> &I,
    std::vector<int> &W, int N, int M) {
  llong q1 = N * M + N, q2 = N;
  std::vector<int> E(N * M + N, 1);
  std::vector<std::multiset<int>> cycles(N), upper_half(N), lower_half(N);
  std::multiset<int> D;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cycles[i].insert(1);
    }
    int length = std::max(X[i], Y[i]) - std::min(X[i], Y[i]);
    lower_half[i].insert(0);
    for (int j = 0; j < length; j++) {
      lower_half[i].insert(1);
    }
    for (int j = 0; j < M - length; j++) {
      upper_half[i].insert(1);
    }
    if (length > 0) {
      int lower = *(lower_half[i].rbegin()), upper = *(upper_half[i].rbegin());
      D.insert(lower + upper - std::max(lower, upper));
    }
  }
  for (int i = 0; i < N; i++) {
    D.insert(1);
  }

  llong out = 1;
  // printf("%d %d %d %d\n", q1, q2, *(D.rbegin()), q1 - q2 - *(D.rbegin()));
  for (int i = 0; i < I.size(); i++) {
    int previous = E[I[i]];
    E[I[i]] = W[i];
    q1 += (W[i] - previous);
    if (I[i] < M * N) {
      int offset = I[i] / M, index = I[i] % M;
      q2 -= *(cycles[offset].rbegin());
      cycles[offset].erase(cycles[offset].lower_bound(previous)), cycles[offset].insert(W[i]);
      q2 += *(cycles[offset].rbegin());
      int length = std::max(X[offset], Y[offset]) - std::min(X[offset], Y[offset]);
      if (length > 0) {
        int lower = *(lower_half[offset].rbegin()), upper = *(upper_half[offset].rbegin());
        D.erase(D.lower_bound(lower + upper - std::max(lower, upper)));
        if (std::min(X[offset], Y[offset]) <= index && index < std::max(X[offset], Y[offset])) {
          lower_half[offset].erase(lower_half[offset].lower_bound(previous));
          lower_half[offset].insert(W[i]);
          lower = *(lower_half[offset].rbegin());
        } else {
          upper_half[offset].erase(upper_half[offset].lower_bound(previous));
          upper_half[offset].insert(W[i]);
          upper = *(upper_half[offset].rbegin());
        }
        D.insert(lower + upper - std::max(lower, upper));
      }
    } else {
      D.erase(D.lower_bound(previous)), D.insert(W[i]);
    }
    llong q3 = *(D.rbegin());
    llong V = (q1 - q2 - q3) % MOD;
    out = (out * V) % MOD;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N, M, E, K;
    std::cin >> N >> M >> E >> K;
    auto X = read_and_generate(K, N, M);
    auto Y = read_and_generate(K, N, M);
    auto I = read_and_generate(K, E, N * M + N);
    auto W = read_and_generate(K, E, 1000000000);
    printf("Case #%d: %lld\n", t + 1, solve(X, Y, I, W, N, M));
  }
  return 0;
}
