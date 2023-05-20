
// 预处理 O(nlogn) 单次询问 O(logn)
#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=5e5+10;

int n,m,root;
int p[N][20],d[N];
vector<int> e[N];

void dfs(int u,int fa)
{
    p[u][0]=fa;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        d[v]=d[u]+1;
        dfs(v,u);
    }
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }

    dfs(root,0);
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
            p[i][j]=p[p[i][j-1]][j-1];

    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(d[a]<d[b]) swap(a,b);
        int h=d[a]-d[b];
        for(int j=19;j>=0;j--)
            if(h>>j&1) a=p[a][j];
        if(a==b) {
            printf("%d\n",a);
            continue;
        }
        for(int j=19;j>=0;j--)
            if(p[a][j]!=p[b][j]) a=p[a][j],b=p[b][j];

        printf("%d\n",p[a][0]);
    }
}

int main()
{
    solve();
    return 0;
}