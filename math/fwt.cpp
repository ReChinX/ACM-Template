/**
 * xor fwt
 * c_k=\sum_{i \oplus j} a_i*b_j
 **/
const int MOD = 1e9+7;
ll qpow(ll a, ll b, ll mod) {
    ll ret = 1;
    while(b) {
        if(b&1) ret = (ret * a) % mod;
        a = (a * a) % mod; b >>= 1;
    }
    return ret;
}
ll inv = qpow(2, MOD-2, MOD);
void fwt_xor(ll *a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                ll x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % MOD;
                a[i + j + d] = (x - y + MOD) % MOD;
            }
}
void ufwt_xor(ll *a, int n) {
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i += m)
            for (int j = 0; j < d; j++) {
                ll x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) * inv % MOD;
                a[i + j + d] = ((x - y) * inv % MOD + MOD) % MOD;
            }
}