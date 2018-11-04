// sccno代表i号节点属于第几个强连通分量
const int N = 100005, M = 100005;
int head[N], nxt[M], to[M], cnt;
int dfn[N], low[N], sccno[N], dfs_ind, vis[N], scc_cnt;
stack<int> st;
inline void init() {memset(head, -1, sizeof(head)); cnt = 0; scc_cnt = 0; dfs_ind = 1;}
inline void add(int u, int v) {to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;}
void tarjan(int u) {
    dfn[u] = low[u] = dfs_ind++;
    st.push(u);
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if(!dfn[v]) {
            tarjan(v); low[u] = min(low[u], low[v]);
        }
        else if(!sccno[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        scc_cnt++;
        while(1) {
            int x = st.top(); st.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}