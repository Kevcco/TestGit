/*
输出具体方案:保留二维，即保留中间状态，从后往前比较状态 反推转移的路径
字典序最小 ：逆序选择物体，反推时能选则选
*/
#include <bits/stdc++.h>

using namespace std;

const int N=1010;

int f[N][N],n,m,v[N],w[N];

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d%d",&v[i],&w[i]);
    
    for(int i=n;i;i--)
    {
        for(int j=0;j<=m;j++)
        {
            if(j<v[i]) f[i][j]=f[i+1][j];
            else f[i][j]=max(f[i+1][j],f[i+1][j-v[i]]+w[i]);
        }
    }
    
    for(int i=1;i<=n;i++)
    {
        if(m>=v[i]&&f[i][m]==f[i+1][m-v[i]]+w[i])
        {
            printf("%d ",i);
            m-=v[i];
        }
    }
    return 0;
}