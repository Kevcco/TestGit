/*
给定n个点的树 ，回答m个询问  n,m <= 5e5
每个询问 给出 v,l,r 询问 节点 v 和在dfs序[l,r]区间内的叶子节点的路径中最短的路径长度 

考虑离线处理 先预处理dfs序 和 所有叶子节点到根的距离 非叶子节点为INF 
然后线段树维护dfs序列的最小值 最后再dfs一遍求答案
假设现在处于u节点，所有叶子节点到u节点的距离都是正确的，那么关于u的所有询问，直接查询[l,r]最小值即可
如何转移到儿子节点 ： 考虑儿子v (u,v)=w 那么在v这个子树的叶子节点，距离会减少w 在dfs序中就是区间修改
                    而其他的叶子节点都距离都会增加w 也是区间修改 因此线段树维护即可

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;
const ll INF=1e18;

int n,m,tot;
int l[N],r[N];
ll a[N];
vector<pii> e[N];
ll ans[N];
vector<array<int,3>> q[N];
struct node
{
    ll v,tag;
}tr[N*4];

void pushup(node &u,node &l,node &r)
{
    u.v=min(l.v,r.v);
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].tag)
    {
        tr[u<<1].v+=tr[u].tag,tr[u<<1].tag+=tr[u].tag;
        tr[u<<1|1].v+=tr[u].tag,tr[u<<1|1].tag+=tr[u].tag;
        tr[u].tag=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u].v=a[L];
        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

//区间修改
void modify(int u,int L,int R,int l,int r,ll d)
{
    if(L>=l&&R<=r)
    {
        tr[u].v+=d;
        tr[u].tag+=d;
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

void dfs(int u,int fa,ll d)
{
    l[u]=++tot;
    for(auto v : e[u])
    {
        ll x=v.first,w=v.second;
        if(x==fa) continue;
        dfs(x,u,d+w);
    }
    r[u]=tot;
    if(l[u]==r[u]) a[u]=d;
    else a[u]=INF;
}

void dfs(int u,int fa)
{
    for(auto x : q[u]) ans[x[2]]=query(1,1,n,x[0],x[1]).v;

    for(auto x : e[u])
    {
        int v=x.first,w=x.second;
        if(v==fa) continue;
        modify(1,1,n,l[v],r[v],-w);
        if(l[v]>1) modify(1,1,n,1,l[v]-1,w);
        if(r[v]<n) modify(1,1,n,r[v]+1,n,w);
        dfs(v,u);
        modify(1,1,n,l[v],r[v],w);
        if(l[v]>1) modify(1,1,n,1,l[v]-1,-w);
        if(r[v]<n) modify(1,1,n,r[v]+1,n,-w);
    }
}

void solve()
{
    cin >> n >> m;
    for(int i=2;i<=n;i++)
    {
        int x,w;
        scanf("%d%d",&x,&w);
        e[i].push_back({x,w});
        e[x].push_back({i,w});
    }

    //因为dfs序不唯一，题目规定按照节点编号小到大来dfs
    for(int i=1;i<=n;i++) sort(e[i].begin(),e[i].end());

    dfs(1,0,0);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int v,l,r;
        scanf("%d%d%d",&v,&l,&r);
        q[v].push_back({l,r,i});
    }

    dfs(1,0);
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}

int main()
{
    solve();
    return 0;
}