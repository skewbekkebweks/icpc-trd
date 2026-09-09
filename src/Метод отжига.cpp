const int n = 100;
const int k = 1000;
int f(vector<int> &p) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        int d = 1;
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(p[i] - p[j]))
                d = 0;
        s += d;
    }
    return s;
}
double rnd() { return double(rand()) / RAND_MAX; }
int main() {
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    mt19937 gen(random_device{}());
    shuffle(v.begin(), v.end(), gen);
    int ans = f(v);

    double t = 1;
	// USE clock() < CLOCKS_PER_SEC * 0.95 from #include <ctime>
    for (int i = 0; i < k && ans < n; i++) {
        t *= 0.99;
        vector<int> u = v;
        swap(u[rand() % n], u[rand() % n]);
        int val = f(u);
        if (val > ans || rnd() < exp((val - ans) / t)) {
            v = u;
            ans = val;
        }
    }

    for (int x : v)
        cout << x + 1 << " ";

    return 0;
}
