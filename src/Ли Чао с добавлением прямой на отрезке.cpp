struct Line {
    ll a, b;
    Line(ll a = 0, ll b = INF): a(a), b(b) {};
    ll getY(ll x) {
        return a * x + b;
    }
};

struct Node {
    Line L;
    Node(Line L = Line()): L(L) {};
};

const int N = 2e5, MOD = 2e5;
int q;
ll p = 0;
Node t[N * 20];

void insert_line(int v, ll tl, ll tr, Line l) {
    if (tl > tr) {
        return;
    }
    ll tm = tl + (tr - tl) / 2;
    Line l2 = t[v].L;
    int l_lower = l.getY(tl) < l2.getY(tl);
    int m_lower = l.getY(tm) < l2.getY(tm);
    if (m_lower) {
        swap(l, t[v].L);
    }
    if (tl == tr) {
        return;
    }
    if (l_lower ^ m_lower) {
        insert_line(v * 2, tl, tm, l);
    } else {
        insert_line(v * 2 + 1, tm + 1, tr, l);
    }
}

void update(int v, ll tl, ll tr, ll ql, ll qr, Line l) {
    if (tr < ql || qr < tl) {
        return;
    }
    if (ql <= tl && tr <= qr) {
        insert_line(v, tl, tr, l);
        return;
    }
    ll tm = tl + (tr - tl) / 2;
    update(v * 2, tl, tm, ql, qr, l);
    update(v * 2 + 1, tm + 1, tr, ql, qr, l);
}

ll get_min(int v, ll tl, ll tr, ll x) {
    if (tl > tr) {
        return INF;
    }
    ll res = t[v].L.getY(x), tm = tl + (tr - tl) / 2;
    if (tl == tr) {
        return res;
    }
    if (x <= tm) {
        res = min(res, get_min(v * 2, tl, tm, x));
        return res;
    } else {
        res = min(res, get_min(v * 2 + 1, tm + 1, tr, x));
        return res;
    }
}

void solve() {
    cin >> q;
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            ll a, b, l, r;
            cin >> a >> b >> l >> r;
            a += p, b += p;
            update(1, -N, N, l, r, Line(a, b));
        } else {
            ll x; cin >> x;
            p = get_min(1, -N, N, x);
            p = (p == INF ? -1 : p);
            cout << p << '\n';
            p = (p % MOD + MOD) % MOD;
        }
    }
}
