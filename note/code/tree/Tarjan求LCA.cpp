#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,root,p[N];
int ans[N],h[N],e[N*2],ne[N*2],idx;
bool st[N];
vector<pii> query[N];

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

int find(int x)
{
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}

void tarjan(int u,int fa)
{
    st[u]=1;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        tarjan(j,u);
        p[j]=u;
    }
    for(auto x : query[u])
    {
        int v=x.first,id=x.second;
        if(st[v]) ans[id]=find(p[v]);
    }
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<=n;i++) h[i]=-1,p[i]=i;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        query[a].push_back({b,i});
        query[b].push_back({a,i});
    }

    tarjan(root,0);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);

}

int main()
{
    solve();
    return 0;
}