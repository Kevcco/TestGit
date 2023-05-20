
/*
利用括号序，将两个点之间的路径变为连续的区间
具体而言 设 l[u] < l[v]
(1)若 lca(u,v) = u 则 u,v 之间的路径就是括号序列中 [l[u], l[v]]这一段里只出现一次的节点
(2)否则, u,v 之间的路径就是 [r[u], l[v]] 这一段里只出现一次的节点 + lca这个节点
因为只计算只出现一次的点 开一个cnt[]记录点的权值信息，同时开st[u] 记录编号为u的这个点的出现次数 
一旦st[u]为偶数，就要删除这个点的权值信息
求路径上出现的不重复数的个数
*/
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+10;

int n,m,a[N],cnt[N],st[N],l[N],r[N],id[N],tot,ans[N],res;
int p[20][N],dep[N];
vector<int> nums,e[N];
array<int,4> query[N];
int len;

bool cmp(array<int,4> &a,array<int,4> &b)
{
    if(a[0]/len!=b[0]/len) return a[0]<b[0];
    if(a[0]/len&1) return a[1]>b[1];
    return a[1]<b[1];
}

void dfs(int u,int fa)
{
    p[0][u]=fa,dep[u]=dep[fa]+1;
    l[u]=++tot;
    id[tot]=u;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
    }
    r[u]=++tot;
    id[tot]=u;
}

int lca(int u,int v)
{
    if(dep[v]>dep[u]) swap(u,v);
    int d=dep[u]-dep[v];
    for(int i=19;i>=0;i--)
        if(d>>i&1) u=p[i][u];
    if(u==v) return u;
    for(int i=19;i>=0;i--)
        if(p[i][u]!=p[i][v])
            u=p[i][u],v=p[i][v];
    return p[0][u];
}

void add(int x)
{
    st[x]^=1;
    if(st[x])
    {
        if(!cnt[a[x]]) res++;
        cnt[a[x]]++;
    }
    else
    {
        cnt[a[x]]--;
        if(!cnt[a[x]]) res--;
    }
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d",a+i),nums.push_back(a[i]);
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(nums.begin(),nums.end(),a[i])-nums.end()+1;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    
    dfs(1,0);
    
    len=(int)sqrt((double)tot*tot/m)+1;
    
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
            p[j][i]=p[j-1][p[j-1][i]];
    
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(l[x]>l[y]) swap(x,y);
        int w=lca(x,y);
        if(x==w) query[i]={l[x],l[y],i,0};
        else query[i]={r[x],l[y],i,w};
    }
    
    sort(query+1,query+m+1,cmp);
    
    for(int i=1,j=0,k=1;k<=m;k++)
    {
        int l=query[k][0],r=query[k][1],w=query[k][3];
        while(j<r) add(id[++j]);
        while(i>l) add(id[--i]);
        while(j>r) add(id[j--]);
        while(i<l) add(id[i++]);
        if(w)
        {
            add(w);
            ans[query[k][2]]=res;
            add(w);
        }
        else ans[query[k][2]]=res;
    }
    
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    
    return 0;
}