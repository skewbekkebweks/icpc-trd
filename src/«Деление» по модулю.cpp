const int mod = 1e9 + 7;
int binpow(int a, int n) {
    int res = 1;
    while (n != 0) {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int inv(int x) {
    return binpow(x, mod - 2);
}
