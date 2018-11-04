/**
 * 用于求解最小的非负整数$x$满足$a^x \equiv b \pmod{p}$
 * 时间复杂度O(\sqrt n)
 **/ 
typedef long long LL;
struct Hash{
    static const LL HASH_MOD = 76543;
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
LL BSGS(LL a, LL b, LL p) {
    has.Init();
    if(b == 1) return 0LL;
    LL m = ceil(sqrt(p * 1.0)), x = 1, t = 1, j;
    for(LL i = 0; i < m; i++) has.Insert(t * b % p, i), t = t * a % p;
    for(LL i = m; i <= p; i += m) {
        j = has.Find(x * t % p); if(j != -1) return i - j; x = x * t % p;
    }
    return -1;
}