#include <bits/stdc++.h>
//#include <bits/extc++.h>
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
//using namespace __gnu_pbds;
using ll = long long;
//using lll = __int128_t;
using ull = unsigned long long;
//#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int)(v).size()
using ld = long double;
//using ordered_set = tree<int, null_type, less<>, rb_tree_tag,
//      tree_order_statistics_node_update>;
const int inf = 1000000000;
const ll INF = (ll)inf * (ll)inf;
const ld EPS = 1e-9;
const ld PI = 3.141592653589793238462643383279;
mt19937 Rand(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());

const int N = 2e5 + 10;
bool vis[N], added[N] = {false, };
vector<int> g[N], t[4], block[4];
int n, m, type[N];

void init() {
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
    }
}

void bfs(vector<int>& s) {
    queue<int> q;
    for (int v : s) {
        q.push(v);
        vis[v] = true;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i : g[v]) {
            if (!vis[i]) {
                vis[i] = true;
                q.push(i);
            }
        }
    }
}

void topsort(int v, vector<int>& ts) {
    vis[v] = true;
    for (int i : g[v]) {
        if (!vis[i]) {
            topsort(i, ts);
        }
    }
    ts.push_back(v);
}

void reorder(vector<int>& b) {
    init();
    vector<int> ts;
    for (int v : b) {
        if (!vis[v]) {
            topsort(v, ts);
        }
    }
    reverse(all(ts));
    vector<int> ord(n + 1);
    for (int i = 0; i < ts.size(); ++i) {
        ord[ts[i]] = i;
    }
    sort(all(b), [&](int i, int j) {
        return ord[i] < ord[j];
    });
}

void solve() {
    cin >> n;
    string com, val;
    for (int i = 1; i <= n; ++i) {
        cin >> com >> val;
        if (com == "set" && val == "true") {
            t[0].push_back(i);
            type[i] = 0;
        } else if (com == "set" && val == "false") {
            t[1].push_back(i);
            type[i] = 1;
        } else if (com == "unset" && val == "true") {
            t[2].push_back(i);
            type[i] = 2;
        } else {
            t[3].push_back(i);
            type[i] = 3;
        }
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    vector<int> s;

    if (t[2].size() > 1) {
        cout << -1;
        return;
    }

    if (!t[2].empty()) {
        s = t[2];
        init();
        bfs(s);
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) {
                if (type[i] == 0 || type[i] == 1) {
                    cout << -1;
                    return;
                }
                if (type[i] == 3) {
                    block[2].push_back(i);
                    added[i] = true;
                }
            }
        }
        added[s[0]] = true;
    }

    if (!t[1].empty()) {
        s = t[1];
        init();
        bfs(s);
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) {
                if (type[i] == 0) {
                    cout << -1;
                    return;
                }
                if (type[i] == 3 && !added[i]) {
                    block[2].push_back(i);
                    added[i] = true;
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (type[i] == 1) {
                block[1].push_back(i);
                added[i] = true;
            }
        }
    }

    if (t[0].size() > 1) {
        cout << -1;
        return;
    }

    if (!t[0].empty()) {
        s = t[0];
        init();
        bfs(s);
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) {
                if (type[i] == 3 && !added[i]) {
                    block[2].push_back(i);
                    added[i] = true;
                }
            }
        }
        added[s[0]] = true;
    }

    for (int i = 1; i <= n; ++i) {
        if (type[i] == 3 && !added[i]) {
            block[0].push_back(i);
        }
    }

    if (!block[2].empty() && t[2].empty()) {
        cout << -1;
        return;
    }
    if (!block[1].empty() && t[0].empty()) {
        cout << -1;
        return;
    }

    reorder(block[0]);
    reorder(block[1]);
    reorder(block[2]);

    for (int v : block[0]) cout << v << ' ';
    if (!t[0].empty()) cout << t[0][0] << ' ';
    for (int v : block[1]) cout << v << ' ';
    if (!t[2].empty()) cout << t[2][0] << ' ';
    for (int v : block[2]) cout << v << ' ';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << setprecision(10) << fixed;
    //freopen("1_27_B.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    auto start = chrono::steady_clock::now();
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
    auto end = chrono::steady_clock::now();
    auto diff = chrono::duration_cast<chrono::milliseconds>(end - start);
    //cout << "\nTIME: " << diff.count();
}