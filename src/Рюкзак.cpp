for i in range(1, n + 1):
    for j in range(0, W + 1):
        dp[i][j] = dp[i - 1][j]
        if a[i] <= j:
            dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i]] + c[i])
