// Luogu p4315 维护边权 单点加/路径加/路径赋值/查询最大值
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,k,p[N],depth[N],siz[N],son[N];
int l[N],r[N],id[N],tot,top[N];
int a[N],idx[N];
struct edge
{
    int v,w,id;
};
vector<edge> e[N];
struct node
{
    int maxv,setv=-1,addv;
}tr[N*4];

void pushup(node &u,node &l,node &r)
{
    u.maxv=max(l.maxv,r.maxv);
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].setv!=-1)
    {
        int t=tr[u].setv,add=tr[u].addv;
        tr[u].setv=-1,tr[u].addv=0;
        tr[u<<1].maxv=tr[u<<1|1].maxv=t+add;
        tr[u<<1].setv=tr[u<<1|1].setv=t;
        tr[u<<1].addv=tr[u<<1|1].addv=add;
    }
    else if(tr[u].addv)
    {
        tr[u<<1].maxv+=tr[u].addv;
        tr[u<<1|1].maxv+=tr[u].addv;
        tr[u<<1].addv+=tr[u].addv;
        tr[u<<1|1].addv+=tr[u].addv;
        tr[u].addv=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={a[id[L]],-1,0};
        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

void modify(int u,int L,int R,int l,int r,int set,int add)
{
    if(L>=l&&R<=r)
    {
        if(set!=-1) tr[u].maxv=tr[u].setv=set,tr[u].addv=0;
        else tr[u].maxv+=add,tr[u].addv+=add;
        return;
    }
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r,set,add);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r,set,add);
    pushup(u);
}

node query(int u,int L,int R,int l,int r)
{
    if(L>=l&&R<=r) return tr[u];
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l>mid) return query(u<<1|1,mid+1,R,l,r);
    else if(r<=mid) return query(u<<1,L,mid,l,r);
    node res,ls=query(u<<1,L,mid,l,r),rs=query(u<<1|1,mid+1,R,l,r);
    pushup(res,ls,rs);
    return res;
}

void modify(int u,int v,int set,int add)
{
    while(top[u]!=top[v])
    {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        modify(1,1,n,l[top[u]],l[u],set,add);
        u=p[top[u]];
    }
    if(u==v) return;
    if(depth[u]<depth[v]) swap(u,v);
    modify(1,1,n,l[v]+1,l[u],set,add);
}

int query(int u,int v)
{
    int res=0;
    while(top[u]!=top[v])
    {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        res=max(res,query(1,1,n,l[top[u]],l[u]).maxv);
        u=p[top[u]];
    }
    if(u==v) return res;
    if(depth[u]<depth[v]) swap(u,v);
    res=max(res,query(1,1,n,l[v]+1,l[u]).maxv);
    return res;
}

void dfs(int u,int fa)
{
    siz[u]=1;
    p[u]=fa;
    depth[u]=depth[fa]+1;
    for(auto v : e[u])
    {
        int j=v.v,w=v.w,id=v.id;
        if(j==fa) continue;
        dfs(j,u);
        siz[u]+=siz[j];
        a[j]=w;
        idx[id]=j;
        if(siz[j]>siz[son[u]]) son[u]=j;
    }
}

void dfs2(int u,int fa,int t)
{
    top[u]=t;
    l[u]=++tot;
    id[tot]=u;
    if(son[u]) dfs2(son[u],u,t);
    for(auto x : e[u])
    {
        int v=x.v;
        if(v==fa||v==son[u]) continue;
        dfs2(v,u,v);
    }
    r[u]=tot;
}

void solve()
{
    cin >> n;
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a].push_back({b,c,i});
        e[b].push_back({a,c,i});
    }

    dfs(1,0);
    dfs2(1,0,1);

    build(1,1,n);
    char opt[20];
    while(scanf("%s",opt),strcmp(opt,"Stop"))
    {
        if(!strcmp(opt,"Max"))
        {
            int a,b;
            scanf("%d%d",&a,&b);
            printf("%d\n",query(a,b));
        }
        else if(!strcmp(opt,"Change"))
        {
            int a,b;
            scanf("%d%d",&a,&b);
            modify(1,1,n,l[idx[a]],l[idx[a]],b,0);
        }
        else if(!strcmp(opt,"Cover"))
        {
            int a,b,w;
            scanf("%d%d%d",&a,&b,&w);
            modify(a,b,w,0);
        }
        else
        {
            int a,b,w;
            scanf("%d%d%d",&a,&b,&w);
            modify(a,b,-1,w);
        }
    }
}

int main()
{
    solve();
    return 0;
}