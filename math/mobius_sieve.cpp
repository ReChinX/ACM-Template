/**
 * 莫比乌斯函数线性筛
 **/
const int N = 1000005;
bool check[N+5];
int prime[N+5], mu[N+5], tot;
void mobius() {
    memset(check, 0, sizeof(check));
    mu[1] = 1; tot = 0;
    for(int i = 2; i <= N; ++i) {
        if(!check[i]) {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot; ++j) {
            if(i * prime[j] > N) break;
            check[i * prime[j]] = true;
            if(i % prime[j] == 0) {
                mu[i * prime[j]] = 0; break;
            }else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}