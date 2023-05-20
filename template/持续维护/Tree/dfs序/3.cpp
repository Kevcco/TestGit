
/*
(7) 单点修改 树链查询
维护所有树链 变成 子树修改 单点查询 再差分 变成dfs序上的单点修改 区间查询 
(8) 子树修改 树链查询 ： 
维护树链的差分 推公式得 维护 d[u] 和 d[u] * depth[u]
子树修改 = [l[u],r[u]] 区间 
所有点v += x * (depth[v]-depth[u]+1)
= x * depth[v] + x * (1 - depth[u])
后一项变成差分数组d[i]的单点修改 前一项变成tr2的单点修改
树链值 = sum_tr1[l[u],r[u]] + sum_tr2[l[u],r[u]] * depth[u] 

*/
// 1.单点修改 2.子树修改 3.树链查询
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m,root,tot,idx;
int depth[N],a[N],pos[N],l[N],r[N],par[N];
int p[22][2*N];
vector<int> e[N];
ll tr1[N],tr2[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,ll c,ll tr[])
{
    if(!x) return;
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

ll sum(int x,ll tr[])
{
    ll res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}


void dfs(int u,int fa)
{
    par[u]=fa;
    l[u]=++idx;
    depth[u]=depth[fa]+1;
    pos[u]=++tot;
    p[0][tot]=u;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        p[0][++tot]=u;
    }
    r[u]=idx;
}

int lca(int u,int v)
{
    int a=pos[u],b=pos[v];
    if(a>b) swap(a,b);
    int k=31-__builtin_clz(b-a+1);
    if(depth[p[k][a]]<depth[p[k][b-(1<<k)+1]]) return p[k][a];
    else return p[k][b-(1<<k)+1];
}

void modify_vertex(int u,ll x)
{
    add(l[u],x,tr1);
    add(r[u]+1,-x,tr1);
}

void modify_subtree(int u,ll x)
{
    ll t=(1-depth[u])*x;
    add(l[u],t,tr1);
    add(r[u]+1,-t,tr1);
    add(l[u],x,tr2);
    add(r[u]+1,-x,tr2);
}

ll query(int u)
{
    ll t=sum(l[u],tr2)*depth[u];
    t+=sum(l[u],tr1);
    return t;
}

ll query_list(int u,int v)
{
    int w=lca(u,v);
    ll res=query(u)+query(v)-query(w)-query(par[w]);
    return res;
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(root,0);

    for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=tot;i++)
            if(depth[p[j-1][i]]<depth[p[j-1][i+(1<<j-1)]]) p[j][i]=p[j-1][i];
            else p[j][i]=p[j-1][i+(1<<j-1)];
    
    for(int i=1;i<=n;i++) modify_vertex(i,a[i]);

    while(m--)
    {
        int opt,a,x;
        scanf("%d%d%d",&opt,&a,&x);
        if(opt==1) modify_vertex(a,x);
        else if(opt==2) modify_subtree(a,x);
        else printf("%lld\n",query_list(a,x));
    }
}

int main()
{
    solve();
    return 0;
}