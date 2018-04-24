/**
 * n is 2^{k} and is larger than the length of polynomial
 **/
void poly_inverse(int n, LL *a, LL *b, LL *tmp) {
    if(n == 1) {b[0] = qpow(a[0], P - 2, P); return;}
    poly_inverse((n + 1) >> 1, a, b, tmp);
    int len = 1; while(len < (n << 1)) len <<= 1;
    for(int i = 0; i < n; ++i) tmp[i] = a[i];
    for(int i = n; i < len; ++i) tmp[i] = 0;
    ntt(tmp, len, 0); ntt(b, len, 0);
    for(int i = 0; i < len; ++i) {
        b[i] = (2 - tmp[i] * b[i] % P + P) % P * b[i] % P;
    }
    ntt(b, len, 1);
    for(int i = n; i < len; ++i) b[i] = 0;
}