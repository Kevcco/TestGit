/*
给定n点m边的无向边带权图  n,m <= 2e5 对于每一条边 分别求出包含这条边的最小生成树


先求出全局最小生成树，对于任意一条边而言
(1) 如果这条边在最小生成树里 那么答案就是全局最小生成树
(2) 如果不是 那么 对于这条边(u,v) 在全局最小生成树中 找到u到v路径上边权最大的边
    去掉那条边 把这条边(u,v)加入生成树 就是权重最小的生成树
    求路径:LCA 维护倍增的父亲节点 同时维护路径上边权的最大值 预处理 O(nlogn)  查询 O(logn)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,p[N],pmax[19][N],f[19][N],depth[N];
vector<pii> e[N];
ll res,ans2[N];
struct edge
{
    int v,l,r,id;
}E[N];

void dfs(int u,int fa)
{
    for(auto v: e[u])
    {
        int j=v.first,w=v.second;
        if(j==fa) continue;
        depth[j]=depth[u]+1;
        pmax[0][j]=w;
        f[0][j]=u;
        dfs(j,u);
    }
}

bool cmp(edge &a,edge &b)
{
    return a.v<b.v;
}

int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=1;i<=m;i++)
    {
        int u,v,x;
        scanf("%d%d%d",&u,&v,&x);
        E[i]={x,u,v,i};
    }

    sort(E+1,E+m+1,cmp);

    for(int i=1;i<=m;i++)
    {
        int u=E[i].l,v=E[i].r;
        int a=find(u),b=find(v);
        if(a==b) continue;
        e[u].push_back({v,E[i].v});
        e[v].push_back({u,E[i].v});
        res+=E[i].v;
        p[a]=b;
    }

    dfs(1,0);

    for(int j=1;j<=18;j++)
        for(int i=1;i<=n;i++)
            f[j][i]=f[j-1][f[j-1][i]],
            pmax[j][i]=max(pmax[j-1][i],pmax[j-1][f[j-1][i]]);

    for(int i=1;i<=m;i++)
    {
        ll ans=0;
        int u=E[i].l,v=E[i].r,id=E[i].id;
        if(depth[u]<depth[v]) swap(u,v);
        int d=depth[u]-depth[v];
        for(int j=18;j>=0;j--)
            if(d>>j&1) ans=max(ans,(ll)pmax[j][u]),u=f[j][u];

        if(u!=v)
        {
            for(int j=18;j>=0;j--)
            {
                if(f[j][u]!=f[j][v])
                {
                    ans=max(ans,(ll)pmax[j][u]);
                    ans=max(ans,(ll)pmax[j][v]);
                    u=f[j][u];
                    v=f[j][v];
                }
            }
            ans=max(ans,(ll)pmax[0][u]);
            ans=max(ans,(ll)pmax[0][v]);
        }
        ans2[id]=res-ans+E[i].v;
    }

    for(int i=1;i<=m;i++) printf("%lld\n",ans2[i]);

}

int main()
{
    solve();
    return 0;
}