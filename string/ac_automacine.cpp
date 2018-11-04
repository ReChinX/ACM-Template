/**
 * nxt[i][j]表示第i个节点的子节点为j的节点编号
 * fail[i]表示i节点fail指针指向的节点
 * end[i]表示第i个节点是否为单词节点
 * 时间复杂度O(len)
 **/
struct ACM {
#define N 110
    int nxt[N][26], fail[N], end[N];
    int root, sz;
    int newnode() {
        for (int i = 0; i < 26; i++) nxt[sz][i] = -1;
        end[sz++] = 0;
        return sz - 1;
    }
    void init() {
        sz = 0;
        root = newnode();
    }
    void insert(char *buf, int id) {
        int len = strlen(buf);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (nxt[now][buf[i] - 'a'] == -1)
                nxt[now][buf[i] - 'a'] = newnode();
            now = nxt[now][buf[i] - 'a'];
        }
        end[now] |= (1 << id);
    }
    void build() {
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < 26; i++) {
            if (nxt[root][i] == -1)
                nxt[root][i] = root;
            else {
                fail[nxt[root][i]] = root;
                Q.push(nxt[root][i]);
            }
        }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            end[now] |= end[fail[now]];
            for (int i = 0; i < 26; i++) {
                if (nxt[now][i] == -1)
                    nxt[now][i] = nxt[fail[now]][i];
                else {
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                    Q.push(nxt[now][i]);
                }
            }
        }
    }

} ac;