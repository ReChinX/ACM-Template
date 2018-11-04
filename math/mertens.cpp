/**
 * 杜教筛求解莫比乌斯函数前缀和
 * 预处理前k个莫比乌斯函数前缀和
 * k=n^{2/3}复杂度最优为$O(n^{2/3})$
 **/
map<ll, int> mp;
ll mertens(ll x) {
    if(x < N) return mu[x];
    if(mp.count(x)) return mp[x];
    ll ret = 0;
    for(ll i = 2, last; i <= x; i = last+1) {
        last = x/(x/i);
        ret += (last - i + 1)*mertens(x/i);
    }
    return mp[x] = 1-ret;
}