/*
一.分解质因数   
ai <= 1e9
1.暴力循环 O(sqrt(n))
2.预处理出 2 - sqrt(n) 内的质数 直接枚举质数 质数个数是 sqrt(n) / log sqrt(n) 大概快10倍

  单个分解 直接暴力即可  
  多个分解 就需要预处理 预处理 O(3e4) 分解每一个大概需要 3e3 时间  能分解 1e4 - 1e5 个数  


ai <= 1e18  大数分解质因子
1.本身是乘积形式 a*b  a,b <= 1e9     分别对 a,b 分解
2. waiting...

二.分解因子

因子个数上界  
n <= 1e8 d(n) <= 1e3
n <= 1e18 d(n) <= 1e5


ai <= 1e9  暴力分解 O(sqrt(n))
ai <= 1e18 先分解质因数 再dfs枚举因子(枚举所有质因子指数的分配) 由于因子个数 <=1e5 不会超时


三.求约数和/个数
1.单个数: 先分解质因数 再公式算  O(sqrt(n))
2.求 1 - n 这 n 个数各自约数和
    枚举约数 i : i<=n  枚举i的倍数 i*j : i*j<=n
    O(nlogn)

四. 最大公约数
(1)gcd(a,b) O(logn)
(2)求n个数的最大公约数 d=0; for(i=1 to n) d=gcd(d,ai)  时间复杂度O(n+logai) 而不是 O(n * log ai)
(3)质因子角度考虑 gcd(a,b) a = p1^a1 * p2^a2 * ...  b = p1^b1 * p2^b2 ... 
    那么 d = p1^min(a1,b1) * p2^min(a2,b2) * ...
    (最小公倍数就是max)

*/



#include <bits/stdc++.h>

#define YES puts("YES")
#define Yes puts("Yes")
#define NO puts("NO")
#define No puts("No")

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;




// dfs 枚举因子
vector<pii> prime;
vector<pair<ll,ll>> factor;
void dfs(int id,ll k1,ll k2) 
{
    if(id==prime.size()) 
    {
        factor.push_back({k1,k2});
        return;
    }
    int p=prime[id].first,cnt=prime[id].second;
    ll pow=1; 
    for(int i=1;i<=cnt;i++) pow*=p;
    ll res=1;
    for(int i=0; i<=cnt;i++) 
    {
        dfs(id+1,k1*res,k2*(pow/res));
        res*=p;
    }
}



int main()
{
    return 0;
}