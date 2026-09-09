#include <numeric>
struct dsu {
    int n;
    vector<int> p;
    vector<int> r;
 
    dsu(int n) : n(n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        r.assign(n, 1);
    }
 
    int get(int a) {
        if (p[a] != a) {
            p[a] = get(p[a]);
        }
        return p[a];
    }
 
    void join(int a, int b) {
        a = get(a);
        b = get(b);
 
        if (a == b) {
            return;
        }
 
        if (r[a] == r[b]) {
            r[a]++;
        }
 
        if (r[a] > r[b]) {
            p[b] = a;
        } else {
            p[a] = b;
        }
    }
};
