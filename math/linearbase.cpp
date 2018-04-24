const int MAX_BASE = 60;
LL a[10005], b[MAX_BASE + 5];
vector<LL> base;
inline void gauss() {
    memset(b, 0, sizeof(b));
    for(int i = 1; i <= n; ++i) {
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
    base.clear();
    for(int i = 0; i <= MAX_BASE; ++i) if(b[i]) base.push_back(b[i]);
}