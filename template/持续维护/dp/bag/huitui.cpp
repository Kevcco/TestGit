/*
求所有的 1<= i <= n,1<=x<=m
去掉第i件物品，装满体积为x的背包的方案数

回退背包，只适用求方案数
所有物品先跑一遍背包
对于任意的i，可以O(m)删掉这个物品的贡献
O(n * m) 
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=10,N=2010;

int n,m,k;
int f[N],v[N];

void solve()
{
    cin >> n >> m;
    f[0]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",v+i);
        for(int j=m;j>=v[i];j--)
            f[j]+=f[j-v[i]],f[j]%=mod;
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=v[i];j<=m;j++)
            f[j]-=f[j-v[i]],f[j]=(f[j]+mod)%mod;
        for(int i=1;i<=m;i++) printf("%d",f[i]);
        puts("");
        for(int j=m;j>=v[i];j--)
            f[j]+=f[j-v[i]],f[j]%=mod;
    }
}

int main()
{
    solve();
    return 0;
}