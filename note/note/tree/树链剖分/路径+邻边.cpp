/*
Luogu P7735
每次修改一条路径，路径上所有点的所有邻边变成0，路径上的边再变成1
每次询问一条路径上1的边的个数

难以给边打标记，考虑给点打标记
每次新的修改，都给路径上的所有点打新的标记
因此只有两个端点的标记相同的边才是1
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k,p[N],depth[N],siz[N],son[N];
int l[N],r[N],id[N],tot,top[N];
vector<int> e[N];

struct node
{
    int lc,rc,cnt=0,tag=0;
}tr[N*4];

void pushup(node &u,node l,node r)
{
    u.lc=l.lc;
    u.rc=r.rc;
    u.cnt=l.cnt+r.cnt+(l.rc==r.lc);
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].tag)
    {
        int mid=L+R>>1;
        tr[u<<1].lc=tr[u<<1].rc=tr[u<<1].tag=tr[u].tag;
        tr[u<<1|1].lc=tr[u<<1|1].rc=tr[u<<1|1].tag=tr[u].tag;
        tr[u<<1].cnt=mid-L;
        tr[u<<1|1].cnt=R-mid-1;
        tr[u].tag=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={L,L,0,0};
        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

//区间修改
void modify(int u,int L,int R,int l,int r,int d)
{
    if(L>=l&&R<=r)
    {
        tr[u].lc=tr[u].rc=tr[u].tag=d;
        tr[u].cnt=R-L;
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

void dfs(int u,int fa)
{
    siz[u]=1;
    p[u]=fa;
    depth[u]=depth[fa]+1;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}

void dfs2(int u,int fa,int t)
{
    top[u]=t;
    l[u]=++tot;
    id[tot]=u;
    if(son[u]) dfs2(son[u],u,t);
    for(auto v : e[u])
    {
        if(v==fa||v==son[u]) continue;
        dfs2(v,u,v);
    }
    r[u]=tot;
}

void modify(int u,int v,int d)
{
    while(top[u]!=top[v])
    {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        modify(1,1,n,l[top[u]],l[u],d);
        u=p[top[u]];
    }
    if(depth[u]>depth[v]) swap(u,v);
    modify(1,1,n,l[u],l[v],d);
}

int query(int u,int v)
{
    node res1,res2;
    res1={-1,0,0,0};
    res2={-2,0,0,0};
    while(top[u]!=top[v])
    {
        if(depth[top[u]]>depth[top[v]])
        {
            if(!res1.rc) res1=query(1,1,n,l[top[u]],l[u]);
            else pushup(res1,query(1,1,n,l[top[u]],l[u]),res1);
            u=p[top[u]];
        }
        else
        {
            if(!res2.rc) res2=query(1,1,n,l[top[v]],l[v]);
            else pushup(res2,query(1,1,n,l[top[v]],l[v]),res2);
            v=p[top[v]];
        }
    }
    if(depth[u]>depth[v])
    {
        if(!res1.rc) res1=query(1,1,n,l[v],l[u]);
        else pushup(res1,query(1,1,n,l[v],l[u]),res1);
    }
    else
    {
        if(!res2.rc) res2=query(1,1,n,l[u],l[v]);
        else pushup(res2,query(1,1,n,l[u],l[v]),res2);
    }
    return res1.cnt+res2.cnt+(res1.lc==res2.lc);
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) e[i].clear(),son[i]=0;
    for(int i=1;i<=4*n;i++) tr[i].tag=0;
    tot=0;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(1,0);
    dfs2(1,0,1);
    build(1,1,n);
 //   printf("asdasd  %d\n",query(1,1,n,1,n).cnt);

    int cnt=0;
    while(m--)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==2) printf("%d\n",query(x,y));
        else
        {
            cnt++;
            modify(x,y,n+cnt);
        }
    }
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}