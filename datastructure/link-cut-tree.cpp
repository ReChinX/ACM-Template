/**
 * makeroot(x) 让x成为原树根节点
 * link(x,y) x, y之间连边
 * cut(x,y) x, y删边
 * split(x,y) 找到x, y所对应的路径，访问y得到路径信息
 * findroot(x) 找到x所在原树的根
 * access(x) 从根节点到x拉一条重边
 **/ 
namespace LinkCutTree {
    const int N = 300005;
    int ch[N][2], fa[N], rev[N], que[N], top;
    int val[N]; 
    void pushup(int x) {
        val[x] = val[ch[x][0]] + val[ch[x][1]] + 1;
    }
    void pushdown(int x) {
        if(rev[x]) {
            rev[ch[x][0]]^=1; rev[ch[x][1]]^=1; rev[x]^=1;
            swap(ch[x][0], ch[x][1]);
        }
    }
    bool isroot(int x) {return ch[fa[x]][0] != x && ch[fa[x]][1] != x;}
    void rotate(int x) {
        int y=fa[x],z=fa[y],l,r;
        if(ch[y][0]==x)l=0;else l=1;r=l^1;
        if(!isroot(y)){if(ch[z][0]==y)ch[z][0]=x;else ch[z][1]=x;}
        fa[x]=z;fa[y]=x;fa[ch[x][r]]=y;
        ch[y][l]=ch[x][r];ch[x][r]=y;
        pushup(y);pushup(x);
    }
    void splay(int x){
        top=1;que[top]=x;
        for(int i=x;!isroot(i);i=fa[i])que[++top]=fa[i];
        for(int i=top;i;i--)pushdown(que[i]);
        while(!isroot(x)){
            int y=fa[x],z=fa[y];
            if(!isroot(y)){
                if((ch[y][0]==x)^(ch[z][0]==y))rotate(x);
                else rotate(y);
            }rotate(x);
        }
    }
    void access(int x){for(int t=0;x;t=x,x=fa[x])splay(x),ch[x][1]=t,pushup(x);}
    void makeroot(int x){access(x);splay(x);rev[x]^=1;}
    int findroot(int x){access(x);splay(x);while(ch[x][0])x=ch[x][0];return x;}
    void split(int x,int y){makeroot(x);access(y);splay(y);}
    void cut(int x,int y){makeroot(x);if(findroot(y)==x&&ch[y][0]==x&&!ch[x][1]&&fa[x]==y)ch[y][0]=0,fa[x]=0,pushup(y);}
    void link(int x,int y){makeroot(x);if(findroot(y)!=x) fa[x]=y;}
}