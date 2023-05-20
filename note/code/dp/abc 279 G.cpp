/*
给定 n,k,c   k,n <= 1e6 , c <= 1e9
给连续的n个方格染色 每个方格可以染c种颜色 但是要保证对于任意长为k的区间，至多有两种颜色
求给n个染色的方案数

考虑 dp[i] 表示染前i个方格且合法的方案数
 (1) 若前 k-1 个格子，也就是[i-k+1,i-1] 有两种颜色,那么第i个格子只可以染两种颜色
     前k-1个格子有两种颜色的方案数 = 前 k-1 个格子的所有方案数 - 前 k-1 个格子只有一种颜色的方案数
      = dp[i-1] - dp[i-k+1] (并不是dp[i-1] - dp[i-k] * c 因为有可能不合法)
      故 dp[i] += (dp[i-1] - dp[i-k+1]) * 2;
      注意如果 i-k+1 < 1 说明前面不足k-1个 那么 只有一种颜色的方案数就是 c 
（2）若前 k-1个格子只有一种颜色 那么第i个格子任意染 也就是
       dp[i] += dp[i-k+1] * c;
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=998244353,N=1e6+10;

int n,k,c;
int dp[N];

void solve()
{
    cin >> n >> k >> c;
    dp[1]=c%mod;
    for(int i=2;i<=n;i++)
    {
        dp[i]=((ll)dp[i-1]-dp[max(i-k+1,1)]+mod)*2%mod;
        dp[i]=(dp[i]+(ll)dp[max(1,i-k+1)]*c%mod)%mod;
    }
    printf("%d\n",dp[n]);
}

int main()
{
    solve();
    return 0;
}