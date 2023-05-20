#include <iostream>
#include <algorithm>

using namespace std;

const int N=1010;

int n,V,f[N];

int main()
{
    cin >> n >> V;
    for(int i=1;i<=n;i++)
    {
        int v,w;
        scanf("%d%d",&v,&w);
        for(int j=v;j<=V;j++)
            f[j]=max(f[j],f[j-v]+w);
    }
    cout << f[V];
    return 0;
}