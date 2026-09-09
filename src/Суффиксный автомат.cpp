const int K = 26;
struct sam {
    struct state {
        int link;
        int len;
        int next[K];
        state() {
            link = -1;
            len = 0;
            for (int i = 0; i < K; ++i) {
                next[i] = -1;
            }
        }
    };
    vector<state> st;
    int last;
    sam() {
        st.push_back(state());
        last = 0;
    }
    int cid(char c) {
        if ('A' <= c && c <= 'Z') {
            return c - 'A';
        }
        return c - 'a';
    }
    void extend_char(int c) {
        int cur = st.size();
        st.push_back(state());
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = clone;
                st[cur].link = clone;
            }
        }
        last = cur;
    }
    void extend_string(const string& s) {
        for (char ch : s) {
            int c = cid(ch);
            if (c < 0 || c >= K) {
                last = 0;
                continue;
            }
            extend_char(c);
        }
    }
    int count_distinct_substrings() {
        int ans = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }
    bool contains(const string& t) {
        int u = 0;
        for (char ch : t) {
            int c = cid(ch);
            if (st[u].next[c] == -1) {
                return false;
            }
            u = st[u].next[c];
        }
        return true;
    }
};
