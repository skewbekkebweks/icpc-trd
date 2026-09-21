#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> c(n);
    vector<int> c_ord(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        c[i]--;
        c_ord[c[i]] = i;
    }

    vector<pair<int, int>> moves;

    vector<int> cur(n);
    vector<int> cur_ord(n);
    for (int i = 0; i < n; ++i) {
        cur[i] = i;
        cur_ord[cur[i]] = i;
    }

    for (int i = 0; i < n; ++i) {
        int pos = cur_ord[c[i]];
        for (int j = pos + 1; j < n; ++j) {
            moves.push_back({cur[j], cur[j - 1]});
            cur_ord[cur[j]] = j - 1;
            cur_ord[cur[j - 1]] = j;
            swap(cur[j], cur[j - 1]);
        }
        for (int j = n - 1; j >= i + 1; --j) {
            moves.push_back({cur[j], cur[j - 1]});
            cur_ord[cur[j]] = j - 1;
            cur_ord[cur[j - 1]] = j;
            swap(cur[j], cur[j - 1]);
        }
    }

    cout << moves.size() << '\n';
    for (auto p : moves) {
        cout << p.first + 1 << ' ' << p.second + 1 << '\n';
    }
}