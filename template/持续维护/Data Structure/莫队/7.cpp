
// 树上带修
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+10;

int n,m,q,a[N],l[N],r[N],id[N*2],tot,tt,qq;
ll ans[N],res;
int p[20][N],dep[N],v[N],w[N];
vector<int> e[N];
int cnt[N],st[N];
struct node
{
    int l,r,w,t,id;
}query[N];
int len;
struct 
{
    int x,y;
}modify[N];

bool cmp(node &a,node &b)
{
    if(a.l/len!=b.l/len) return a.l<b.l;
    if(a.r/len!=b.r/len) return a.r<b.r;
    return a.t<b.t;
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
    int t=a[x];
    st[x]^=1;
    if(st[x])
    {
        cnt[t]++;
        res+=(ll)v[t]*w[cnt[t]];
    }
    else
    {
        res-=(ll)v[t]*w[cnt[t]];
        cnt[t]--;
    }
}

void swapp(int m1,int m2)
{
    res-=(ll)v[m1]*w[cnt[m1]];
    cnt[m1]--;
    cnt[m2]++;
    res+=(ll)v[m2]*w[cnt[m2]];
}

void change(int t,int L,int R)
{
    int x=modify[t].x,y=modify[t].y;
    // 判断是否在区间内
    if(st[x]) swapp(a[x],y);
    swap(a[x],modify[t].y);
}

int main()
{
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++) scanf("%d",v+i);
    for(int i=1;i<=n;i++) scanf("%d",w+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(1,0);
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
            p[j][i]=p[j-1][p[j-1][i]];

    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=q;i++)
    {
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt)
        {
            ++qq;
            if(l[x]>l[y]) swap(x,y);
            int w=lca(x,y);
            if(x==w) query[qq]={l[x],l[y],0,tt,qq};
            else query[qq]={r[x],l[y],w,tt,qq};
        }
        else
        {
            ++tt;
            modify[tt]={x,y};
        }
    }
    
    len=(int)cbrt((double)tot*tot*max(1,tt)/qq)+1;
    
    sort(query+1,query+qq+1,cmp);
    
    for(int i=1,j=0,T=0,k=1;k<=qq;k++)
    {
        int l=query[k].l,r=query[k].r,w=query[k].w,t=query[k].t;
        while(j<r) add(id[++j]);
        while(i>l) add(id[--i]);
        while(j>r) add(id[j--]);
        while(i<l) add(id[i++]);
        while(T<t) change(++T,i,j);
        while(T>t) change(T--,i,j);
        if(w)
        {
            add(w);
            ans[query[k].id]=res;
            add(w);
        }
        else ans[query[k].id]=res;
    }
    
    for(int i=1;i<=qq;i++) printf("%lld\n",ans[i]);
    
    return 0;
}