/*

给定 n 个物品 m体积背包  每个物品 有 v w 选取若干物品装背包
询问 对于 1 <= i <= n 物品而言
不选第i个物品的最大价值 val1 总最大价值 val2 询问 最少使 wi 增加多少 满足 val2 > val1
输出 1-n n中情况


考虑去掉第 i 件物品的 01背包   1<=i<=n
    朴素做法是枚举物品 对每种情况单独做一次背包 O(n^2*m)
    优化做法是 定义 f[i][j] 是只考虑前i件物品的01背包   g[i][j] 是只考虑后i件的01背包
    那么其实 去掉第i件的背包就是 f[i-1][j] 和 g[n-i][j] 组合起来考虑即可
    具体的求 max 就是  max(f[i-1][j]+g[n-i][k])  j + k == m  O(n * m + m )

处理询问 就是处理  F[i][m]-F[i-vi]-wi+1  F[i][j] 代表去掉第i件物品的01背包
 val1 = F[i][m] 如果val2 > val1 那么 必然要选第 i 件物品 那么 val2 = F[i][m-vi]+wi   
 ans = val1 - val2 + 1 (严格大于)

总时间复杂度 O(nm)

Luogu P4141 问题有相似之处 但解法不一样
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5010;

int n,m,k;
int v[N],w[N];
int f[N][N],g[N][N];

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d%d",v+i,w+i);
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
        {
            f[i][j]=f[i-1][j];
            if(j>=v[i]) f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);
        }
    for(int i=n;i>1;i--)
        for(int j=1;j<=m;j++)
        {
            g[i][j]=g[i+1][j];
            if(j>=v[i]) g[i][j]=max(g[i][j],g[i+1][j-v[i]]+w[i]);
        }

    for(int i=1;i<=n;i++)
    {
        int val1=0,val2=0;
        for(int j=0;j<=m;j++)
            val1=max(val1,f[i-1][j]+g[n-i][m-j]);
        for(int j=0;j<=m-v[i];j++)
            val2=max(val2,f[i-1][j]+g[n-i][m-v[i]-j]);
        
        printf("%d\n",max(0,val1-val2-w[i]+1));
    }
}

int main()
{
    solve();
    return 0;
}