/*
dp[n][m] 直接dp 时间复杂度 O(nm)
矩阵乘法  O(m^3*logn)
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