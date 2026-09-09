vector<int> build_pi(string_view p) {
    int m = (int)p.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) ++j;
        pi[i] = j;
    }
    return pi;
}
vector<int> kmp_search(string_view s, string_view p) { // find p in s
    vector<int> res;
    if (p.empty()) {
        res.reserve(s.size() + 1);
        for (int i = 0; i <= (int)s.size(); ++i) res.push_back(i);
        return res;
    }
    vector<int> pi = build_pi(p);
    int n = (int)s.size(), m = (int)p.size();
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && s[i] != p[j]) j = pi[j - 1];
        if (s[i] == p[j]) ++j;
        if (j == m) {
            res.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return res;
}
