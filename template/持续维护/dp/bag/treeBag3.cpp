/*
当物品体积都是1或者与节点个数相关时
上下界优化  O(n^n)

给定树 询问对于所有的1<=x<=n
满足某个节点集合的导出子图有x个连通块，这样的节点集合的个数
dp[i][u][j][0] 表示以u为根的子树, 不选u, 只考虑前i个儿子 有j个连通块的子集个数
dp[i][u][j][1] 表示以u为根的子树, 选u, 只考虑前i个儿子 有j个连通块的子集个数
dp[i][u][j][0] = sum ( dp[i-1][u][j-k][0] * (dp[][v][k][0]+dp[][v][k][1])) 
dp[i][u][j][1] = sum ( dp[i-1][u][j-k][1] * (dp[][v][k][0]+dp[][v][k+1][1])) 
v为第i个儿子, 0 <= k <= j
可以滚动数组 优化掉一维 dp[u][j][0/1]
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=998244353,N=5010;

int n,m,k;
int dp[N][N][2],siz[N],tmp[N][2];
vector<int> e[N];

void dfs(int u,int fa)
{
    siz[u]=1;
    dp[u][1][1]=dp[u][0][0]=1;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        for(int j=0;j<=siz[u]+siz[v];j++)
        {
            tmp[j][0]=dp[u][j][0],
            tmp[j][1]=dp[u][j][1],
            dp[u][j][1]=dp[u][j][0]=0;
        }
        for(int j=siz[u]+siz[v];j>=0;j--)
            for(int k=max(0,j-siz[u]);k<=min(j,siz[v]);k++) {
                dp[u][j][0]+=(ll)tmp[j-k][0]*(dp[v][k][0]+dp[v][k][1])%mod;
                dp[u][j][0]%=mod;
                dp[u][j][1]+=(ll)tmp[j-k][1]*(dp[v][k][0]+dp[v][k+1][1])%mod;
                dp[u][j][1]%=mod;
            }
                
        siz[u]+=siz[v];
    }

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

    dfs(1,0);

    for(int i=1;i<=n;i++)
        printf("%d\n",(dp[1][i][0]+dp[1][i][1])%mod);
}

int main()
{
    solve();
    return 0;
}