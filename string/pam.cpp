int s[N], ch[N][26], fail[N], len[N], cnt[N], last, ecnt, n;
void init() {
    fail[0] = 1; fail[1] = 1; 
    len[0] = 0;  len[1] = -1;
    ecnt = 1; last = 1;
}
void extend( int w ) {
    int p = last; s[++n] = w;
    while( s[n-1-len[p]] != w ) 
        p = fail[p];
    if(!ch[p][w]) {
        int u = ++ecnt, v = fail[p];
        while( s[n-1-len[v]] != w ) v = fail[v];
        len[u] = len[p]+2; fail[u] = ch[v][w]; ch[p][w] = u;
    }
    last = ch[p][w]; cnt[last]++;
}

void calc() {
    for( int i = ecnt; ~i; i -- ) cnt[fail[i]] += cnt[i];
}