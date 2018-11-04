/**
 * f为积性函数
 * pow_cnt为最小质因子的指数次数
 * low为最小质因数p在唯一分解中出现的p^t
 **/
const int N = 10000000;
int prime[N+5], low[N+5], check[N+5], pow_cnt[N+5], tot, f[N+5];
void sieve() {
    memset(check, 0, sizeof(check));
    low[1] = 1; tot = 0; f[1] = 1; pow_cnt[1] = 0; 
    for(int i = 2; i <= N; ++i) {
        if(!check[i]) {
            low[i] = i; prime[tot++] = i;f[i] = /** f(p)情况**/;
        }
        for(int j = 0; j < tot; ++j) {
            if(i * prime[j] > N) break;
            check[i*prime[j]] = 1;
            if(i % prime[j] == 0) {
                pow_cnt[i * prime[j]] = pow_cnt[i] + 1;
                low[i * prime[j]] = low[i] * prime[j];             
                if(low[i] == i) {
                    f[i*prime[j]] = /** f(p^k)情况**/;
                }else {
                    f[i * prime[j]] = f[i / low[i]] * f[low[i] * prime[j]];
                }
                break;
            }else {
                low[i * prime[j]] = prime[j];
                pow_cnt[i * prime[j]] = 1;
                f[i * prime[j]] = f[i] * f[prime[j]];
            }
        }
    }
}