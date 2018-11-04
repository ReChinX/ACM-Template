/**
 * 线性预处理阶乘及逆元
 * fac阶乘，inv逆元，finv阶乘逆元
 **/
int finv[N], fac[N], inv[N];
void precalc() {
    fac[0] = 1; 
    for(int i = 1; i < N; ++i) {
        fac[i] = 1LL*fac[i - 1] * i % MOD;
    }
    inv[1] = 1;
    for(int i = 2; i < N; ++i) {
        inv[i] = (ll)(MOD-MOD/i)*inv[MOD%i]%MOD;
    }
    finv[0] = 1;
    for(int i = 1; i < N; ++i) {
        finv[i] = 1LL*finv[i-1]*inv[i]%MOD;
    }
}