/*
求所有的 i s[i - n] 与 p 的最大前缀匹配
 s = p + '#' + s , 转化为 s[i - n] 与 s 的最大前缀匹配
 为了减少越界特判  s += '$'

z[i] : s[i - n] 与 s 的最长前缀匹配
维护 R 最大的 [L,R] L 是起点 R 是 最长匹配的终点
求 z[i]:
(1) 如果 i > R , 暴力匹配
(2) 如果 i <= R , 求出 [1,R-L+1] 中和 i在[L,R]位置一样的 k = i - L + 1 
         若  z[k] < R - i + 1  , 那么 z[i] = z[k]
         否则  z[i] = R - i + 1 , 然后继续暴力匹配
每次更新最大的[L,R]
每次进行暴力匹配时都会更新 R  因此时间复杂度 O(n)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int z[N],Z[N];
char s[N],p[N];

void exkmp()
{
    p[m+1]='@',s[n+1]='#';
    z[1]=0;
    int L=1,R=0;
    for(int i=2;i<=m;i++)
    {
        if(i>R) z[i]=0;
        else
        {
            int k=i-L+1;
            z[i]=min(z[k],R-i+1);
        }
        while(p[i+z[i]]==p[1+z[i]]) z[i]++;
        if(i+z[i]-1>R) L=i,R=i+z[i]-1;
    }

    L=0,R=0;
    for(int i=1;i<=n;i++)
    {
        if(i>R) Z[i]=0;
        else
        {
            int k=i-L+1;
            Z[i]=min(z[k],R-i+1);
        }
        while(s[i+Z[i]]==p[1+Z[i]]) Z[i]++;
        if(i+Z[i]-1>R) L=i,R=i+Z[i]-1;
    }
}

void solve()
{
    
}

int main()
{
    solve();
    return 0;
}