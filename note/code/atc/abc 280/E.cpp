/*

怪物有 n 血    n <= 2e5
每次攻击有 p/100 的概率造成 2 伤害, 有 1 - p/100 的概率造成 1 伤害
问 杀死怪物的期望攻击次数




注意到杀死怪物的情况: 
1. 2 -> 0 or 1 -> 0     
2. 1 -> -1

idea1:
枚举杀死怪物的次数k 计算k次杀死怪物的概率p  ans += k*p

如何计算p：k次杀死怪物   
    1. 正好造成n点伤害 即 n-k 次 2, 2k-n 次 1
    2. 正好造成n-1点伤害 最后一次造成 2 点伤害 (注意不是正好造成n+1点伤害,因为其包含n -> n+1)
利用组合数计算即可


*/


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=998244353,N=2e5+10;

int n,m,k;
int p[N],infact[N],fact[N];
ll ans;

int qmi(int a,int k,int p)
{
    int res=1;
    while(k)
    {
        if(k&1) res=(ll)res*a%p;
        a=(ll)a*a%p;
        k>>=1;
    }
    return res;
}

void solve()
{
    cin >> n >> m;

    fact[0]=fact[1]=1;
    for(int i=2;i<=n;i++)
        fact[i]=(ll)fact[i-1]*i%mod;

    infact[n]=qmi(fact[n],mod-2,mod);
    for(int i=n-1;i>=0;i--)
        infact[i]=(ll)infact[i+1]*(i+1)%mod;

    int inv=qmi(100,mod-2,mod);
    int p=(ll)m*inv%mod;
    int q=(ll)(100-m)*inv%mod;

    for(int k=1;k<=n;k++)
    {
        if(2*k>=n) ans=(ans+(ll)k*fact[k]%mod*infact[n-k]%mod*infact[2*k-n]%mod*qmi(p,n-k,mod)%mod*qmi(q,2*k-n,mod)%mod)%mod;
        if(2*k>=n+1) ans=(ans+(ll)k*fact[k-1]%mod*infact[n-k]%mod*infact[2*k-n-1]%mod*qmi(p,n-k+1,mod)%mod*qmi(q,2*k-n-1,mod)%mod)%mod;
    }

    cout << ans;
}

int main()
{
    solve();
    return 0;
}