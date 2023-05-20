/*

一. 逆元
    
对任意 a  a / b mod p = a * x mod p   x称为 b mod p 下的逆元
将除法变成乘法 从而 如果 a 过大 可以提前 mod p 
a mod p = a * b * x mod p  推得
b * x mod p = 1

1.b mod p 意义下 存在逆元的充要条件  gcd(b,p) = 1 即 b,p互质 (线性同余方程 b*x + p*y = 1)
  逆元在 mod p 意义下 唯一存在
2.求法
    (1) p 是质数     费马定理 + 快速幂
        由费马定理 b^p-1 mod p = 1
        立即得到逆元 x = b^p-2 mod p

    (2) p 不是质数    扩展欧几里得算法
        b * x mod p = 1  ->  b * x + p * y = 1  
        求得一个特殊解后 变成 0 - p-1 范围内即可

    (3) 求 1 - n 逆元   inv[i] = (p - p / i) * inv[p % i] % p;

    (4) 求 1! - n! 逆元
        先求出来 n!逆元 然后从后往前递推  inv[i-1] = inv[i] * i % p;  

    (5) 求 a1 a2 ... an 的逆元
        前缀乘积si 先求出sn的逆元 然后 invs[i-1]= invs[i] * a[i] % p;
        而 inv[i] = s[i-1] * invs[i] % p;  (s[0]=1)

3. a / b mod p 如果b p不互质 逆元不存在的处理方法
   a / b mod p = a mod (p * b) / b  （a mod (p * b）一定整除 b)
   这种方法任何情况都适用，不管逆元存不存在

二. exgcd

    (1)用于求解 ax + by = gcd(a,b) 的特解 x0,y0
        通解 x = x0 + b/d * k , y = y0 - a/d * k 
        最小正整数解 t = b/d , x = ( x0 % t + t ) % t 
    (2)普通线性同余方程  ax + by = c  (ax 同余 c mod b)
        先解 ax + by = gcd(a,b) = d  如果 c整除d 有解 否则无解
        则线性同余方程的解  x0' =   x0* c/d   x' = x0' + b/d * k   x' 同余 b/d
        最小正整数解 t = b/d , x = ( x0 % t + t ) % t 


三. 中国剩余定理

    x mod mi = ai
    (1) mi mj 两两互质
        令 M = m1 * m2 * ... * mn
        x 的通解关于 M 同余
        求特解: 构造  x0 = sum ( ai * M/mi * ti )   ti 是 M/mi mod mi 的逆元
        验证可知 x0是解： 对于 第一个方程而言  x0除了第一项,其他项 mod mi = 0
                因为M/mi 是 m1 的倍数 则 x0 = a1 * M /m1 * t1
                x0 mod m1 = a1 * M/mi * t1 =a1 * (M/mi) / (M/mi)  mod m1 = a1  成立

    (2) mi,mi 无限制  扩展中国剩余定理
        考虑合并两个方程 merge
        x = a mod b     x = c mod d
        设 x = bt + a    bt + a + dt'= c   bt + dt' = c-a   exgcd 解出 t = t0 + d/g * k
        x = b*t0 + a + b*d/g *k  因此新的 a = b*t0 + a  b = b*d/g; 

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

// 逆元
// 快速幂求
int inv1(int b,int p)
{
    return qmi(b,p-2,p);
}

//扩展欧几里得算法
// ax + by = 1 有解的条件是 gcd (a,b) = 1    
// 直接解 ax + by = gcd (a,b) 即可
int inv2(int b,int p)
{
    ll x,y;
    ll d=exgcd(b,p,x,y);
    if(d!=1) return -1;
    return (x%p+p)%p;    //x 通解  x = x0 + b/d * k 同余 b/d,同余 b
}


//线性求逆元  O(n)求 1 - n 所有数 mod p 的逆元
int inv[N];
void inv3(int n,int p)
{
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=(ll)(p-p/i)*inv[p%i]%p;
}



//求阶乘逆元 求 1! - n! 逆元 
int infact[N];
void inv4(int n,int p)
{
    int res=1;
    for(int i=2;i<=n;i++) res=(ll)res*i%p;
    infact[n]=inv1(res,p);
    for(int i=n-1;i>0;i--)
        infact[i]=(ll)infact[i+1]*(i+1)%p;
}           


// 中国剩余定理
// x = bi mod ai
void CRT()
{
    cin >> n;
    ll M=1;
    for(int i=0;i<n;i++)
    {
        cin >> a[i] >> b[i];
        M*=a[i];
    }
    
    ll res=0;
    for(int i=0;i<n;i++)
    {
        ll m=M/a[i];
        ll x,y;
        exgcd(m,a[i],x,y);
        x%=a[i];
        res+=(ll)b[i]*m*x;
    }
    res=(res%M+M)%M;
    cout << res;
}


//合并两个方程 x = a mod b   x = c mod d
void merge(ll &a,ll &b,ll c,ll d)
{
    //if(a==-1&&b==-1) return;
    a=(a+b)%b;
    c=(c+d)%d;
    ll x,y;
    ll g=exgcd(b,d,x,y);
    if((c-a)%g)
    {
        a=b=-1;
        return;
    }
    d/=g;
    ll t0=(c-a)/g%d*x%d;
    if(t0<0) t0+=d;  //找到最小的非负特解t0
    a=b*t0+a; // a在 0 - b-1 之间
    b=b*d;
}

void exCRT()
{
    ll a=0,b=1;
    for(int i=0;i<n;i++)
    {
        ll c,d;
        cin >> c >> d;
        merge(a,b,c,d);
    }

    printf("%lld\n",a);
}


int main()
{
    return 0;
}
