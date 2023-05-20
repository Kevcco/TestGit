#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;

int n,cnt;
int p[N];//p[i]:i的最小质因子
int pr[N];//所有质数
bool st[N];

//线性筛
void shai()
{
    for(int i=2;i<=n;i++)
    {
        if(!p[i]) p[i]=i,pr[cnt++]=i;
        for(int j=0;pr[j]*i<=n;j++)
        {
            p[pr[j]*i]=pr[j];
            if(p[i]==pr[j]) break;
        }
    }
}

// long long 取模  O(1)
// 计算  a*b mod m  a*b会爆ll
//转化为 a*b - (a*b)/m * m
// (a*b)/m 可以用 long double 计算 然后强转成ll   (a b都小于m a*b/m 一定<m 不会爆ll)
// res = a*b - d*m   虽然 a*b 和 d*m 都会爆ll 但是他们的差是一个在 0 - m-1 之间的数
// 因此溢出的部分本来就是相同的 不会影响作差的结果
// 最后两个if是防止浮点数计算出现误差 有可能d多算了1 res<0 也有可能d少算1 res>=m
ll longlong_mod(ll a,ll b,ll m)
{
    a%=m,b%=m;
    ll d=(long double)a*b/m;
    d=a*b-d*m;
    if(d>=m) d-=m;
    if(d<0) d+=m;
    return d;
}

// 快速乘方法 O(logn)
// 将 b拆成二进制  a*b = a*2^k + a*2^k-1 + ...
ll longlong_mul(ll a,ll b,ll p)
{
    a%=p,b%=p;
    ll res=0;
    while(b)
    {
        if(b&1) res=(res+a)%p;
        a=(a+a)%p;
    } 
    return res;
}


// 区间筛: 求 [l,r] 之间的素数个数   l,r <=1e14    r-l <= 1e7
// 我们知道一个合数一定有不超过其根号的质因子 因此我们可以预处理1e7以内的质数 然后利用埃氏筛的思想
// 将[l,r] 筛一遍  时间复杂度 O(n*loglogn)
int interval()
{
    ll l,r;
    cin >> l >> r;
    if(l==1) l=2;
    for(int i=0;i<cnt;i++)
    {
        int t=pr[i];
        for(ll j=r/t*t;j>=l&&j>t;j-=t) st[j-l]=1;
    }
    int sum=0;
    for(int i=0;i<=r-l;i++) sum+=(!st[i]);
    return sum;
}

int main()
{
    
    return 0;
}