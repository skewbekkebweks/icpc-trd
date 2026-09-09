const int k = 26;
 
struct vertex {
    vertex* to[k] = {0};
    vertex* go[k] = {0};
    vertex* link = nullptr;
    vertex* out_link = nullptr;
    vertex* p = nullptr;
    int pch = -1;
    bool term = false;
    vector<int> out;
    vertex(int _pch, vertex* _p) : p(_p), pch(_pch) {}
};
 
vertex* root = new vertex(-1, nullptr);
 
int cid(char c) {
    return c - 'a';
}
 
void add_string(const string& s, int id) {
    vertex* v = root;
    for (char ch : s) {
        int c = cid(ch);
        if (c < 0 || c >= k) {
            continue;
        }
        if (!v->to[c]) {
            v->to[c] = new vertex(c, v);
        }
        v = v->to[c];
    }
    v->term = true;
    v->out.push_back(id);
}
 
vertex* go(vertex* v, int c);
 
vertex* link(vertex* v) {
    if (v->link) {
        return v->link;
    }
    if (v == root || v->p == root) {
        return v->link = root;
    }
    return v->link = go(link(v->p), v->pch);
}
 
vertex* go(vertex* v, int c) {
    if (v->go[c]) {
        return v->go[c];
    }
    if (v->to[c]) {
        return v->go[c] = v->to[c];
    }
    if (v == root) {
        return v->go[c] = root;
    }
    return v->go[c] = go(link(v), c);
}
 
vertex* out_link(vertex* v) {
    if (v->out_link) {
        return v->out_link;
    }
    vertex* u = link(v);
    if (u == v) {
        return v->out_link = nullptr;
    }
    if (!u) {
        return v->out_link = nullptr;
    }
    if (u->term) {
        return v->out_link = u;
    }
    return v->out_link = out_link(u);
}
 
template<class f>
void find_all(const string& text, f on_match) {
    vertex* v = root;
    for (int i = 0; i < (int)text.size(); ++i) {
        int c = cid(text[i]);
        if (c < 0 || c >= k) {
            v = root;
            continue;
        }
        v = go(v, c);
        if (v->term) {
            for (int id : v->out) {
                on_match(i, id);
            }
        }
        for (vertex* u = out_link(v); u; u = out_link(u)) {
            for (int id : u->out) {
                on_match(i, id);
            }
        }
    }
}
