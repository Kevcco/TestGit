/*
1.求到 n 号点的概率: 
f[i] 表示从1号点到i号点的概率  
f[1]=1, f[i] = sum(f[j]/deg[j]) j存在一条指向i的出边

2.求到n号点的期望步数
f[i] 表示从i号点走到n号点的期望步数  
f[n]=0  f[i] = sum(f[j]/deg[x]) + 1  j为i的出边指向的点  

3.到达n号点的期望步数 图不保证是无环的
f[n]=0 线性方程组 高斯消元 O(n^3)

4.一个长为n的01串 每次等概率选择一位翻转 问将01串变成全0的期望步数
f[i] 表示当前串有i个1 变成i-1个1的期望步数   有f[n]=1
考虑i<n  f[i] = i/n * 1 + (1-i/n) * (1 + f[i+1] + f[i])
整理可得   i * f[i] = n + (n-i) * f[i+1]
假设给定串有cnt个1   res = sum(f[i]) i from 1 to cnt 
*/
// 4
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=998244353,N=1e6+10;

int n,m,k;
string x,y;

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
    cin >> n;
    cin >> x >> y;
    int cnt=0;
    for(int i=0;i<n;i++) cnt+=(x[i]!=y[i]);

    ll res=0;
    vector<int> f(n+1,0);
    f[n]=1;
    if(cnt==n) res+=1;
    for(int i=n-1;i>=1;i--)
    {
        int t=((ll)(n-i)*f[i+1]%mod+n)%mod;
        f[i]=(ll)t*qmi(i,mod-2,mod)%mod;
        if(i<=cnt) res+=f[i],res%=mod;
    }

    printf("%d\n",res);
}