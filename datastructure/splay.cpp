#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 50005, M = 100005;
int head[N], nxt[2 * M], to[2 * M], cnt, vis[N];
LL val[2 * M], dis[N];
vector<LL> a;
int n, m;
inline void add(int u, int v, LL value) {to[cnt] = v; nxt[cnt] = head[u]; val[cnt] = value;head[u] = cnt++;}
void dfs(int u, int fa) {
    vis[u] = 1;
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i]; if(v == fa) continue;
        if(!vis[v]) {
            dis[v] = dis[u] ^ val[i]; dfs(v, u);
        }else {
            a.push_back(dis[u] ^ val[i] ^ dis[v]);
        }
    }
}
const int MAX_BASE = 60;
LL b[MAX_BASE + 5];
inline void gauss() {
    memset(b, 0, sizeof(b));
    for(int i = 0; i < a.size(); ++i) {
        for(LL j = MAX_BASE; j >= 0; --j) {
            if((a[i] >> j) & 1) {
                if(b[j]) a[i] ^= b[j];
                else {
                    b[j] = a[i]; 
                    for(LL k = j - 1; k >= 0; --k) if (b[k] && ((b[j] >> k) & 1)) b[j] ^= b[k];
                    for(LL k = j + 1; k <= MAX_BASE; ++k) if ((b[k] >> j) & 1) b[k] ^= b[j];
                    break;
                }
            }
        }
    }
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int x, y; LL z;
        scanf("%d %d% lld", &x, &y, &z);
        add(x, y, z); add(y, x, z);
    }
    dfs(1, 0);
    gauss();
    LL ret = dis[n];
    for(LL i = MAX_BASE; i >= 0; --i) {
        if(!((ret >> i) & 1)) ret ^= b[i];
    }
    cout << ret << endl;
    return 0;
}