/*
a[i] <= m   O(mlogm)
给定 a[i] 解决 f[mask]=sum(a[i]) 的求解   其中 i是所有mask的子集 

定义 dp[i][mask] 代表只有二进制从低到高到i位和mask不同的 sum(a[i])
    if( mask>>i &1 == 0) dp[i][mask] = dp[i-1][mask]
    else dp[i][mask] = dp[i-1][mask] + dp[i-1][mask^(1<<i)]
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=1e5+10,M=1<<17;

int n,m,k;
ll dp[M];
int a[N];

void solve()
{
    cin >> n;
    int maxv=M-1;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        a[i]=x;
        dp[x]++;
    }

    //i从0开始
    for(int i=0;i<17;i++)
        for(int j=M-1;j>=0;j--)
            if(j>>i&1) dp[j]+=dp[j^(1<<i)];

    ll res=0;
    for(int i=0;i<n;i++)
        res+=dp[a[i]^maxv];

    cout << res << endl;
}