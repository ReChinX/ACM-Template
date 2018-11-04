/**
 * spfa支持负权图，能判负权环
 **/
#define inf 0x7f7f7f7f
const int N = 2005, M = 20005;
int head[N], nxt[M], val[M], to[M], cnt;
int dis[N], Out[N];
bool vis[N];
inline void init() {memset(head, -1, sizeof(head)); cnt=0;}
inline void addedge(int u, int v, int w) {
    to[cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt++;
}
bool spfa(int s, int n) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 127, sizeof(dis));
    memset(Out, 0, sizeof(Out));
    dis[s] = 0; vis[s] = 1; Out[s] = 1;
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        vis[u] = 0; 
        for(int i = head[u]; ~i; i = nxt[i]) {
            int v = to[i];
            if(dis[v] > dis[u] + val[i]) {
                dis[v] = dis[u] + val[i];
                if(!vis[v]) {
                    vis[v] = 1; que.push(v);
                    if(++Out[v] > n) return false;
                }
            }
        }
    }
    return true;
}