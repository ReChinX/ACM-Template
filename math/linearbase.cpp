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
/**
 * version 2
 **/
struct L_B
{
    int a[32];
    void init()
    {
        memset(a,0,sizeof(a));
    }
    bool insert(int val)
    {
        for(int i=30;i>=0;i--)
        {
            if(val&(1<<i))
            {
                if(!a[i])
                {
                    a[i]=val;
                    break;
                }
                else val^=a[i];
            }
        }
        return val>0;
    }
    int query_max()
    {
        int ret=0;
        for(int i=30;i>=0;i--)
        {
            if((ret^a[i])>ret)ret^=a[i];
        }
        return ret;
    }
    L_B merge(L_B m)
    {
        L_B ret;
        for(int i=0;i<31;i++){ret.a[i]=a[i];}
        for(int i=0;i<31;i++)
        {
            for(int j=i;j>=0;j--)
            {
                if(m.a[i]&(1<<j))
                {
                    if(ret.a[j]) m.a[i]^=ret.a[j];
                    else {ret.a[j]=m.a[i];break;}
                }
            }
        }
        return ret;
    }
}