/**
 * example 
 * f(n) = \sum_^{i=0}^{n} C(k-1+n-i,n-i)a_i (mod 1e9 + 7)
 * */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N = 50005;
LL P, G = 3, MOD = 1e9 + 7, m1 = 998244353, m2 = 469762049, m3 = 1004535809;
inline LL qpow(LL a, LL b, LL mod) {
    LL ret = 1;
    while(b) {
        if(b & 1) ret = (ret * a) % mod;
        a = (a * a) % mod; b >>= 1;
    }
    return ret;
}
int w[2][N << 2], tot;
inline void pre(int n) {
    tot = n;
    LL g = qpow(G, (P - 1) / n, P), invg = qpow(g, P - 2, P);
    w[0][0] = w[1][0] = 1;
    for(int i = 1; i < n; ++i) {
        w[0][i] = w[0][i - 1] * g % P;
        w[1][i] = w[1][i - 1] * invg % P;
    }
}
inline void ntt(LL *x, int n, int r) { // zero for ntt and one for inverse
    for(int i = 0, j = 0; i < n; ++i) {
        if(i > j) swap(x[i], x[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1;
        for(int j = 0; j < n; j += i) {
            for(int k = 0; k < m; ++k) {
                LL z = x[j + m + k] * w[r][tot / i * k] % P;
                x[j + m + k] = (x[j + k] - z + P) % P;
                x[j + k] = (x[j + k] + z) % P;
            }
        }
    }
    if(r) for(int i = 0, inv = qpow(n, P - 2, P); i < n; ++i) x[i] = x[i] * inv % P;
}
inline LL mul(LL a,LL b,LL mod){
    a %= mod; b %= mod;
    return ((a * b - (LL)((LL)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}
inline LL crt(LL a1, LL a2, LL a3) {
    LL M = m1 * m2;
    LL A = (mul(a1 * m2 % M, qpow(m2 % m1, m1 - 2, m1), M) + mul(a2 * m1 % M, qpow(m1 % m2, m2 - 2, m2), M)) % M;
    LL k = ((a3 - A) % m3 + m3) % m3 * qpow(M % m3, m3 - 2, m3) % m3;
    return ((k % MOD) * (M % MOD) % MOD + A % MOD) % MOD;
}
int n, L;
LL k, a[N << 2], b[N << 2], x[N << 2], ans[3][N], inv[N];
int main() {
    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    L = 1; while(L < (n << 1)) L <<= 1;
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= n; ++i) inv[i] = (-(MOD / i) * inv[MOD % i] % MOD + MOD) % MOD;
    P = 998244353;
    pre(L);
    x[0] = 1; b[0] = a[0];
    for(int i = 1; i < n; ++i) x[i] = (x[i - 1] * (k + i - 1) % MOD * inv[i] % MOD) % MOD, b[i] = a[i];
    for(int i = n; i < L; ++i) x[i] = 0, b[i] = 0;
    ntt(b, L, 0); ntt(x, L, 0);
    for(int i = 0; i < L; ++i) b[i] = b[i] * x[i];
    ntt(b, L, 1);
    for(int i = 0; i < n; ++i) ans[0][i] = b[i];
    P = 469762049;
    pre(L);
    x[0] = 1; b[0] = a[0];
    for(int i = 1; i < n; ++i) x[i] = (x[i - 1] * (k + i - 1) % MOD * inv[i] % MOD) % MOD, b[i] = a[i];
    for(int i = n; i < L; ++i) x[i] = 0, b[i] = 0;
    ntt(b, L, 0); ntt(x, L, 0);
    for(int i = 0; i < L; ++i) b[i] = b[i] * x[i];
    ntt(b, L, 1);
    for(int i = 0; i < n; ++i) ans[1][i] = b[i];
    P = 1004535809;
    pre(L);
    x[0] = 1;b[0] = a[0];
    for(int i = 1; i < n; ++i) x[i] = (x[i - 1] * (k + i - 1) % MOD * inv[i] % MOD) % MOD, b[i] = a[i];
    for(int i = n; i < L; ++i) x[i] = 0, b[i] = 0;
    ntt(b, L, 0); ntt(x, L, 0);
    for(int i = 0; i < L; ++i) b[i] = b[i] * x[i];
    ntt(b, L, 1);
    for(int i = 0; i < n; ++i) ans[2][i] = b[i];
    for(int i = 0; i < n; ++i) {
        cout << crt(ans[0][i], ans[1][i], ans[2][i]) << endl;
    }
    return 0;
}