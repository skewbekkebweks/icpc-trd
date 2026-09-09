i64 MD1 = 1e9 + 7;
i64 MD2 = 1e9 + 9;
 
struct Mint {
    i64 x1, x2;
 
    Mint (i64 x = 0) : x1(((x % MD1) + MD1) % MD1), x2(((x % MD2) + MD2) % MD2) {}
    
    Mint (i64 x1, i64 x2) : x1(((x1 % MD1) + MD1) % MD1), x2(((x2 % MD2) + MD2) % MD2) {}
 
    friend Mint operator+(Mint l, Mint r) {
        return Mint(l.x1 + r.x1, l.x2 + r.x2);
    }
    friend Mint operator-(Mint l, Mint r) {
        return Mint(l.x1 - r.x1, l.x2 - r.x2);
    }
    friend Mint operator* (Mint l, Mint r) {
        return Mint(l.x1 * r.x1, l.x2 * r.x2);
    }
    friend bool operator==(Mint l, Mint r) {
        return l.x1 == r.x1 && l.x2 == r.x2;
    }
    friend bool operator!=(Mint l, Mint r) {
        return l.x1 != r.x1 || l.x2 != r.x2;
    }
    friend bool operator<(Mint l, Mint r) {
        return l.x1 < r.x1 || (l.x1 == r.x1 && l.x2 < r.x2);
    }
    void operator+=(Mint r) {
        *this = *this + r;
    }
    void operator-=(Mint r) {
        *this = *this - r;
    }
    void operator*=(Mint r) {
        *this = *this * r;
    }
};

Mint p = 179;
vector<Mint> degp;
 
int maxnum = 100000;

vector<Mint> h;

int n;
Mint hash_substring(int l, int r) {
    return (h[r + 1] - h[l]) * degp[n - l];
}

int main() {
    degp.resize(maxnum + 1);
    degp[0] = 1;
    for (int i = 1; i <= maxnum; ++i) {
        degp[i] = degp[i - 1] * p;
    }

    string s;
    cin >> s;

    n = s.size();

    h.resize(n + 1);
    h[0] = 0;
    for (int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] + degp[i - 1] * (s[i - 1] - 'a' + 1);
    }
}
