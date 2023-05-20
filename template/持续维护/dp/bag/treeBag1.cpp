//基于dfs  O(n * m * m)
#include <bits/stdc++.h>

using namespace std;

const int N=110;

int f[N][N],w[N],v[N];
int root,n,m;
vector<int> e[N];


void dfs(int u)
{
    for(int i=v[u];i<=m;i++) f[u][i]=w[u];
    for(auto s : e[u])
    {
        dfs(s);
        for(int j=m;j>=v[u];j--)
            for(int k=0;k<=j-v[u];k++)
                f[u][j]=max(f[u][j],f[u][j-k]+f[s][k]);
    }
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        int a,b,p;
        scanf("%d%d%d",&a,&b,&p);
        v[i]=a,w[i]=b;
        if(p==-1) root=i;
        else e[p].push_back(i);
    }
    
    dfs(root);
    
    printf("%d\n",f[root][m]);
    
    return 0;
}