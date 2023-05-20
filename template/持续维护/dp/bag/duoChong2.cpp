//二进制优化  O(n * m * logs)

#include <iostream>
using namespace std;
const int M=2010;

int f[M],n,m;

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        int v,w,s;
        scanf("%d%d%d",&v,&w,&s);
        int k=1;
        while(k<=s)
        {
            int V=v*k,W=w*k;
            for(int j=m;j>=V;j--)
                f[j]=max(f[j],f[j-V]+W);
            s-=k;
            k*=2;
        }
        if(s)
        {            
            int V=v*s,W=w*s;
            for(int j=m;j>=V;j--)
                f[j]=max(f[j],f[j-V]+W);
        }
    }
    cout << f[m];
}