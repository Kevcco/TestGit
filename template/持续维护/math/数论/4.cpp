/*
整除分块: 对于 n/i (下取整  1 <= i <= n) 
其取值只有 O(sqrt n)个

1.计算 sum (n/i)  i属于[1,n] 下取整
根据整除分块的性质 每次计算一整块 那么时间复杂度 O(sqrt n)
如何O(1)计算一整块: 对于每一块的左端点l 块内的值 d=n/l, 
块内的右端点就是满足 i*d<=n 的最大的i
故 r = n/d 下取整

2.计算 sum(n/i) 上取整 
  上取整 n/i = (n-1) / i + 1

3.计算 sum(k mod i)  i[1,n]
  k mod i = k - k/i * i 每一块都是等差数列
  注意边界 if(!d) r=n; else r = min(n,k/d);

4.计算 sum(f(i)*(n/i))
  一类题 可以预处理 f(i) 的前缀和 s[i] 然后整除分块
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];

// sum (n/i)
ll block()
{
    ll sum=0;
    for(int l=1;l<=n;l++)
    {
        ll d=n/l,r=n/d;
        sum+=(r-l+1)*d;
        l=r;
    }
    return sum;
}

int main()
{

    return 0;
}