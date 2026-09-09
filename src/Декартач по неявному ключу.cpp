mt19937 Rand(chrono::steady_clock::now().time_since_epoch().count());
struct Node {
    Node *l, *r;
    int x;
    int g;
    int sz;
    int y;
    Node(int x) : x(x), g(x), sz(1) {
        y = (int)Rand();
        l = r = nullptr;
    }
};

Node *treap = nullptr;

int get_sz(Node *t) {
    return t ? t->sz : 0;
}

int get_g(Node *t) {
    return t ? t->g : 0;
}

void recalc(Node *t) {
    if (!t) return;
    t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    t->g = t->x;
    t->g = gcd(t->g, get_g(t->l));
    t->g = gcd(t->g, get_g(t->r));
}

Node *merge(Node *t1, Node *t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    if (t1->y >= t2->y) {
        t1->r = merge(t1->r, t2);
        recalc(t1);
        return t1;
    } else {
        t2->l = merge(t1, t2->l);
        recalc(t2);
        return t2;
    }
}

pair<Node*, Node*> split(Node *t, int k) {
    if (!t) {
        return {nullptr, nullptr};
    }
    int left_sz = get_sz(t->l);
    if (left_sz >= k) {
        auto [a, b] = split(t->l, k);
        t->l = b;
        recalc(t);
        return {a, t};
    } else {
        auto [a, b] = split(t->r, k - left_sz - 1);
        t->r = a;
        recalc(t);
        return {t, b};
    }
}

int get_gcd(int l, int r) {
    auto [a, bc] = split(treap, l);
    auto [b, c] = split(bc, r - l + 1);
    int ans = get_g(b);
    treap = merge(a, merge(b, c));
    return ans;
}

void update(int pos, int x) {
    auto [a, bc] = split(treap, pos);
    auto [b, c] = split(bc, 1);
    delete b;
    treap = merge(a, merge(new Node(x), c));
}

void insert(int pos, int x) {
    auto [a, b] = split(treap, pos);
    treap = merge(a, merge(new Node(x), b));
}

void erase(int pos) {
    auto [a, bc] = split(treap, pos);
    auto [b, c] = split(bc, 1);
    delete b;
    treap = merge(a, c);
}
