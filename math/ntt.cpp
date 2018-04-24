/**
 * while(L < (n << 1)) L <<= 1
 * */
const LL N = 100005, P = 663224321, G = 3;
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