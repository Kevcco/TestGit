//Luogu P2590
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,a[N];
vector<int> e[N];
int siz[N],son[N],depth[N],fa[N];
int l[N],r[N],id[N],tot,top[N];

struct node
{
    int lc,rc,cnt;
    int tag;
}tr[N*4];

void pushup(node &u,node l,node r)
{
    u.lc=l.lc,u.rc=r.rc;
    u.cnt=l.cnt+r.cnt-(l.rc==r.lc);
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].tag)
    {
        int t=tr[u].tag;
        tr[u<<1]={t,t,1,t};
        tr[u<<1|1]={t,t,1,t};
        tr[u].tag=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={a[id[L]],a[id[L]],1,0};
        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

void modify(int u,int L,int R,int l,int r,int d)
{
    if(L>=l&&R<=r)
    {
        tr[u]={d,d,1,d};
        return;
    }
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r,d);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r,d);
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

//路径查询
int query(int u,int v)
{
    node res[2];
    res[0]=res[1]={0,0,0,0};
    int tag=0;
    while(top[u]!=top[v])
    {
        if(depth[top[u]]<depth[top[v]]) swap(u,v),tag^=1;
        pushup(res[tag],query(1,1,n,l[top[u]],l[u]),res[tag]),u=fa[top[u]];
    }
    if(depth[u]<depth[v]) swap(u,v),tag^=1;
    pushup(res[tag],query(1,1,n,l[v],l[u]),res[tag]);
    return res[0].cnt+res[1].cnt-(res[0].lc==res[1].lc);
}

//路径修改
void modify(int u,int v,int c)
{
    while(top[u]!=top[v])
    {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        modify(1,1,n,l[top[u]],l[u],c);
        u=fa[top[u]];
    }
    if(depth[u]<depth[v]) swap(u,v);
    modify(1,1,n,l[v],l[u],c);
}

void dfs1(int u,int f)
{
    depth[u]=depth[f]+1;
    siz[u]=1,fa[u]=f;
    for(auto v: e[u])
    {
        if(v==f) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}

void dfs2(int u,int f,int t)
{
    top[u]=t;
    l[u]=++tot;
    id[tot]=u;
    if(son[u]) dfs2(son[u],u,t);
    for(auto v : e[u])
    {
        if(v==f) continue;
        if(v!=son[u]) dfs2(v,u,v);
    }
    r[u]=tot;
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs1(1,0),dfs2(1,0,1);
    build(1,1,n);
    while(m--)
    {
        char opt[10];
        int a,b;
        scanf("%s%d%d",opt,&a,&b);
        if(*opt=='C')
        {
            int c;
            scanf("%d",&c);
            modify(a,b,c);
        }
        else printf("%d\n",query(a,b));
    }
}

int main()
{
    solve();
    return 0;
}