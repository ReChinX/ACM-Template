struct SuffixAutomaton{
#define N 200005
    int trans[N][26], pa[N], Maxlen[N], sz, root, last, Right[N];
    char str[200005]; int len = 0;
    struct Edge{
        int to, nxt;
    }edge[N];
    int cnte, head[N];
    inline void InitEdge() {
        cnte = 0;
        memset(head, -1, sizeof(head));
    }
    inline void AddEdge(int u, int v) {
        edge[cnte].to = v;
        edge[cnte].nxt = head[u];
        head[u] = cnte++;
    }
    inline void InitSam() {
        memset(trans, 0, sizeof(trans));
        memset(Maxlen, 0, sizeof(Maxlen));
        memset(Right, 0, sizeof(Right));
        root = last = sz = 1;
    }
    inline void Extend(int c, int x) {
        int p = last, np = ++sz; last = np; Maxlen[np] = x; Right[np] = 1;
        for(;p && !trans[p][c]; p = pa[p]) trans[p][c] = np;
        if(!p) {
            pa[np] = root;
        }else {
            int q = trans[p][c];
            if(Maxlen[q] == Maxlen[p] + 1) {
                pa[np] = q;
            }else {
                int nq = ++sz;
                memcpy(trans[nq], trans[q], sizeof(trans[q]));
                pa[nq] = pa[q]; Maxlen[nq] = Maxlen[p] + 1; pa[q] = pa[np] = nq;
                for(;trans[p][c] == q; p = pa[p]) trans[p][c] = nq;
            }
        }
    }
    inline void Build(char *s) {
        strcpy(str, s);
        len = strlen(str);
        for(int i = 0; i < len; i++) {
            Extend(str[i] - 'a', i + 1);
        }
    }
    int DFS(int u) {
        for(int i = head[u]; ~i; i = edge[i].nxt) Right[u] += DFS(edge[i].to);
        return Right[u];
    }
    inline void Solve() {
        InitEdge();
        for(int i = 2; i <= sz; i++) {
            AddEdge(pa[i], i);
        }
        DFS(root);
    }
}sam;