#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void get_preorder(
    const std::vector<std::pair<int, int>> &S, std::vector<int> &X, const int &index) {
  X.push_back(index);
  if (S[index].first != -1) {
    get_preorder(S, X, S[index].first);
  }
  if (S[index].second != -1) {
    get_preorder(S, X, S[index].second);
  }
}

void get_postorder(
    const std::vector<std::pair<int, int>> &S, std::vector<int> &X, const int &index) {
  if (S[index].first != -1) {
    get_postorder(S, X, S[index].first);
  }
  if (S[index].second != -1) {
    get_postorder(S, X, S[index].second);
  }
  X.push_back(index);
}

std::vector<int> reverse(const std::vector<int> &A) {
  std::vector<int> out(A.size());
  for (int i = 0; i < A.size(); i++) {
    out[A[i]] = i;
  }
  return out;
}

int find_root(const std::vector<std::pair<int, int>> &S) {
  std::vector<bool> A(S.size());
  for (int i = 0; i < S.size(); i++) {
    if (S[i].first != -1) {
      A[S[i].first] = true;
    }
    if (S[i].second != -1) {
      A[S[i].second] = true;
    }
  }
  for (int i = 0; i < A.size(); i++) {
    if (!A[i]) {
      return i;
    }
  }
  return -1;
}

std::string solve(const std::vector<std::pair<int, int>> &S, const int &K) {
  std::vector<int> A, B, L(S.size());
  int root = find_root(S);
  get_preorder(S, A, root), get_postorder(S, B, root);
  std::vector<int> A_rev = reverse(A);

  int count = 0;
  for (int i = 0; i < A.size(); i++) {
    if (A[i] == -1) {
      continue;
    }
    count++;
    int index = i;
    L[A[index]] = count % K + 1;
    while (A[index] != -1) {
      L[B[index]] = count % K + 1, A[index] = -1, index = A_rev[B[index]];
    }
  }
  if (count < K) {
    return "Impossible";
  }
  std::stringstream out;
  for (const auto &l : L) {
    out << l << " ";
  }
  out.unget();
  return out.str();
}

int main() {
  int T, N, K;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> K;
    std::vector<std::pair<int, int>> S(N);
    for (int i = 0; i < N; i++) {
      std::cin >> S[i].first >> S[i].second, S[i].first--, S[i].second--;
    }
    printf("Case #%d: %s\n", t + 1, solve(S, K).c_str());
  }
  return 0;
}
