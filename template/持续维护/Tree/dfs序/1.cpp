/*
(1) 单点修改 子树查询 : dfs序相当于单点修改 区间查询 树状数组即可
(2) 子树修改 单点查询 : dfs序相当于区间修改 单点查询 维护序列的差分数组即可
(3) 子树修改  子树查询： dfs序 相当于区间修改 区间查询 维护两个dfs序差分树状数组即可
*/
// (3)
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=1e6+10;

int n,m,root,p[N];
ll tr1[N],tr2[N],res[N];
vector<int> e[N];
int l[N],r[N],tot;


int lowbit(int x)
{
    return x&-x;
}

void add(int x,ll c,ll tr[])
{
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

ll sum(int x,ll tr[])
{
    ll res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

ll prefix(int x)
{
    return (ll)(x+1)*sum(x,tr1)-sum(x,tr2);
}

void dfs(int u,int fa)
{
    l[u]=++tot;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
    }
    r[u]=tot;
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(root,0);

    for(int i=1;i<=n;i++) res[l[i]]=p[i];
    for(int i=n;i>0;i--) res[i]-=res[i-1];
    for(int i=1;i<=n;i++) add(i,res[i],tr1),add(i,res[i]*i,tr2);

    while(m--)
    {
        int opt,a,x;
        scanf("%d%d",&opt,&a);
        if(opt==1)
        {
            scanf("%d",&x);
            add(l[a],x,tr1),add(r[a]+1,-x,tr1);
            add(l[a],(ll)l[a]*x,tr2),add(r[a]+1,-(ll)(r[a]+1)*x,tr2);
        }
        else printf("%lld\n",prefix(r[a])-prefix(l[a]-1));
    }
}

int main()
{
    solve();
    return 0;
}