
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+10;

int n,m,f[18][N];

void init()
{
    for(int j=1;j<18;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            f[j][i]=max(f[j-1][i],f[j-1][i+(1<<j-1)]);
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        f[0][i]=x;
    }
    
    init();
    
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int k=31-__builtin_clz(r-l+1);
        printf("%d\n",max(f[k][l],f[k][r-(1<<k)+1]));
    }
}