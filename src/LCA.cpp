const int N = 1000010, LOG = 21;
vector <int> g[N];
int tin[N], tout[N], timer = 0;
int up[LOG][N];

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[0][v] = (p == -1 ? v : p);
    for (int i = 1; i < LOG; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int i : g[v]) {
        if (i == p) {
            continue;
        }
        dfs(i, v);
    }
    tout[v] = timer;
}

int upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int LCA(int a, int b) {
    if (upper(a, b)) {
        return a;
    }
    if (upper(b, a)) {
        return b;
    }
    for (int i = LOG - 1; i >= 0; --i) {
        if (!upper(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}
