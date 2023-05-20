/*
高斯消元 O(n^3)

从 1 - n 每次消一列  消第i列时 从l行 - n行选择 a[j][i]的绝对值最大的那一行换到第l行 这样误差小
如果所有行在这一列都是0 直接跳过
否则 使用第l行 将 其他所有行的第i列都消成0 
这样 最后就 消成了 对角矩阵

最后判断解的情况：
 (1) 如果存在 l- n 某一行 的 b[i] != 0 说明 无解 
 (2) 如果 l <= n 说明有某一列全为0 有自由元 有无穷多解
 (3) 否则 有唯一解  x[i] = b[i] / a[i][i]


应用:
 (1) 求行列式 记录一个符号位sgn 每次交换两行 符号位变号 最后将主对角线元素相乘再乘sgn
 (2) 矩阵求逆
 (3) 解异或线性方程组 : 每次消元时都替换成异或
*/
#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7, N=110;
const double eps=1e-10;

int n,m,k;
double a[N][N], b[N];

void gauss()
{
    int l=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=l;j<=n;j++)
        {
            if(abs(a[j][i])>abs(a[l][i]))
            {
                for(int k=i;k<=n;k++) swap(a[j][k],a[l][k]);
                swap(b[j],b[l]);
            }
        }

        if(abs(a[l][i])<eps) continue;

        for(int j=1;j<=n;j++)
        {
            if(j!=l&&abs(a[j][i])>eps)
            {
                double d=a[j][i]/a[l][i];
                for(int k=i;k<=n;k++) a[j][k]-=d*a[l][k];
                b[j]-=d*b[l];
            }
        }
        l++;
    }

    for(int i=l;i<=n;i++)
    {
        if(abs(b[i])>eps)
        {
            //无解
            printf("-1\n");
            return;
        }
    }

    if(l<=n)
    {
        //无穷多解
        printf("-2\n");
        return;
    }

    for(int i=1;i<=n;i++) printf("%.10lf ",b[i]/a[i][i]);

}

void solve()
{
    
}

int main()
{
    solve();
    return 0;
}