struct edge {
    ll to, c, f;
};

const int N = 1010;
ll cur_flow, s, t;
ll d[N], ptr[N];
vector<int> g[N];
vector<edge> e;

void init() {
    for (int i = 1; i < N; ++i) {
        d[i] = inf;
        ptr[i] = 0;
    }
}

void add(ll a, ll b, ll c) {
    g[a].push_back(sz(e));
    e.push_back({b, c, 0});
    g[b].push_back(sz(e));
    e.push_back({a, 0, 0});
}

int bfs() {
    queue<ll> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        for (int i: g[v]) {
            if (e[i].c - e[i].f >= cur_flow && d[e[i].to] == inf) {
                d[e[i].to] = d[v] + 1;
                q.push(e[i].to);
            }
        }
    }
    return (d[t] != inf);
}

int dfs(ll v) {
    if (v == t)
        return 1;
    for (ll i = ptr[v]; i < sz(g[v]); ++i) {
        int num = g[v][i];
        if (d[e[num].to] == d[v] + 1 && e[num].c - e[num].f >= cur_flow) {
            int x = dfs(e[num].to);
            if (x) {
                e[num].f += cur_flow;
                e[num ^ 1].f -= cur_flow;
                return 1;
            }
        }
        ++ptr[v];
    }
    return 0;
}

ll max_flow() {
    ll res = 0;
    for (ll power = 32; power >= 0; --power) {
        cur_flow = (1ll << power);
        init();
        while (bfs()) {
            int x = dfs(s);
            while (x) {
                res += cur_flow;
                x = dfs(s);
            }
            init();
        }
    }
    return res;
}
