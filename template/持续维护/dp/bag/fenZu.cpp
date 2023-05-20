// o(n * m * s)
#include <bits/stdc++.h>

using namespace std;

const int N=110;

int f[N],n,m,s,v[N],w[N];

int main()
{
    cin >> n >> m;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&s);
        for(int i=0;i<s;i++)
            scanf("%d%d",&v[i],&w[i]);

        for(int j=m;j>=0;j--)
            for(int k=0;k<s;k++)
                if(j>=v[k]) f[j]=max(f[j],f[j-v[k]]+w[k]);
    }
    cout << f[m];
    
    return 0;
}