typedef pair<int, int> P;
const int N = 3005, M = 200005;
int head[N], nxt[M], to[M], val[M], cnt, dis[N];
priority_queue<P, vector<P>, greater<P> > pq;
inline void init() {memset(head, -1, sizeof(head));cnt = 0;}
inline void add(int u, int v, int w) {to[cnt] = v; val[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt++;}
inline void dijkstra(int s) {
    for(int i = 1; i <= n; ++i) dis[i] = inf;
    dis[s] = 0; pq.push(make_pair(dis[s], s));
    while(!pq.empty()) {
        P t = pq.top(); pq.pop();
        int now = t.second;
        if(dis[now] < t.first) continue;
        for(int i = head[now]; ~i; i = nxt[i]) {
            int vv = to[i], ww = val[i];
            if(dis[vv] > t.first + 1LL * ww) {
                dis[vv] = t.first + 1LL * ww;
                pq.push(make_pair(dis[vv], vv));
            }
        }
    }
}