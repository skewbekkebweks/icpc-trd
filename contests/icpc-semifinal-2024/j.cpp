#include <bits/stdc++.h>
#define int long long
using namespace std;

const int inf = 1e18;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> tasks(n);
    vector<int> l(m), t(q);
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].second;
    }
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].first;
    }
    for (int i = 0; i < m; ++i) cin >> l[i];
    for (int i = 0; i < q; ++i) cin >> t[i];

    vector<int> l_pref(m + 1, 0);
    for (int i = 0; i < m; ++i) {
        l_pref[i + 1] = l_pref[i] + l[i];
    }

    sort(tasks.begin(), tasks.end());
    vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + tasks[i].second;
    }
    vector<int> suf(n + 1);
    suf[n] = inf;
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = min(tasks[i].first, suf[i + 1]) - tasks[i].second;
    }
    for (int i = 0; i < q; ++i) {
        auto it = lower_bound(suf.begin(), suf.end(), t[i]);
        int ind = it - suf.begin();
        // [ind, n) -- back
        int time_left = t[i] - pref[ind];
        int cnt = upper_bound(l_pref.begin(), l_pref.end(), time_left) - l_pref.begin() - 1;

        if (ind == 0) {
            cout << cnt << ' ';
            continue;
        }
        ind--;
        time_left = suf[ind] - pref[ind];
        cnt = max<int>(cnt, upper_bound(l_pref.begin(), l_pref.end(), time_left) - l_pref.begin() - 1);
        cout << cnt << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}