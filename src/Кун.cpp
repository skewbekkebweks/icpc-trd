#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool dfs(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    g.resize(n);
    mt.resize(m, -1);

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        while (v != 0) {
            v--;
            g[i].emplace_back(v);
            cin >> v;
        }
    }

    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        if (dfs(i)) {
            cnt++;
        }
    }

    cout << cnt << '\n';
}
