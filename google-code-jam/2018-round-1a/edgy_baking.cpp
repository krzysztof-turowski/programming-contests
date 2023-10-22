#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using ldouble = long double;

ldouble solve(std::vector<std::pair<ldouble, ldouble>> &S, const int &P) {
  ldouble value = P, start = 0;
  for (int i = 0; i < S.size(); i++) {
    start += 2 * (S[i].first + S[i].second);
  }
  sort(
      S.begin(), S.end(),
      [](const std::pair<ldouble, ldouble> &a, const std::pair<ldouble, ldouble> &b) {
          return a.first + a.second < b.first + b.second;
  });
  std::vector<std::pair<ldouble, ldouble>> V;
  V.push_back(std::make_pair(start, start));
  for (int i = 0; i < S.size(); i++) {
    int size = V.size();
    ldouble low = 2 * std::min(S[i].first, S[i].second);
    ldouble high = 2 * sqrtl(S[i].first * S[i].first + S[i].second * S[i].second);
    for (int j = 0; j < size; j++) {
      V.push_back(std::make_pair(V[j].first + low, V[j].second + high));
    }
    sort(
        V.begin(), V.end(),
        [](const std::pair<ldouble, ldouble> &a, const std::pair<ldouble, ldouble> &b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
    });
    int index = 0;
    for (int j = 1; j < V.size(); j++) {
      if (V[index].second >= P) {
        break;
      }
      if (V[index].second >= V[j].first) {
        V[index].second = V[j].second;
      } else {
        index++, V[index] = V[j];
      }
    }
    V.resize(index + 1);
  }
  for (int i = 0; i < V.size(); i++) {
    if (P >= V[i].first && P <= V[i].second) {
      return P;
    } else if (P < V[i].first && P > V[i - 1].second) {
      return V[i - 1].second;
    }
  }
  return V.back().second;
}

int main() {
  int T, N, P;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> P;
    std::vector<std::pair<ldouble, ldouble>> S(N);
    for (int i = 0; i < N; i++) {
      std::cin >> S[i].first >> S[i].second;
    }
    printf("Case #%d: %.7Lf\n", t + 1, solve(S, P));
  }
}
