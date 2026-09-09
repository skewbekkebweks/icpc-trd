const int N = 100010;
int n, m;
vector<int> g[N * 2], rg[N * 2];
int used[N * 2];
vector<int> ts;

void dfs(int v) {
    used[v] = 1;
    for (int i: g[v]) {
        if (!used[i]) dfs(i);
    }
    ts.push_back(v);
}

void dfs2(int v, int c) {
    used[v] = c;
    for (int i: rg[v]) {
        if (!used[i])
            dfs2(i, c);
    }
}

void solve() {
    while (cin >> n >> m) {
        for (int i = 0; i < 2 * n; ++i)
            g[i] = rg[i] = {}, used[i] = 0;
        ts = {};
        for (int i = 1; i <= m; ++i) {
            int i1, e1, i2, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            g[i1 * 2 + (e1 ^ 1)].push_back(i2 * 2 + e2);
            rg[i2 * 2 + e2].push_back(i1 * 2 + (e1 ^ 1));
            g[i2 * 2 + (e2 ^ 1)].push_back(i1 * 2 + e1);
            rg[i1 * 2 + e1].push_back(i2 * 2 + (e2 ^ 1));
        }
        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) dfs(i);
        }
        for (int i = 0; i < 2 * n; ++i) {
            used[i] = 0;
        }
        reverse(all(ts));
        for (int i = 0, j = 1; i < 2 * n; ++i) {
            if (!used[ts[i]]) dfs2(ts[i], j++);
        }
        bool possible = true;
        for (int i = 0; i < n; ++i) {
            if (used[2 * i] == used[2 * i + 1]) {
                possible = false;
                break;
            }
        }
        for (int i = 0; i < n; ++i)
            cout << (used[i * 2] < used[i * 2 + 1] ? 1 : 0);
        cout << '\n';
    }
}
