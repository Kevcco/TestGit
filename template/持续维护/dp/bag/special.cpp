/*
01背包 三维属性a,b,w,求满足总的 a>=m,b>=p 的最小重量 w
普通背包  f[i][j],表示二维属性不超过i,j
本题      f[i][j]表示二维属性不小于，因此转移有所区别
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mod=1e9+7,N=110;

int n,m,p;
int f[N][N];

void solve()
{
    cin >> m >> p >> n;

    for(int j=0;j<=m;j++)
        for(int k=0;k<=p;k++)
            f[j][k]=0x3f3f3f3f;

    f[0][0]=0;

    for(int i=1;i<=n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        for(int j=m;j>=0;j--)
            for(int k=p;k>=0;k--)
                f[j][k]=min(f[j][k],f[max(0,j-a)][max(0,k-b)]+c);
    }

    printf("%d\n",f[m][p]);
}
