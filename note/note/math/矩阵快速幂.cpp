/*
矩阵乘法: 解决递推式 常见于dp 用矩阵乘法加速状态转移
          适合 f[i][j] = sum (f[i-1][k]) 并且k的选取不依赖i 此时两层之间的状态转移矩阵a是固定的
          初始 f[1-m] 相当于f[0][1-m]     f*a^n = f 此时 f 就是 f[n][1-m] 
dp[n][m] 直接dp 时间复杂度 O(nm)
矩阵乘法  O(m^3*logn) 如果 n很大,m很小 适合


1.路径数量统计: 给定有向图 统计从 u->v 正好经过k条边的路径个数
    f[i][j] 表示经过i条边到j的路径数
    n <= 200  m <= 2e4  k <= 1e9
  初始矩阵 f[200]  f[i]表示经过0条边到达u的路径个数
    a[200][200] 即 邻接矩阵 
    f每乘一次a  f[i]=sum(f[j]*a[j][i]) 相当于再走一条边的过程 
    因此经过k次迭代 f[i]就表示经过k条边的路径

2.

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=102;

ll n,m;
ll a[N][N],f[N];

void fa()
{
    ll t[N]={0};
    for(int i=1;i<=m;i++)
        if(f[i])
            for(int j=1;j<=m;j++)
                if(a[i][j])
                    t[j]+=f[i]*a[i][j],t[j]%=mod;
    memcpy(f,t,sizeof t);
}

void aa()
{
    ll t[N][N]={0};
    for(int i=1;i<=m;i++)
        for(int k=1;k<=m;k++)
            if(a[i][k])
                for(int j=1;j<=m;j++)
                    if(a[k][j])
                        t[i][j]+=a[i][k]*a[k][j],t[i][j]%=mod;
    memcpy(a,t,sizeof t);
}

void qmi(ll x)
{
    while(x)
    {
        if(x&1) fa();
        aa();
        x>>=1;
    }
}

void solve()
{
    cin >> n >> m;
    for(int i=2;i<=m;i++) a[i][i-1]=1;
    a[1][m]=a[m][m]=1;
    f[m]=1;
    qmi(n);
    printf("%d\n",f[m]);
}

int main()
{
    solve();
    return 0;
}