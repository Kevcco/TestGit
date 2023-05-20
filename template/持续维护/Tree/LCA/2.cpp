
/*
欧拉序转为RMQ问题
对两个点u,v 他们的lca一定是
区间 pos[u] - pos[v] 中深度最小的那个点
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,root;
vector<int> e[N];
// pos[u]记录u第一次出现的位置
int depth[N],pos[N],tot; 
pii id[N*2],f[21][N*2];

void dfs(int u,int fa)
{
    depth[u]=depth[fa]+1;
    pos[u]=++tot;
    f[0][tot]={depth[u],u};
    for(auto v: e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        f[0][++tot]={depth[u],u};
    }
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(root,0);
    for(int j=1;j<=20;j++)
        for(int i=1;i+(1<<j)-1<=tot;i++)
            f[j][i]=min(f[j-1][i],f[j-1][i+(1<<j-1)]);

    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(pos[a]>pos[b]) swap(a,b);
        int k=31-__builtin_clz(pos[b]-pos[a]+1);
        printf("%d\n",min(f[k][pos[a]],f[k][pos[b]-(1<<k)+1]).second);
    }

}

int main()
{
    solve();
    return 0;
}