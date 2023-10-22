#include <iostream>
#include <vector>

#define INF 10000000

struct candidate {
 public:
  int M, N, start, xstart;

  candidate() {
    this->M = 0, this->N = 0, this->start = 0, this->xstart = 0;
  }

  candidate& operator= (const candidate &other) {
    this->M = other.M, this->N = other.N, this->start = other.start, this->xstart = other.xstart;
    return *this;
  }
};

int verify_A(
    const std::vector<int> &D, const std::vector<int> &A, const std::vector<int> &B,
    const int &start) {
  int M = D[start] + A[start], N = INF;
  for (int i = start; i < D.size(); i++) {
    if (D[i] + A[i] != M) {
      if (N != INF && D[i] - B[i] != N) {
        return i - start;
      }
      if (N == INF)
        N = D[i] - B[i];
    }
  }
  return D.size() - start;
}

int verify_B(
    const std::vector<int> &D, const std::vector<int> &A, const std::vector<int> &B,
    const int &start) {
  int M = INF, N = D[start] - B[start];
  for (int i = start; i < D.size(); i++) {
    if (D[i] - B[i] != N) {
      if (M != INF && D[i] + A[i] != M) {
        return i - start;
      }
      if (M == INF)
        M = D[i] + A[i];
    }
  }
  return D.size() - start;
}

std::pair<int, int> solve(
    const std::vector<int> &D, const std::vector<int> &A, const std::vector<int> &B) {
  std::vector<int> S(D.size());
  int max_S = 0, count_S = 0;
  for (int i = 0; i < D.size(); i++) {
    S[i] = std::max(verify_A(D, A, B, i), verify_B(D, A, B, i));
    max_S = std::max(max_S, S[i]);
  }
  for (int i = 0; i < S.size(); i++) {
    if (S[i] == max_S) {
      count_S++;
    }
  }
  return std::make_pair(max_S, count_S);
}

std::pair<int, int> solve_2(
    const std::vector<int> &D, const std::vector<int> &A, const std::vector<int> &B) {
  std::vector<candidate> M(D.size()), N(D.size());
  M[0].M = D[0] + A[0], N[0].M = D[0] - B[0];
  for (int i = 1; i < D.size(); i++) {
    if (D[i] + A[i] == M[i - 1].M) {
      M[i] = M[i - 1];
    } else if (D[i] + A[i] == N[i - 1].M) {
      M[i] = N[i - 1], M[i].xstart = i;
    } else {
      M[i] = N[i - 1], M[i].xstart = i, M[i].start = N[i - 1].xstart;
    }

    if (D[i] - B[i] == N[i - 1].N) {
      N[i] = N[i - 1];
    } else if (D[i] - B[i] == M[i - 1].N) {
      N[i] = M[i - 1], N[i].xstart = i;
    } else {
      N[i] = M[i - 1], N[i].xstart = i, N[i].start = M[i - 1].xstart;
    }
  }

  int max_S = 0, count_S = 0;
  for (int i = 0; i < D.size(); i++) {
    max_S = i + 1 - std::min(M[i].start, N[i].start);
  }
  for (int i = 0; i < D.size(); i++) {
    if (i + 1 - std::min(M[i].start, N[i].start) == max_S) {
      count_S++;
    }
  }
  return std::make_pair(max_S, count_S);
}

int main() {
  int T, S;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> S;
    std::vector<int> D(S), A(S), B(S);
    for (int i = 0; i < S; i++)
      std::cin >> D[i] >> A[i] >> B[i];
    std::pair<int, int> solution = solve(D, A, B);
    printf("Case #%d: %d %d\n", t + 1, solution.first, solution.second);
  }
}
