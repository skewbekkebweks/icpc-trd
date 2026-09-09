int levenshtein(const string& A, const string& B) {
    int n = (int)A.size(), m = (int)B.size();
    vector<int> prev(m+1), cur(m+1);
    iota(prev.begin(), prev.end(), 0); // dp[0][j] = j
    for (int i = 1; i <= n; ++i) {
        cur[0] = i; // dp[i][0] = i
        for (int j = 1; j <= m; ++j) {
            int cost = (A[i-1] == B[j-1]) ? 0 : 1;
            cur[j] = min({
                prev[j] + 1,        // delete A[i-1]
                cur[j-1] + 1,       // insert B[j-1]
                prev[j-1] + cost    // replace/match
            });
        }
        swap(prev, cur);
    }
    return prev[m];
}
