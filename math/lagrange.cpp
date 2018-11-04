const int N = 10005;
LL inv[N], buf[N];
inline void init(int d) {
    inv[1] = 1;
    for (int i = 2; i < d; ++i) inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
}
inline LL lagrange(LL *vals, LL d, LL x) { // d for deg + 1, x for required value
    if(x < d) return vals[x];
    LL tmp = 1, ret = 0;
    for (int i = 1; i < d; ++ i) {
        tmp = tmp * (x - i + 1) % MOD * inv[i] % MOD;
        buf[i] = tmp * vals[i] % MOD;
    }
    tmp = 1; ret = buf[d - 1];
    for (int i = d - 2; i >= 0; -- i) {
        tmp = (MOD - tmp) * inv[d - 1 - i] % MOD * (x - i - 1) % MOD;
        ret = (ret + buf[i] * tmp % MOD) % MOD;
    }    
    return ret;
}