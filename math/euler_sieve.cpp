/**
 * 欧拉函数线性筛
 **/
const int N = 100005;
bool check[N];
int prime[N], phi[N], tot;
void euler() {
    memset(check, 0, sizeof(check));
    phi[1] = 1; tot = 0;
    for(int i = 2; i < N; ++i) {
        if(!check[i]) {
            prime[tot++] = i;
            phi[i] = i-1;
        }
        for(int j = 0; j < tot; ++j) {
            if(i * prime[j] >= N) break;
            check[i * prime[j]] = true;
            if(i % prime[j] == 0) {
                phi[i * prime[j]] = prime[j] * phi[i]; break;
            }else {
                phi[i * prime[j]] = (prime[j]-1) * phi[i];
            }
        }
    }
}