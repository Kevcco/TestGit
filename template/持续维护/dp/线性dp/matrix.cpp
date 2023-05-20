// 两条路同时走
#include <bits/stdc++.h>

using namespace std;

const int N=15;

int n,g[N][N],f[2*N][N][N];

int main()
{
    cin >> n;
    int x,y,w;
    while(scanf("%d%d%d",&x,&y,&w),x) g[x][y]=w;
    
    for(int i=2;i<=n*2;i++)
        for(int j=1;j<min(n+1,i);j++)
            for(int k=1;k<min(n+1,i);k++)
            {
                if(i-j>n||i-k>n) continue;
                f[i][j][k]=max({f[i-1][j-1][k],f[i-1][j-1][k-1],f[i-1][j][k],f[i-1][j][k-1]});
                f[i][j][k]+=g[j][i-j]+g[k][i-k];
                if(j==k) f[i][j][k]-=g[j][i-j];
            }
            
    printf("%d\n",f[2*n][n][n]);
}