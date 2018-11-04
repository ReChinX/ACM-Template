/**
 * O(\sqrt(n))分解质因子
 **/
ll factor[50]; int f_cnt = 0, f_exp[50];
void get_factor(ll x) {
    f_cnt = 0; ll n = x;
    for(int i = 0; i < tot; ++i) {
        if(1LL * prime[i] * prime[i] > n) break;
        if(x % prime[i] == 0) {
            f_exp[f_cnt] = 0;
            while(x % prime[i] == 0) {
                x /= prime[i]; f_exp[f_cnt]++;
            }
            factor[f_cnt++] = prime[i];
        }
    }
    if(x > 1) {
        f_exp[f_cnt] = 1; factor[f_cnt++] = x;
    }
}