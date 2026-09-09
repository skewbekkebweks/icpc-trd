vector<vector<pii>> g;
vector<int> fr, used, e;
void dfs(int v) {
	while (fr[v] < sz(g[v])) {
		auto &[to, id] = g[v][fr[v]];
		++fr[v];
		if (used[id])
			continue;
		used[id] = true;
		dfs(to);
	}
	e.eb(v);
}
void solve() {
	int n, m;
    vector<int> odd;
	vector<pii> edges;
    // INPUT
    fr.resize(n);
	g.resize(n);
	for (auto &[u, v] : edges) {
		g[u].emplace_back(v, m);
		g[v].emplace_back(u, m++);
	}
	int v1 = 0, v2;
	bool f = false;
	if (odd.size() == 2) {
		v1 = odd[0];
		v2 = odd[1];
		g[v1].emplace_back(v2, m);
		g[v2].emplace_back(v1, m++);
		odd.clear();
		f = true;
	}
	if (!odd.empty()) {
		cout << -1;
		return;
	}
	used.resize(m);
	dfs(v1);
	if (f) {
		for (int i = 0; i < m - 1; ++i) {
			if (e[i] == v1 && e[i + 1] == v2 || e[i] == v2 && e[i + 1] == v1) {
				vector<int> new_e(e.begin() + i + 1, e.end());
				new_e.insert(new_e.end(), e.begin(), e.begin() + i);
				e = new_e;
				break;
			}
		}
		--m;
	}
	// euler tour in e
}
