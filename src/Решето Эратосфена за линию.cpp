const int n = 1e6;

int d[n + 1];
vector<int> p;
 
for (int k = 2; k <= n; k++) {
    if (d[k] == 0) {
        d[k] = k;
        p.push_back(k);
    }
    for (int x : p) {
        if (x > d[k] || x * k > n)
            break;
        d[k * x] = x;
    }
}
