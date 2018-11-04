// top[x] x节点所在链的顶端节点，wson[x] x节点重儿子
// dep[x] x节点深度，sz[x] x节点子树节点个数
// fa[x] x节点父节点
// pos[x] x节点在线段树中位置（也就是dfs序位置），pre[l] 线段树中位置为l（dfs序为l）对应的节点
#define inf 0x7f7f7f7f
using namespace std;
const int N = 30005, M = 100010;
int head[N], nxt[M], to[M], cnt;
int sz[N], dep[N], fa[N], top[N], wson[N], pre[M], pos[N], ind = 0;
int a[N], n;
inline void init() {memset(head, -1, sizeof(head)); cnt = 0; dep[1] = 1; fa[1] = 1;}
inline void add(int u, int v) {to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;}
void dfs1(int u, int f) {
    sz[u] = 1;
    for(int i = head[u]; ~i; i = nxt[i]) {        
        int v = to[i]; if(f == v) continue;
        dep[v] = dep[u] + 1; fa[v] = u; dfs1(v, u);
        sz[u] += sz[v]; if(sz[v] > sz[wson[u]]) wson[u] = v;
    }
}
void dfs2(int u, int h) {
    top[u] = h; pos[u] = ++ind;  pre[ind] = u;
    if(wson[u]) dfs2(wson[u], h);
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i]; if(v == fa[u] || v == wson[u]) continue;
        dfs2(v, v);
    }
}
int sum[N << 2], maxv[N << 2];
inline void pushup(int x) {sum[x] = sum[x<<1] + sum[x<<1|1]; maxv[x] = max(maxv[x<<1], maxv[x<<1|1]);}
void build(int x, int l, int r) {
    if(l == r) {
        sum[x] = maxv[x] = a[pre[l]]; return;
    }
    int mid = (l + r) >> 1;
    build(x<<1, l, mid); build(x<<1|1, mid+1, r);
    pushup(x);
}
void update(int x, int l, int r, int q, int v) {
    if(l == r) {sum[x] = maxv[x] = v; return;}
    int mid = (l + r)>>1;
    if(q <= mid) update(x<<1, l, mid, q, v);
    else update(x<<1|1, mid+1, r, q, v);
    pushup(x);
}
int querysum(int x, int l, int r, int ql, int qr) {
    if(ql <= l && r <= qr) {
        return sum[x];
    }
    int mid = (l+r)>>1, ans = 0;
    if(ql <= mid) ans += querysum(x<<1, l, mid, ql, qr);
    if(qr > mid) ans += querysum(x<<1|1, mid+1, r, ql, qr);
    pushup(x);
    return ans;
}
int querymax(int x, int l, int r, int ql, int qr) {
    if(ql <= l && r <= qr) {
        return maxv[x];
    }
    int mid = (l+r)>>1, ans = -inf;
    if(ql <= mid) ans = max(ans, querymax(x<<1, l, mid, ql, qr));
    if(qr > mid) ans = max(ans, querymax(x<<1|1, mid+1, r, ql, qr));
    pushup(x);
    return ans;
}
int qsum(int u, int v) {
    int ans = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ans += querysum(1, 1, n, pos[top[u]], pos[u]);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    ans += querysum(1, 1, n, pos[v], pos[u]);
    return ans;
}
int qmax(int u, int v) {
    int ans = -inf;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ans = max(ans, querymax(1, 1, n, pos[top[u]], pos[u]));
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    ans = max(ans, querymax(1, 1, n, pos[v], pos[u]));
    return ans;
}