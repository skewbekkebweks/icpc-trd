struct SegTree {
    struct node {
        ll add;
        ll sum;
    };

    vector<node> tree;
    int size = 1;
    const ll null = 0;

    void init(int n) {
        while (size < n) size *= 2;
    }

    void build(int n) {
        init(n);
        tree.assign(2 * size - 1, {0, 0});
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;

        tree[2 * x + 1].add += tree[x].add / 2;
        tree[2 * x + 1].sum += tree[x].add / 2;
        tree[2 * x + 2].add += tree[x].add / 2;
        tree[2 * x + 2].sum += tree[x].add / 2;

        tree[x].add = 0;
    }

    void modify(int l, int r, ll v, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (rx <= l || lx >= r) return;

        if (lx >= l && rx <= r) {
            tree[x].add += v * (rx - lx);
            tree[x].sum += v * (rx - lx);
            return;
        }

        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
    }

    void modify(int l, int r, ll v) {
        modify(l, r, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (rx <= l || lx >= r) return 0;
        if (lx >= l && rx <= r) return tree[x].sum;

        int m = (lx + rx) / 2;
        return  get(l, r, 2 * x + 1, lx, m) + get(l, r, 2 * x + 2, m, rx);
    }
    
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};
