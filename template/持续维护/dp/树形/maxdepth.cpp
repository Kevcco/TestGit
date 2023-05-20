// 换根 求最大深度和
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=1e5+10;

int n,m,k,p[N],siz[N];
ll dp[N];
vector<pair<int,int>> e[N];

void pre(int u,int fa)
{
    siz[u]=p[u];
    for(auto v : e[u])
    {
        int j=v.first,w=v.second;
        if(j==fa) continue;
        pre(j,u);
        siz[u]+=siz[j];
        dp[1]+=(ll)siz[j]*w;
    }
}

void dfs(int u,int fa)
{
    for(auto v : e[u])
    {
        int j=v.first,w=v.second;
        if(j==fa) continue;
        dp[j]=dp[u]+(siz[1]-(ll)2*siz[j])*w;
        dfs(j,u);
    }
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }

    pre(1,0);
    dfs(1,0);
    ll res=1e18;
    for(int i=1;i<=n;i++) res=min(res,dp[i]);
    printf("%lld\n",res);
}
int main()
{
    solve();
    return 0;
}