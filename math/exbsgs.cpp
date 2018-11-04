/**
 * 用于求解最小的非负整数$x$满足$a^x \equiv b \pmod{p}$
 * p为任意整数
 * 时间复杂度O(\sqrt n)
 **/ 
typedef long long LL;
struct Hash{
    static const LL HASH_MOD = 99991;
    LL Hash[HASH_MOD], head[HASH_MOD], nxt[HASH_MOD], id[HASH_MOD], top;
    inline void Init() {
        memset(head, -1, sizeof(head));
        top = 1;
    }
    inline void Insert(LL x, LL y) {
        LL k = x % HASH_MOD;
        Hash[top] = x;
        id[top] = y;
        nxt[top] = head[k];
        head[k] = top++;
    }
    inline LL Find(LL x) {
        LL k = x % HASH_MOD;
        for(LL i = head[k]; ~i; i = nxt[i]) {
            if(Hash[i] == x) return id[i];
        }
        return -1;
    }
}has;
LL ExBSGS(LL a, LL b, LL p) {
    has.Init();
    a %= p; b %= p;
    if(b == 1LL) return 0LL;
    LL C = 1LL, k = 0, d, j;
    while((d = __gcd(a, p)) != 1) {
        if(b % d) return -1;
        k++; b /= d; p /= d; C = (C * a / d) % p;
        if(b == C) return k;
    }
    LL m = ceil(sqrt(p * 1.0)), t = 1LL;
    for(LL i = 0; i <= m; i++) {
        if(i == 0) has.Insert(b, i);
        else t = t * a % p, has.Insert(t * b % p, i);
    }
    for(LL i = 1; i <= m; i++) {
        C = C * t % p; if((j = has.Find(C)) != -1) return i * m - j + k;
    }
    return -1;
}