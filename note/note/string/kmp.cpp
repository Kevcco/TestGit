/*
字符串匹配:
(1) hash O(n+m)
(2) kmp  O(n+m)

ne[i] : 1 - i 的 最长border 即最长的前后缀匹配
f[i] : 以 i 结尾 的 能和p匹配的最大长度  即最长的 p前缀 和 s[1 - i]后缀 匹配

先预处理 p 的 ne[] 数组   然后和s串匹配  j最多 + O(n) 次 因此最多 - O(n) 次 总 O(n)
简便写法： 发现求ne数组和匹配其实是一样的 可以把s接到p后面 中间加一个'#'隔开防止错误匹配
          然后直接求一遍ne数组即可   ne[m+2] - ne[m+n+1] 也就是 f[1] - f[n]


1.最小循环覆盖 给定 求一个最短的字符串t 使得t循环若干次后 s是t的前缀
  结论 : min_lenth = n - ne[n]
  假设一个循环覆盖的长度是 t 那么可以推出 n-t 是 s 的 一个border
  反之 假设 t 是 一个 border 那么可以推出 s的 n-t 这么长的前缀 是 一个循环覆盖

2.周期 字符串s的周期指 s = aaa...aa  
  先证明 所有的循环覆盖 一定是 最小循环覆盖的倍数
  假设t是最小循环覆盖 t' 是 > t 的一个循环覆盖 假设 t | t' 不成立
  那么 设 d = gcd(t,t') 可知 d < t 下证 d 是 一个循环覆盖
  由裴蜀定理  d = x*t + y*t' 故  s[i] = s[i + x*t] = s[i + x*t + y*t] = s[i + d]
  得证 故假设不成立 故结论成立 
  所以 t = n - ne[n] 如果 t | n 那么 t 就是最短的周期 否则 不存在周期(或者是s本身)

总结 : t = n - ne[n] 是 s 的最小循环覆盖 并且 其他的循环覆盖长度是t的倍数
       假设 t | n , 那么 t 就是 s 的最小周期 否则 不存在周期

3.求 s 的 所有 border :  ne[n] 是最长 border ne[ne[n]] 是次长 以此类推
        while(ne[n]) n=ne[n];

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=1e6+10,M=1e5+10;

int n,m;
char s[N],p[M];
int ne[M],f[N];

void kmp()
{
    ne[1]=0;
    for(int i=2,j=0;i<=m;i++)
    {
        while(j&&p[j+1]!=p[i]) j=ne[j];
        if(p[j+1]==p[i]) j++;
        ne[i]=j;
    }
    for(int i=1,j=0;i<=n;i++)
    {
        while((j==m)||(j&&p[j+1]!=s[i])) j=ne[j];
        if(p[j+1]==s[i]) j++;
        f[i]=j;
    }
}

void kmp2()
{
    p[m+1]='#';
    for(int i=1,j=m+2;i<=n;i++,j++) p[j]=s[i];
    ne[1]=0;
    for(int i=2,j=0;i<=n+m+1;i++)
    {
        while(j&&p[i]!=p[j+1]) j=ne[j];
        if(p[i]==p[j+1]) j++;
        ne[i]=j;
    }

    for(int i=m+2;i<=m+n+1;i++)
        if(ne[i]==m) printf("%d ",i-m-m-1);
}

void solve()
{
    
}

int main()
{
    solve();
    return 0;
}