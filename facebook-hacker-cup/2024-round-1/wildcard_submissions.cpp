#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

const int MAX_THREADS = 8;
const int MAX = 100;
const int64_t MOD = 998244353LL;

const std::vector<int> LOG = {
    1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10,
    1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16, 1 << 17, 1 << 18, 1 << 19, 1 << 20,
    1 << 21, 1 << 22, 1 << 23, 1 << 24, 1 << 25};

inline int log(int s) {
    return std::upper_bound(LOG.begin(), LOG.end(), s) - LOG.begin();
}

int ones(int u) {
    int count = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
    return ((count + (count >> 3)) & 030707070707) % 63;
}

int64_t count(const __int128 &v, int lcp) {
    int64_t out = 0;
    for (int i = lcp - 1; i >= 0; i--) {
        out = ((v & (((__int128)1) << i)) ? (26 * (out + 1)) : (out + 1)) % MOD;
    }
    return out;
}

int lcp(const std::string &a, const std::string &b) {
    for (int i = 0; i < std::min(a.size(), b.size()); i++) {
        if (a[i] != '?' && b[i] != '?' && a[i] != b[i]) {
            return i;
        }
    }
    return std::min(a.size(), b.size());
}

int64_t solve(const std::vector<std::string> &S) {
    std::map<std::pair<int, int>, int> LCP_pair;
    for (int i = 0; i < S.size(); i++) {
        for (int j = i + 1; j < S.size(); j++) {
            LCP_pair[std::make_pair(i, j)] = lcp(S[i], S[j]);
        }
    }

    int64_t out = 1;
    std::vector<int> LCP(1 << S.size());
    std::vector<__int128> V(1 << S.size());
    for (int s = 0; s < (1 << S.size()); s++) {
        if (s == 0) {
            LCP[s] = MAX + 1;
            continue;
        }
        int p_1 = log(s);
        int s_l = (1 << p_1);
        if (s == s_l) {
            auto &S_index = S[p_1];
            LCP[s] = S_index.size();
            auto &v = V[s];
            for (int i = 0; i < S_index.size(); i++) {
                if (S_index[i] == '?') {
                    v ^= ((__int128)1) << i;
                }
            }
        } else {
            int s_1 = s ^ s_l;
            int p_2 = log(s_1);
            int s_2 = s ^ (1 << p_2);
            LCP[s] = std::min(std::min(LCP[s_1], LCP[s_2]), LCP_pair[std::minmax(p_1, p_2)]);
            V[s] = V[s_1] & V[s_l];
        }
        int64_t c = count(V[s], LCP[s]);
        out = (out + (ones(s) % 2 ? c : MOD - c)) % MOD;
    }
    return out;
}

std::mutex mtx;

void parallel(int &t, int T, std::vector<int64_t> &out) {
    int N;
    std::vector<std::string> S;
    while (t < T) {
        mtx.lock();
        std::cin >> N;
        std::cin.ignore();
        S.resize(N);
        for (int i = 0; i < N; i++) {
            std::getline(std::cin, S[i]);
        }
        auto &value = out[index];
        mtx.unlock();
        value = solve(S);
    }
}

int main() {
    int T;
    std::cin >> T;
    std::vector<int64_t> out(T);
    int count = 0;
    std::vector<std::thread> threads(MAX_THREADS);
    for (int t = 0; t < MAX_THREADS; t++) {
        threads[t] = std::thread(parallel, std::ref(count), T, std::ref(out));
    }
    for (int t = 0; t < MAX_THREADS; t++) {
        threads[t].join();
    }
    for (int t = 0; t < T; t++) {
        printf("Case #%d: %lld\n", t + 1, out[t]);
    }
}
