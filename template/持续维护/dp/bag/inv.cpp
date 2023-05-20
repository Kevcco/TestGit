/*
根据dp结果反推物品的属性

n个物品，每个物品有重量 wi ,对于每个物品，每次可选择购买整个，或者购买半个
现在知道  1<=k<=m  总重量 = k的方案数，求n个物品的重量
每次找到最小的 f[i] > 0 的 i (i > 0),那么 f[i]只能是由半个物品转移而来，因此就
确定了一个物品 i*2, 然后将这个物品的贡献删去
O(n * m)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=998244353,N=5010;

int n,m,k;
int dp[N];

void solve()
{
    cin >> m;
    vector<int> res;
    for(int i=1;i<=m;i++) scanf("%d",&dp[i]);
    dp[0]=1;
    for(int i=1;i<=m;i++)
    {
        while(dp[i])
        {
            res.push_back(i*2);
            for(int j=i;j<=m;j++)
            {
                dp[j]-=dp[j-i],dp[j]=(dp[j]+mod)%mod;
                if(j>=2*i) dp[j]-=dp[j-2*i],dp[j]=(dp[j]+mod)%mod;
            }
        }
    }

    for(auto x : res) printf("%d ",x); 
}

int main()
{
    solve();
    return 0;
}