/*
给定n行m列矩阵，其元素值是0或1，
定义某一元素为隔离状态 ： 其与上下左右四个相邻的元素的值都不同，称为隔离
定义一次操作：将某一行所有元素值取反，即0变1，1变0
询问：使得矩阵所有元素都不是隔离状态的最少操作次数，若不可能则输出-1

1 <= n,m <= 1000




o(n^2)时间复杂度可解决，想到dp
从集合角度考虑，将前i行都变成合法后，无后效性，只需要专注于后面几行的操作，
只不过判断第i行是否合法需要用到第i+1行和第i-1行，也就是需要枚举状态，状压dp
必须要三维，两维不行，或者状压
并且状态只有0和1两种，也就是操作0次或1次
状态表示 f[i,j,k] 表示将前i-1行操作成合法状态，并且第i-1行的状态是j，第i行状态是k的操作集合
如何转移： f[i-1,u,j]  表示前i-2行合法，只需专注于第i-1行
i-2  u
i-1  j
i    k
if(此状态下第i-1行合法)  f[i,j,k]可以从 f[i-1,u,j]转移过来，并且如果k=1，则操作数再加1
因此 f[i,j,k] = min ( f[i-1,0,j] , f[i-1,1,j] ) + k 当然如果两种情况都不合法，f[i,j,k]=inf
最后再枚举 f[n,j,k] 判断第n行是否合法，如果合法，可以作为答案  

如果定义状态f[i,st] 前i-1行摆好，第i行是st
如何更新：f[i-1,0],f[i-1,1],并不能确定第i-1行是否合法，因为只知道第i-1行和第i行

*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N=1010;

bool g[N][N];
int n,m,f[N][2][2];


bool check(int i,int st1,int st2,int st3)
{
    if(i==1)
    {
        if((g[i][1]^st2)!=(g[i][2]^st2)&&(g[i][1]^st2)!=(g[i+1][1]^st3)) return false;
        if((g[i][m]^st2)!=(g[i][m-1]^st2)&&(g[i][m]^st2)!=(g[i+1][m]^st3)) return false;
        for(int j=2;j<m;j++)
        {
            bool x=g[i][j]^st2;
            if(x!=(g[i][j+1]^st2)&&x!=(g[i][j-1]^st2)&&x!=(g[i+1][j]^st3)) return false;
        }
        return true;
    }
    else if(i==n)
    {
        if((g[i][1]^st2)!=(g[i][2]^st2)&&(g[i][1]^st2)!=(g[i-1][1]^st1)) return false;
        if((g[i][m]^st2)!=(g[i][m-1]^st2)&&(g[i][m]^st2)!=(g[i-1][m]^st1)) return false;
        for(int j=2;j<m;j++)
        {
            bool x=g[i][j]^st2;
            if(x!=(g[i][j+1]^st2)&&x!=(g[i][j-1]^st2)&&x!=(g[i-1][j]^st1)) return false;
        }
        return true;
    }
    else
    {
        if((g[i][1]^st2)!=(g[i][2]^st2)&&(g[i][1]^st2)!=(g[i+1][1]^st3)&&(g[i][1]^st2)!=(g[i-1][1]^st1)) return false;
        if((g[i][m]^st2)!=(g[i][m-1]^st2)&&(g[i][m]^st2)!=(g[i+1][m]^st3)&&(g[i][m]^st2)!=(g[i-1][m]^st1)) return false;
        for(int j=2;j<m;j++)
        {
            bool x=g[i][j]^st2;
            if(x!=(g[i][j+1]^st2)&&x!=(g[i][j-1]^st2)&&x!=(g[i+1][j]^st3)&&x!=(g[i-1][j]^st1)) return false;
        }
        return true;
    }
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            g[i][j]=x;
            
        }
    //初始化
    memset(f,0x3f,sizeof f);
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++) 
            f[1][i][j]=j;

    //dp
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<2;j++)
        {
            for(int k=0;k<2;k++)
            {
                for(int u=0;u<2;u++)
                {
                    if(check(i-1,u,j,k)) f[i][j][k]=min(f[i][j][k],f[i-1][u][j]+k);
                }
            }
        }
    }

    //res
    int res=0x3f3f3f3f;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            if(check(n,i,j,0)) res=min(f[n][i][j],res);
            
    if(res==0x3f3f3f3f) res=-1;
    cout << res;

    return 0;
}