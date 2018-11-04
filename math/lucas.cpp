/**
 * 大组合数取模
 * O（log_p n）
 **/
typedef long long LL;
LL QuickPow(LL a, LL b, LL MOD) {
    LL res = 1;
    while(b) {
        if(b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
LL Inv(LL x, LL MOD) {
    return QuickPow(x, MOD -2 , MOD);
}
LL C(LL n, LL m, LL MOD) {
    if(m > n) return 0LL;
    LL up = 1LL, down = 1LL;
    for(LL i = n - m + 1; i <= n; i++) up = (up * i) % MOD;
    for(LL i = 1; i <= m; i++) down = (down * i) % MOD;
    return (up * Inv(down, MOD)) % MOD;
}
LL Lucas(LL n, LL m, LL MOD) {
    if(m > n) return 0LL;
    LL ans = 1;
    for(; m; m /= MOD, n /= MOD) {
        ans = (ans * C(n % MOD, m % MOD, MOD)) % MOD;
    }
    return ans;
}