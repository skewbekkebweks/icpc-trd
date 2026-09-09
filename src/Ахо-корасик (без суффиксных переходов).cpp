struct node {
    int nxt[26];
    int term = 0;
    int p = -1;
    int pch;
    int link = -1, super_link = -1;

    node(int p = -1, int ch = -1) : p(p), pch(ch) {
        fill(begin(nxt), end(nxt), 0);
    }
};

vector<node> trie(1);

void add(string &s) {
    int v = 0;
    for (char ch: s) {
        int c = ch - 'a';
        if (trie[v].nxt[c] == 0) {
            trie[v].nxt[c] = sz(trie);
            trie.emplace_back(v, c);
        }
        v = trie[v].nxt[c];
    }
    trie[v].term = 1;
}

void bfs() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int c: trie[v].nxt) {
            if (c != 0)
                q.push(c);
        }
        if (v == 0) {
            trie[v].link = trie[v].super_link = 0;
            continue;
        }
        if (trie[v].p == 0) {
            trie[v].link = trie[v].super_link = 0;
        } else {
            trie[v].link = trie[trie[trie[v].p].link].nxt[trie[v].pch];
            trie[v].super_link = (trie[trie[v].link].term ? trie[v].link : trie[trie[v].link].super_link);
        }
        for (int c = 0; c < 26; ++c) {
            if (trie[v].nxt[c] == 0)
                trie[v].nxt[c] = trie[trie[v].link].nxt[c];
        }
    }
}
