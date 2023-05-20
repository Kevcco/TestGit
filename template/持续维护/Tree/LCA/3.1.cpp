
// O(n + m)
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,root,p[N];
int ans[N];
bool st[N];
vector<int> e[N];
vector<pii> query[N];


int find(int x)
{
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}

void tarjan(int u,int fa)
{
    st[u]=1;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        tarjan(v,u);
        p[v]=u;
    }
    for(auto x : query[u])
    {
        int v=x.first,id=x.second;
        if(st[v]) ans[id]=find(p[v]);
    }
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        query[a].push_back({b,i});
        query[b].push_back({a,i});
    }

    tarjan(root,0);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);

}

int main()
{
    solve();
    return 0;
}