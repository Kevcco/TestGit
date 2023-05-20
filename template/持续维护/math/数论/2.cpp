/*
逆元
(1) p 是质数
x = b^p-2 mod p

(2) p 不是质数    
扩展欧几里得算法
b * x mod p = 1  ->  b * x + p * y = 1  
求得一个特殊解后 变成 0 - p-1 范围内即可

(3) 求 1 - n 逆元   inv[i] = (p - p / i) * inv[p % i] % p;

(4) 求 1! - n! 逆元
先求出来 n!逆元 然后从后往前递推  inv[i-1] = inv[i] * i % p;  

(5) 求 a1 a2 ... an 的逆元
前缀乘积si 先求出sn的逆元 然后 invs[i-1]= invs[i] * a[i] % p;
而 inv[i] = s[i-1] * invs[i] % p;  (s[0]=1)

(6) a / b mod p 如果b p不互质
   a / b mod p = a mod (p * b) / b  

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e6+10;

ll res,m1,a1,m2,a2;
int n,a[N],b[N];

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

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y=y-a/b*x;
    return d;
}

// (1)
int inv1(int b,int p)
{
    return qmi(b,p-2,p);
}

// (2)
int inv2(int b,int p)
{
    ll x,y;
    ll d=exgcd(b,p,x,y);
    if(d!=1) return -1;
    return (x%p+p)%p;    //x 通解  x = x0 + b/d * k 同余 b/d,同余 b
}


//求 1 - n 的逆元
int inv[N];
void inv3(int n,int p)
{
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=(ll)(p-p/i)*inv[p%i]%p;
}

//求 1! - n! 逆元 
int infact[N];
void inv4(int n,int p)
{
    int res=1;
    for(int i=2;i<=n;i++) res=(ll)res*i%p;
    infact[n]=inv1(res,p);
    for(int i=n-1;i>0;i--)
        infact[i]=(ll)infact[i+1]*(i+1)%p;
}           

