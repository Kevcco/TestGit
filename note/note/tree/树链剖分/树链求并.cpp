//https://vjudge.csgrandeur.cn/problem/%E9%BB%91%E6%9A%97%E7%88%86%E7%82%B8-3589
// 1.子树同加  2.查询 k(k<=5)个树链的并的合
//树链剖分转化为区间求并，排序贪心合并即可
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const ll mod=(1LL<<31),N=2e5+10;

int n,m,k,a[N],idx;
vector<int> e[N];
int siz[N],son[N],depth[N],fa[N];
int l[N],r[N],id[N],tot,top[N];
pii seg[1000];
struct node
{
    ll sum,tag;
}tr[N*4];

void pushup(node &u,node &l,node &r)
{
    u.sum=l.sum+r.sum;
    u.sum%=mod;
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].tag)
    {
        ll t=tr[u].tag;
        int mid=L+R>>1;
        tr[u].tag=0;
        tr[u<<1].sum+=t*(mid-L+1),tr[u<<1].tag+=t;
        tr[u<<1|1].sum+=t*(R-mid),tr[u<<1|1].tag+=t;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={0,0};
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
        tr[u].sum+=d*(R-L+1),tr[u].sum%=mod;
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

void add_chain(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(depth[top[u]]>depth[top[v]]) seg[idx++]={l[top[u]],l[u]},u=fa[top[u]];
        else seg[idx++]={l[top[v]],l[v]},v=fa[top[v]];
    }
    if(depth[u]<=depth[v]) seg[idx++]={l[u],l[v]};
    else seg[idx++]={l[v],l[u]};
}

//区间求并 
ll query()
{
    ll res=0;
    sort(seg,seg+idx);
    int l=seg[0].first,r=seg[0].second;
    for(int i=1;i<idx;i++)
    {
        if(seg[i].first>r+1)
        {
            res+=query(1,1,n,l,r).sum;
            res%=mod;
            l=seg[i].first,r=seg[i].second;
        }
        else r=max(r,seg[i].second);
    }
    res+=query(1,1,n,l,r).sum;
    res%=mod;
    return res;
}

//求size,son,father,depth
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

//求dfs序(先dfs重儿子),重链的链头
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
    cin >> n;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs1(1,0);
    dfs2(1,0,1);
    //build(1,1,n);
    cin >> m;
    while(m--)
    {
        int opt,a,b;
        scanf("%d",&opt);
        if(opt)
        {
            scanf("%d",&k);
            idx=0;
            while(k--)
            {
                scanf("%d%d",&a,&b);
                add_chain(a,b);
            }
            printf("%d\n",query());
        }
        else
        {
            scanf("%d%d",&a,&b);
            modify(1,1,n,l[a],r[a],b);
        }
    }
}

int main()
{
    solve();
    return 0;
}