vector<vector<int>> g;
vector<vector<int>> gr;
vector<bool> used;
vector<int> topsort;
vector<vector<int>> components;
map<int, int> vertex_to_comp;
void dfs(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    topsort.emplace_back(v);
}
void dfs2(int v) {
    used[v] = true;
    components.back().emplace_back(v);
    vertex_to_comp[v] = components.size() - 1;
    for (int u : gr[v]) {
        if (!used[u]) {
            dfs2(u);
        }
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    gr.resize(n);
    used.assign(n, false);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs(v);
        }
    }
    fill(used.begin(), used.end(), false);
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < n; ++i) {
        if (!used[topsort[i]]) {
            components.push_back(vector<int>());
            dfs2(topsort[i]);
        }
	}
}
