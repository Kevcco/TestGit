
// 高斯消元  O(n^3)
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