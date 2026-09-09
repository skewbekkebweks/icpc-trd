#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int INF = 1e9;

struct Edge {
    int to;
    int rev;
    int flow;
    int capacity;
};

vector<Edge> edges;
vector<vector<int>> g;
vector<int> dist;
vector<int> current_edge;
int S, T;
int total_flow = 0;

int dfs(int v, int min_capacity) {
    if (v == T) {
        return min_capacity;
    }
    
    for (; current_edge[v] < g[v].size(); ++current_edge[v]) {
        int i = g[v][current_edge[v]];
        Edge& e = edges[i];
        
        if (dist[e.to] == dist[v] + 1 && e.capacity - e.flow > 0) {
            int flow = dfs(e.to, min(min_capacity, e.capacity - e.flow));
            if (flow > 0) {
                e.flow += flow;
                edges[e.rev].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

bool bfs() {
    fill(dist.begin(), dist.end(), -1);
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        for (int i : g[v]) {
            Edge& e = edges[i];
            if (e.capacity - e.flow > 0 && dist[e.to] == -1) {
                dist[e.to] = dist[v] + 1;
                q.push(e.to);
            }
        }
    }

    return dist[T] != -1;
}

void max_flow() {
    while (bfs()) {
        fill(current_edge.begin(), current_edge.end(), 0);
        while (true) {
            int flow = dfs(S, INF);
            if (flow <= 0) {
                break;
            }
            total_flow += flow;
        }
    }
}

void add_edge(int from, int to, int capacity) {
    int forward_edge = edges.size();
    int backward_edge = forward_edge + 1;
    
    g[from].push_back(forward_edge);
    g[to].push_back(backward_edge);
    
    edges.push_back({to, backward_edge, 0, capacity});
    edges.push_back({from, forward_edge, 0, 0});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    g.resize(n);
    current_edge.resize(n);
    dist.resize(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v;
        --u; --v;
        
        add_edge(u, v, 1);
        add_edge(v, u, 1);
    }
    
    S = 0;
    T = n - 1;
    max_flow();
    
    cout << total_flow << '\n';
    
    for (int i = 0; i < edges.size(); i += 4) {
        int flow = edges[i].flow;
    }
    
    return 0;
}
