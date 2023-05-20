/*
重链剖分

性质：从下到上，经过轻边，子树大小翻倍，因此最多经过O(logn)条轻边
      因此任意两点之间的路径,最多 O(logn) 条轻边，最多O(logn)段重链

求dfs序时先dfs重儿子,这样每一条重链在dfs序中都是连续的一段
两点之间的路径就转化为了序列上O(logn)个区间
就可以对dfs序建线段树

1.求lca
2.路径查询/修改
3.树链求并 O(k*logn*logn)  (O(klogn)个区间排序求并+查询)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,s;
vector<int> e[N];
int siz[N],son[N],depth[N],fa[N];
int l[N],r[N],id[N],tot,top[N];

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

// O(logn)
int lca(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(depth[top[u]]>depth[top[v]]) u=fa[top[u]];
        else v=fa[top[v]];
    }
    if(depth[u]<depth[v]) return u;
    else return v;
}

void solve()
{
    cin >> n >> m >> s;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs1(s,0);
    dfs2(s,0,s);
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",lca(a,b));
    }
}

int main()
{
    solve();
    return 0;
}