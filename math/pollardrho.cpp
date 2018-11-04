/**
 * 快速质因数分解
 * 时间复杂度O(n^(1/4))
 **/ 
const int Times = 10;
const int N = 5500;
LL ct, cnt;
LL fac[N], num[N];
const LL primes[20]={2,5,7,61,97,37,101,13,11,997,2083,5807,7213,9907,10781,11897,14033,18013,43789,10009};
inline LL QuickMul(LL a, LL b, LL Mod) {
    LL res = 0; a %= Mod;
    for(; b; b >>= 1) {
        if(b & 1) res = (res + a) % Mod;
        a = (a + a) % Mod;
    }
    return res;
}
inline LL QuickPow(LL a, LL b, LL Mod) {
    LL res = 1; a %= Mod;
    for(; b; b >>= 1) {
        if(b & 1) res = QuickMul(res, a, Mod);
        a = QuickMul(a, a, Mod);
    }
    return res;
}
inline bool MillerRabin(LL x) {
    if(x == 2) return true;
    if(x < 2 || !(x & 1)) return false;
    LL m = x - 1, k = 0, a, res, f;
    for(;!(m & 1); k++, m >>= 1);
    for(int i = 0; i < Times; ++i) {
        a = rand() % (x - 1) + 1;
        res = QuickPow(a, m, x);
        f = 0;
        for(int j = 0; j < k; ++j) {
            f = QuickMul(res, res, x);
            if(f == 1 && res != 1 && res != x - 1) return false;
            res = f;
        }
        if(f != 1) return false;
    }
    return true;
}
inline LL PollardRho(LL n, LL c) {
    LL i = 1, k = 2, x = rand() % (n - 1) + 1, y = x, d;
    for(;;) {
        i++; x = (QuickMul(x, x, n) + c) % n;
        d = __gcd((y - x + n) % n, n);
        if (1 < d && d < n) return d;
        if (y == x) return n;
        if (i == k) {
            y = x; k <<= 1;
        }
    }
}
void Find(LL n, int c) {
    if (n == 1) return;
    if (MillerRabin(n)) {
        fac[ct++] = n;
        return;
    }
    LL p = n, k = c;
    while (p >= n) p = PollardRho(p, c--);
    Find(p, k); Find(n / p, k);
}
inline void Solve(LL n) {
    ct = 0;
    Find(n, 120);
    sort(fac, fac + ct);
    num[0] = 1;
    int k = 1;
    for(int i = 1; i < ct; ++i) {
        if(fac[i] == fac[i - 1]) ++num[k - 1];
        else num[k] = 1, fac[k++] = fac[i];
    }
    cnt = k;
}