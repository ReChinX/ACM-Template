/**
 * 大组合数取模
 * p为一般整数
 **/
typedef long long LL;
inline LL QuickPow(LL a, LL b, LL MOD) {
    LL res = 1LL;
    while(b) {
        if(b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
void Exgcd(LL a, LL b, LL &x, LL &y) {
    if(!b) x = 1LL, y = 0LL;
    else Exgcd(b, a % b, y, x), y -= a / b * x;
}
inline LL Inv(LL A, LL MOD) {
    if(!A) return 0LL;
    LL a = A, b = MOD, x = 0LL, y = 0LL;
    Exgcd(a, b, x, y);
    x = ((x % b) + b) % b;
    if(!x) x += b;
    return x;
}
LL Mul(LL n, LL p, LL pk) {
    if (!n) return 1LL;
    LL ans = 1LL;
    for (LL i = 2; i <= pk; ++i) if (i % p) ans = ans * i % pk;
    ans = QuickPow(ans, n / pk, pk);
    for (LL i = 2; i <= n % pk; ++i) if (i % p) ans = ans * i % pk;
    return ans * Mul(n / p, p, pk) % pk;
}

inline LL C(LL n, LL m, LL MOD, LL p, LL pk) {
    if (m > n) return 0LL;
    LL a = Mul(n, p, pk), b = Mul(m, p, pk), c = Mul(n - m, p, pk);
    LL k = 0LL, ans;
    for (LL i = n; i; i /= p) k += i / p;
    for (LL i = m; i; i /= p) k -= i / p;
    for (LL i = n - m; i; i /= p) k -= i / p;
    ans = a * Inv(b, pk) % pk * Inv(c, pk) % pk * QuickPow(p, k, pk) % pk;
    return ans * (MOD / pk) % MOD * Inv(MOD / pk, pk) % MOD;
}
inline LL ExLucas(LL n, LL m, LL p) {
    LL res = 0LL, x = p;
    for (LL i = 2; i * i <= p; ++i) {
        if (x % i == 0) {
            LL pk = 1LL;
            while (x % i == 0) pk *= i, x /= i;
            res = (res + C(n, m, p, i, pk)) % p;
        }
    }
    if(x > 1) res = (res + C(n, m, p, x, x)) % p;
    return res;
}