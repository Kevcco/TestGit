/*
给定 n 个物品 m体积背包  每个物品 有 v w 选取若干物品装背包
n件物品，求考虑去掉某一件物品的01背包   
定义 f[i][j] 是只考虑前i件物品的01背包   g[i][j] 是只考虑后i件的01背包
去掉第i件的背包就是 f[i-1][j] 和 g[n-i][j] 组合起来
可以 O(m) 时间求去掉第i件物品，体积不超过v的最大值
具体就是 dp[v] = max (f[i-1][j] + g[n-i][v-j])
O(n * m + q * m)
*/
#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=5010;

int n,m,k,v[N],w[N];
int f[N][N],g[N][N];
int dp[N]; // dp[i] 为去掉第i个物品，体积不超过 m 的最大值


void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d%d",v+i,w+i);

    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            f[i][j]=f[i-1][j];
            if(j>=v[i]) f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);
        }
    }

    for(int i=n;i>1;i--)
    {
        for(int j=1;j<=m;j++)
        {
            g[i][j]=g[i+1][j];
            if(j>=v[i]) g[i][j]=max(g[i][j],g[i+1][j-v[i]]+w[i]);
        }
    }

    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
            dp[i]=max(dp[i],f[i-1][j]+g[n-i][m-j]);
}