/*
求恰好装满背包的方案数
01背包  f[i][j]=f[i-1][j]+f[i-1][j-v]
完全背包  f[i][j]=f[i-1][j]+f[i][j-v]
多重背包  f[i][j]=f[i-1][j]+f[i-1][j-v]+...+f[i-1][j-s*v] (预处理前缀和）
*/

#include <bits/stdc++.h>

using namespace std;

const int N=110,mod=1e6+7;

int n,m;
int f[N],g[N];

int main()
{
    cin >> n >> m;
    
    f[0]=1,g[0]=1;
    for(int i=0,s;i<n;i++)
    {
        for(int j=1;j<=m;j++)g[j]=g[j-1]+f[j];
        cin >> s;
        for(int j=1;j<=m;j++)
        {
            if(j>s) f[j]=(g[j]-g[j-s-1])%mod;
            else f[j]=g[j]%mod;
        }
    }

    printf("%d",f[m]);
    return 0;
}