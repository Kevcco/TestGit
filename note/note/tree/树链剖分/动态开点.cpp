/*
Luogu P3313
每个点有一个颜色c和权值w
1.修改单点c 
2.修改单点w 
3.查询路径上和起始点c相同的所有点的权值的和 
4.查询路径上和起始点c相同的所有点的权值的最大值


每一个颜色都开一个线段树，考虑动态开点 空间复杂度 O((n+m) * logn)
树剖，在颜色c的那颗树上查询/修改 时间复杂度 O(m*logn*logn)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,k,p[N],depth[N],siz[N],son[N];
int l[N],r[N],id[N],tot,top[N];
vector<int> e[N];
int cc[N],w[N];

//动态开点
//root=1
struct node
{
    int ls=0,rs=0;
    int sum,maxv;    
}tr[N*30];//O(mlogn) 尽量开大
int root[N],idx;

void pushup(node &u,node left,node right)
{
    u.sum=left.sum+right.sum;
    u.maxv=max(left.maxv,right.maxv);
}

void pushup(int u)
{
    pushup(tr[u],tr[tr[u].ls],tr[tr[u].rs]);
}


//单点修改
void modify(int &u,int L,int R,int x,int d)
{
    if(!u) u=++idx;
    if(L==R)
    {
        tr[u].sum=tr[u].maxv=d;
        return;
    }
    int mid=L+R-1>>1;
    if(x>mid) modify(tr[u].rs,mid+1,R,x,d);
    else modify(tr[u].ls,L,mid,x,d);
    pushup(u);
}

//区间查询 要保证 l <= r 
node query(int u,int L,int R,int l,int r)
{
    if(!u) return node();
    if(L>=l&&R<=r) return tr[u];
    int mid=L+R-1>>1;
    if(l>mid) return query(tr[u].rs,mid+1,R,l,r);
    else if(r<=mid) return query(tr[u].ls,L,mid,l,r);
    node res;
    node left=query(tr[u].ls,L,mid,l,r);
    node right=query(tr[u].rs,mid+1,R,l,r);
    pushup(res,left,right);
    return res;
}

void dfs(int u,int fa)
{
    siz[u]=1;
    p[u]=fa;
    depth[u]=depth[fa]+1;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}

void dfs2(int u,int fa,int t)
{
    top[u]=t;
    l[u]=++tot;
    id[tot]=u;
    if(son[u]) dfs2(son[u],u,t);
    for(auto v : e[u])
    {
        if(v==fa||v==son[u]) continue;
        dfs2(v,u,v);
    }
    r[u]=tot;
}

node query(int u,int v,int c)
{
    node res={0,0,0,0};
    while(top[u]!=top[v])
    {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        pushup(res,query(root[c],1,n,l[top[u]],l[u]),res);
        u=p[top[u]];
    }
    if(depth[u]<depth[v]) swap(u,v);
    pushup(res,query(root[c],1,n,l[v],l[u]),res);
    return res;
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d%d",w+i,cc+i);
    for(int i=1;i<N;i++) root[i]=++idx;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(1,0);
    dfs2(1,0,1);
    for(int i=1;i<=n;i++) modify(root[cc[i]],1,n,l[i],w[i]);

    while(m--)
    {
        char op[4];
        int a,b;
        scanf("%s%d%d",op,&a,&b);
        if(!strcmp(op,"QS")) printf("%d\n",query(a,b,cc[a]).sum);
        else if(!strcmp(op,"QM")) printf("%d\n",query(a,b,cc[a]).maxv);
        else if(!strcmp(op,"CW")) modify(root[cc[a]],1,n,l[a],b),w[a]=b;
        else
        {
            modify(root[cc[a]],1,n,l[a],0);
            cc[a]=b;
            modify(root[cc[a]],1,n,l[a],w[a]);
        }
    }
}

int main()
{
    int _=1;
    while(_--) solve();
    return 0;
}