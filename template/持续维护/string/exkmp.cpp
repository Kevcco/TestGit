/*
求所有的 i s[i - n] 与 p 的最大前缀匹配
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