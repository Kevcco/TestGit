
// tarjan 求路径上边权的最值
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10,INF=1e9;

int n,m,root,p[N];
int maxv[N],minv[N];
pii ans[N];
bool st[N];
vector<pii> query[N],e[N];
vector<array<int,3>> deal[N];

int find(int x)
{
    if(x!=p[x])
    {
        int t=p[x];
        p[x]=find(p[x]);
        minv[x]=min(minv[x],minv[t]);
        maxv[x]=max(maxv[x],maxv[t]);
    }
    return p[x];
}

void tarjan(int u,int fa)
{
    minv[u]=INF,maxv[u]=0;
    st[u]=1;
    for(auto v : e[u])
    {
        int j=v.first,w=v.second;
        if(j==fa) continue;
        tarjan(j,u);
        maxv[j]=minv[j]=w;
        p[j]=u;
    }
    for(auto x : query[u])
    {
        int v=x.first,id=x.second;
        if(st[v]) deal[find(v)].push_back({u,v,id});
    }

    for(auto x : deal[u])
    {
        find(x[0]),find(x[1]);
        int t1=min(minv[x[0]],minv[x[1]]);
        int t2=max(maxv[x[0]],maxv[x[1]]);
        ans[x[2]]={t1,t2};
    }
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }
    cin >> m;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        query[a].push_back({b,i});
        query[b].push_back({a,i});
    }

    tarjan(1,0);
    for(int i=1;i<=m;i++) printf("%d %d\n",ans[i].first,ans[i].second);

}

int main()
{
    solve();
    return 0;
}