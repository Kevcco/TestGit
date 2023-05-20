//求最优解方案数

#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=1010;

int n,m,p;
int f[N],g[N];

void solve()
{
    cin >> n >> m;

    for(int i=0;i<=m;i++) g[i]=1;

    for(int i=1;i<=n;i++)
    {
        int v,w;
        scanf("%d%d",&v,&w);

        for(int j=m;j>=v;j--)
        {
            int t=f[j-v]+w;
            if(f[j]<t) f[j]=t,g[j]=g[j-v];
            else if(f[j]==t) g[j]=(g[j]+g[j-v])%mod;
        }
    }

    printf("%d\n",g[m]);
}