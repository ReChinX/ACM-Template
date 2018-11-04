// 匈牙利算法，link数组代表左集合第i个匹配到右集合link[i]
// 时间复杂度 O(nm)
int head[N], nxt[2 * M], to[2 * M], cnt = 0;
int link[N], vis[N];
inline void init() {memset(head, -1, sizeof(head)); cnt = 0;}
inline void add(int u, int v) {to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;}
int dfs(int x) {
    for(int i = head[x]; ~i; i = nxt[i]) {
        int v = to[i]; if(!vis[v]) {
            vis[v] = 1; if(!link[v] || dfs(link[v])) {
                link[v] = x; return 1;
            }
        }
    }
    return 0;
}
// 枚举右集合，通过增广边找匹配
int hungary() {
    int ret = 0;
    for(int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) ret++;
    }
    return ret;
}