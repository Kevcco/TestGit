/*
求 ai | (aj & ak)  i<j<k  的最大值
dp[i][j] 表示j的超集中前二大的下标

*/
#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=1e6+10,M=1<<21;

int n,m,p[N];
pair<int,int> dp[M];

void insert(int mask,int u)
{
    if(u>dp[mask].first) dp[mask].second=dp[mask].first,dp[mask].first=u;
    else if(u>dp[mask].second&&u!=dp[mask].first) dp[mask].second=u;
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i),insert(p[i],i);
    for(int j=0;j<=20;j++)
        for(int i=0;i<M;i++)
            if((i>>j&1)==0)
                insert(i,dp[i^(1<<j)].first),insert(i,dp[i^(1<<j)].second);
    int ans=0;
    for(int i=1;i<n-1;i++)
    {
        int res=0;
        int mask=0;
        for(int j=20;j>=0;j--)
        {
            if(p[i]>>j&1) res+=(1<<j);
            else if(dp[mask|(1<<j)].second>i) res+=(1<<j),mask|=(1<<j);
        }
        ans=max(ans,res);
    }

    cout << ans << endl;
}