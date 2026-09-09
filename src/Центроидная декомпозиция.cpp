const int N = 100010, LOG = 20;
vector<int> g[N];
int cent[N], _size[N], pr[N][LOG];
vector<int> a;
// TODO fill(cent, cent + N, -1)
int dfs(int v, int p) {
    if (cent[v] != -1)
        return 0;
    _size[v] = 1;
    for (int i: g[v]) {
        if (i == p)
            continue;
        _size[v] += dfs(i, v);
    }
    a.push_back(v);
    return _size[v];
}

void dfs2(int v, int p, int c, int level) {
    if (cent[v] != -1)
        return;
    pr[v][level] = c;
    for (int i: g[v]) {
        if (i == p)
            continue;
        dfs2(i, v, c, level);
    }
}

void find_centroid(int v, int level) {
    a.clear();
    int s = dfs(v, -1);
    for (int i: a) {
        if (_size[i] > s / 2) {
            v = i;
            break;
        }
    }
    dfs2(v, -1, v, level);
    cent[v] = level;
    for (int i: g[v]) {
        if (cent[i] != -1)
            find_centroid(i, level + 1);
    }
}