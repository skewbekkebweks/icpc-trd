vector <ll> res;
void eiler(ll v, vector <vector <pair <ll, ll>>>& gr, vector <char>& used) {
    for (ll i = 0; i < gr[v].size(); ++i) {
        ll to = gr[v][i].first;
        ll ind = gr[v][i].second;
        if (used[ind])
            continue;
        used[ind] = 1;
        eiler(to, gr, used);
    }
    res.push_back(v);
}
