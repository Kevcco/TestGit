// 树的中心
#include <bits/stdc++.h>

using namespace std;

const int N=10010,inf=0x3f3f3f3f;

int n,d1[N],d2[N],pos[N],up[N];
vector<pair<int,int>> e[N];

int dfs_d(int u,int fa)
{
    d1[u]=d2[u]=-inf; // 考虑负权
    for(auto v : e[u])
    {
        int j=v.first,w=v.second;
        if(j==fa) continue;
        int d=dfs_d(j,u)+w;
        if(d>=d1[u]) d2[u]=d1[u],d1[u]=d,pos[u]=j;
        else if(d>d2[u]) d2[u]=d;
    }
    
    if(d1[u]==-inf) return 0;
    else return d1[u];
}

void dfs_u(int u,int fa)
{
    for(auto v : e[u])
    {
        int j=v.first,w=v.second;
        if(j==fa) continue;
        up[j]=up[u]+w;
        if(j==pos[u]) up[j]=max(up[j],d2[u]+w);
        else up[j]=max(up[j],d1[u]+w);
        
        dfs_u(j,u);
    }
}

int main()
{
    cin >> n;
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }
    
    dfs_d(1,0);
    dfs_u(1,0);
    
    int res=inf;
    for(int i=1;i<=n;i++) res=min(res,max(d1[i],up[i]));
    
    printf("%d\n",res);
    
    return 0;
}