#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int MAX = 1000000;
int D[300][300][2];

std::vector<int> generate(
    std::vector<int> &stack, const int &f, const int &H) {
  for (int j = 0; j <= H; j++) {
    for (int c = 0; c <= H + 1; c++) {
      for (int g = 0; g < 2; g++) {
        D[j][c][g] = MAX;
      }
    }
  }
  for (int c = 0; c <= H; c++) {
    D[0][c][f] = 0;
  }
  for (int j = 0; j < H; j++) {
    for (int c = 0; c <= H; c++) {
      for (int g = 0; g < 2; g++) {
        D[j + 1][c + (stack[j] != g)][stack[j]] = std::min(
          D[j + 1][c + (stack[j] != g)][stack[j]], D[j][c][g]);
        D[j + 1][c][g] = std::min(D[j + 1][c][g], D[j][c][g] + 1);
      }
    }
  }
  std::vector<int> out(H + 1, MAX);
  for (int c = 0; c <= H; c++) {
    for (int g = 0; g < 2; g++) {
      out[c] = std::min(out[c], D[H][c][g]);
    }
  }
  return out;
}

int query(const int &q, const int &H, std::vector<int> &L) {
  int low = -1, high = H;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (L[mid] > q) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return high + 1;
}

std::vector<int> solve(
    std::vector<std::string> &P, const int &H, const int &S,
    std::vector<int> &Q) {
  std::vector<std::vector<int>> F(H + 1, std::vector<int>(2, 0));
  for (int i = 0; i < S; i++) {
    std::vector<int> stack(H);
    for (int j = 0; j < H; j++) {
      stack[j] = (P[j][i] == 'B');
    }
    for (int f = 0; f < 2; f++) {
      auto M = generate(stack, f, H);
      for (int c = 0; c <= H; c++) {
        F[c][f] += M[c];
      }
    }
  }
  std::vector<int> L(H + 1, MAX);
  for (int c = 0; c <= H; c++) {
    for (int f = 0; f < 2; f++) {
      L[c] = std::min(L[c], F[c][f]);
    }
  }
  std::vector<int> out;
  for (auto &q : Q) {
    out.push_back(query(q, H, L));
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int H, S, L;
    std::cin >> H >> S >> L;
    std::cin.ignore(256, '\n');
    std::vector<std::string> P(H);
    for (int i = 0; i < H; i++) {
      std::cin >> P[i];
    }
    std::vector<int> Q(L);
    for (int i = 0; i < L; i++) {
      std::cin >> Q[i];
    }
    printf("Case #%d: ", t + 1);
    for (auto &v : solve(P, H, S, Q)) {
      printf("%d ", v);
    }
    printf("\n");
  }
  return 0;
}
