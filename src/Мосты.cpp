void dfs(int v, int height, int prev) {
    used[v] = true;
    h[v] = height;
    d[v] = height;
    for (auto [u, i] : g[v]) {
        if (!used[u]) {
            dfs(u, height + 1, v);
        }
        if (u != prev) {
            d[v] = min(d[v], d[u]);
            if (d[u] > h[v]) {
                bridges.emplace_back(i);
            }
        }
    }
}
void find_bridges() {
	for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs(v, 0, -1);
        }
    }

}
