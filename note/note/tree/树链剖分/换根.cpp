// Luogu P3979
//1.换根 2.路径赋值 3.查询子树最小值
//换根：以1为根树剖，记录当前的根，讨论询问的节点u与根的关系
//若根=u，那么u的子树是整棵树，若根是u的儿子，那么u的子树是除根所在的u的儿子这棵子树外的其他所有点
//否则，u的子树不变
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,k,p[18][N],depth[N],siz[N],son[N];
int l[N],r[N],id[N],tot,top[N];
int a[N],root;
vector<int> e[N];

struct node
{
    int minv,tag;
}tr[N*4];

void pushup(node &u,node l,node r)
{
    u.minv=min(l.minv,r.minv);
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u)
{
    if(tr[u].tag)
    {
        tr[u<<1].minv=tr[u].tag;
        tr[u<<1].tag=tr[u].tag;
        tr[u<<1|1].minv=tr[u].tag;
        tr[u<<1|1].tag=tr[u].tag;
        tr[u].tag=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={a[id[L]],0};
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
        tr[u].minv=d;
        tr[u].tag=d;
        return;
    }
    pushdown(u);
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r,d);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r,d);
    pushup(u);
}

node query(int u,int L,int R,int l,int r)
{
    if(l>r) return {(int)2e9,0};
    if(L>=l&&R<=r) return tr[u];
    pushdown(u);
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
    p[0][u]=fa;
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
        u=p[0][top[u]];
    }
    if(depth[u]>depth[v]) swap(u,v);
    modify(1,1,n,l[u],l[v],d);
}

//分三种情况讨论
int query(int u)
{
    if(u==root) return query(1,1,n,1,n).minv;
    if(l[root]>l[u]&&r[root]<=r[u])
    {
        int d=depth[root]-depth[u]-1;
        int sub=root;
        for(int i=17;i>=0;i--)
            if(d>>i&1) sub=p[i][sub];
        return min(query(1,1,n,1,l[sub]-1).minv,query(1,1,n,r[sub]+1,n).minv);
    }
    else return query(1,1,n,l[u],r[u]).minv;
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    cin >> root;
    dfs(1,0);
    dfs2(1,0,1);
    build(1,1,n);

    for(int j=1;j<18;j++)
        for(int i=1;i<=n;i++)
            p[j][i]=p[j-1][p[j-1][i]];

    while(m--)
    {
        int op,x,y,z;
        scanf("%d%d",&op,&x);
        if(op==1) root=x;
        else if(op==3) printf("%d\n",query(x));
        else
        {
            scanf("%d%d",&y,&z);
            modify(x,y,z);
        }
    }
}

int main()
{
    solve();
    return 0;
}
