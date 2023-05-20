//定义f[i][j]表示以b[j]结尾的LCIS
#include <iostream>

using namespace std;

const int N=3010;

int n,a[N],b[N],f[N][N];

int main()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    
    for(int i=1;i<=n;i++)
    {
        int maxv=0; 
        // maxv表示f[i-1][1-j]中满足 b[j]<a[i] 的最大值
        for(int j=1;j<=n;j++)
        {
            f[i][j]=f[i-1][j];
            if(a[i]==b[j]) f[i][j]=max(f[i][j],maxv+1);
            if(b[j]<a[i]) maxv=max(maxv,f[i-1][j]);
        }
    }
    
    int res=0;
    for(int i=1;i<=n;i++) res=max(res,f[n][i]);
    
    printf("%d\n",res);
    
    return 0;
}