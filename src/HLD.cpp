const int N = 1e5 + 1;
vector<int> g[N];
int sz[N], p[N], tin[N], tout[N], head[N], t[N * 10];
int timer = 1, n;

void sizes(int v, int anc) {
    sz[v] = 1;
    for (int &i: g[v]) {
        if (i == anc)
            continue;
        p[i] = v;
        sizes(i, v);
        sz[v] += sz[i];
        if (sz[i] > sz[g[v][0]])
            swap(i, g[v][0]);
    }
}

void hld(int v, int anc) {
    tin[v] = timer++;
    for (int i: g[v]) {
        if (i == anc)
            continue;
        head[i] = (i == g[v][0] ? head[v] : i);
        hld(i, v);
    }
    tout[v] = timer;
}

int upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int get(int v, int tl, int tr, int ql, int qr) {
    if (qr < tl || tr < ql)
        return -inf;
    if (ql <= tl && tr <= qr)
        return t[v];
    int m = (tl + tr) >> 1;
    return max(get(v * 2, tl, m, ql, qr), get(v * 2 + 1, m + 1, tr, ql, qr));
}

void add(int v, int tl, int tr, int pos, int x) {
    if (tl == tr) {
        t[v] += x;
        return;
    }
    int m = (tl + tr) >> 1;
    if (pos <= m) add(v * 2, tl, m, pos, x);
    else add(v * 2 + 1, m + 1, tr, pos, x);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

void up(int &a, int &b, int &res) {
    while (!upper(head[a], b)) {
        res = max(res, get(1, 1, timer, tin[head[a]], tin[a]));
        a = p[head[a]];
    }
}

int get_max(int a, int b) {
    int res = -inf;
    up(a, b, res);
    up(b, a, res);
    if (!upper(a, b))
        swap(a, b);
    res = max(res, get(1, 1, timer, tin[a], tin[b]));
    return res;
}
//TODO p[root] = head[root] = root;
