#include <cstring>
#include <iostream>

using namespace std;

using i32 = int;
using i64 = long long;

const int maxn = 1e5 + 1;
const int logn = 17;

int a[maxn], mn[logn][maxn];

int rmq(int l, int r) {
    int t = __lg(r - l + 1);
    return min(mn[t][l], mn[t][r + 1 - (1 << t)]);
}

int main() {
    int n, m;

    memcpy(mn[0], a, sizeof a);
    for (int l = 0; l < logn - 1; ++l) {
        for (int i = 0; i + (2 << l) <= n; ++i) {
            mn[l + 1][i] = min(mn[l][i], mn[l][i + (1 << l)]);
        }
    }

    int ansi = rmq(min(u, v) - 1, max(u, v) - 1);

    for (int i = 1; i < m; ++i) {
        ansi = rmq(min(u, v) - 1, max(u, v) - 1);
    }

    return 0;
}
