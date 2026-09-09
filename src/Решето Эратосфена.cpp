vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            for (int j = 2 * i; j <= n; j += i)
                is_prime[j] = false;
    return is_prime;            
}
