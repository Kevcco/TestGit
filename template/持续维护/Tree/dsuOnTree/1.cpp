/*
询问所有子树中，出现最多次数的颜色，有多少种
O(nlogn)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+10;

int n,c[N];
vector<int> e[N];
int son[N],siz[N],cnt[N];
int l[N],r[N],id[N],tot;
ll ans[N],sum,maxv;

void dfs(int u,int fa)
{
    l[u]=++tot;
    id[tot]=u;
    siz[u]=1;
    for(auto j : e[u])
    {
        if(j==fa) continue;
        dfs(j,u);
        siz[u]+=siz[j];
        if(siz[j]>siz[son[u]]) son[u]=j;
    }
    r[u]=tot;
}

void dfs2(int u,int fa,bool keep)
{
    for(auto j : e[u])
    {
        if(j==fa||j==son[u]) continue;
        dfs2(j,u,0);
    }

    if(son[u]) dfs2(son[u],u,1);

    for(auto j: e[u])
    {
        if(j==fa||j==son[u]) continue;
        for(int k=l[j];k<=r[j];k++)
        {
            int x=c[id[k]];
            cnt[x]++;
            if(cnt[x]>maxv) maxv=cnt[x],sum=0;
            if(cnt[x]==maxv) sum+=x;
        }
    }

    int x=c[u];
    cnt[x]++;
    if(cnt[x]>maxv) maxv=cnt[x],sum=0;
    if(cnt[x]==maxv) sum+=x;

    ans[u]=sum;
    if(!keep)
    {
        for(int i=l[u];i<=r[u];i++) cnt[c[id[i]]]--;
        maxv=0,sum=0;
    }
}

int main()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    
    dfs(1,0);
    dfs2(1,0,1);
    
    for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
    
    return 0;
}