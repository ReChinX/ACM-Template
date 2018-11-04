/**
 * 分解质因数版本
 **/
const int N = 500010;
int prime[N+5], check[N+5], tot;
ll qpow(ll a, ll b, ll mod) {
    ll ret = 1;
    while(b) {
        if(b&1) ret = (ret*a) % mod;
        a = (a*a) % mod; b >>= 1;
    }
    return ret;
}
void sieve() {
    memset(check, 0, sizeof(check)); tot = 0;
    for(int i = 2; i <= N; ++i) {
        if(!check[i]) {
            prime[tot++] = i;
        }
        for(int j = 0; j < tot; ++j) {
            if(i * prime[j] > N) break;
            check[i*prime[j]] = 1;
            if(i % prime[j] == 0) {
                break;
            }
        }
    }
}
int factor[N];
int primitive_root(ll p) {
    if(p == 2) return p;
    ll x = p - 1; int cnt = 0;
    for(int i = 0; 1LL*prime[i]*prime[i]<=x; ++i) {
        if(x%prime[i]==0) {
            factor[cnt++]=prime[i];
            while(x%prime[i]==0) x /= prime[i];
        }
    }
    if(x > 1) factor[cnt++] = x;
    for(int g = 2; g < p; ++g) {
        int flag = 1;
        for(int i = 0; i < cnt; ++i) {
            if(qpow(g, (p-1)/factor[i], p) == 1LL) {flag = 0; break;}
        }
        if(flag) return g;
    }
    return 0;
}
/**
 * 复杂度较低版本
 **/
bool check(int g, int p) {
    for (int i = 1; i < p - 1; i++)
        if (qpow(g, i, p) == 1) return false;
    return true;
}
int primitive_root(ll p) {
    int g = 2;
    for (; !checkf(g, p); g++);
    return g;
}