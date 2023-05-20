/*
t = n - ne[n] 是 s 的最小循环覆盖 并且 
其他的循环覆盖长度是t的倍数
假设 t | n , 那么 t 就是 s 的最小周期 否则 不存在周期
求 s 的 所有 border :  ne[n] 是最长 border 
ne[ne[n]] 是次长 以此类推
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