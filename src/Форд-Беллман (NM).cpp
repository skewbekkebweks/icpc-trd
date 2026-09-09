void Ford_Bellman(int start) {
    for (int i = 1; i <= n; ++i)
        d[i] = INF;
    d[start] = 0;
    vector<int> cnt(n + 1, 0);
    queue<pair<int, int> > q;
    q.push({start, 0});
    while (!q.empty()) {
        auto [v, dist] = q.front();
        q.pop();
        if (dist > d[v])
            continue;
        for (auto [i, w]: g[v]) {
            if (d[v] + w < d[i]) {
                d[i] = d[v] + w;
                cnt[i] = cnt[v] + 1;
                if (cnt[i] >= n)
                    return; // отрицательный цикл
                q.push({i, d[i]});
            }
        }
    }
}
