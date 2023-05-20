/*
dfs序写法   O(n * m)
0是虚拟源点
*/
#include <bits/stdc++.h>

using namespace std;

const int N=310;

int f[N][N],w[N],v[N],r[N],tot,id[N];
int n,m;
vector<int> e[N];

void dfs(int u)
{
    id[++tot]=u;
    for(auto s : e[u])
        dfs(s);
    r[u]=tot;
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        int a,p;
        scanf("%d%d",&p,&a);
        w[i]=a;
        v[i]=1;
        if(!p) e[0].push_back(i);
        else e[p].push_back(i);
    }
    
    dfs(0);
    
    for(int i=n;i>=0;i--)
        for(int j=1;j<=m;j++)
            if(j>=v[id[i]]) f[i][j]=max(f[r[id[i]]+1][j],f[i+1][j-v[id[i]]]+w[id[i]]);
            else f[i][j]=f[r[id[i]]+1][j];
    
    printf("%d\n",f[0][m]);
    
    return 0;
}