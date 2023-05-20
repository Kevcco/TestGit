/*
树上差分： 真正的节点值是整棵子树的差分数组值之和
(1)修改路径上的所有点：变成修改单点的信息，修改一点，
   那么这一点到根的路径上的所有点都会修改
(2)求单点点权 ： 子树和
(3)求子树和 ： 推公式 与点的深度有关
具体来说:
(1) 点差分 ：修改 u -> v 的路径上的所有点  --> 修改 u -> lca 和 v -> lca的下面一个节点 两条链
            也就是 d[u]++,d[v]++,d[lca.father]--,d[lca]--;
(2) 边差分 ： 定义某一点代表这个点到其父亲节点的边 那么修改 u -> v 路径上的所有边
            也就是 d[u]++,d[v]--,d[lca]-=2;

维护两个树状数组，一个d[u]
另一个 depth[u]*d[u] 的值
子树u的和 = sum( d[v] * (depth[v] - depth[u] + 1) )
= sum_tr2(l[u],r[u]) - sum_tr1(l[u],r[u]) * (depth[u] - 1)
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m,root,tot,idx;
int depth[N],a[N],pos[N],l[N],r[N],par[N];
int p[22][2*N];
vector<int> e[N];
ll tr1[N],tr2[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,ll c,ll tr[])
{
    if(!x) return;
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

ll sum(int x,ll tr[])
{
    ll res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}


void dfs(int u,int fa)
{
    par[u]=fa;
    l[u]=++idx;
    depth[u]=depth[fa]+1;
    pos[u]=++tot;
    p[0][tot]=u;
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        p[0][++tot]=u;
    }
    r[u]=idx;
}

int lca(int u,int v)
{
    int a=pos[u],b=pos[v];
    if(a>b) swap(a,b);
    int k=31-__builtin_clz(b-a+1);
    if(depth[p[k][a]]<depth[p[k][b-(1<<k)+1]]) return p[k][a];
    else return p[k][b-(1<<k)+1];
}

void add_list(int u,int v,int x)
{
    int w=lca(u,v);
    add(l[u],x,tr1);
    add(l[u],(ll)depth[u]*x,tr2);
    add(l[v],x,tr1);
    add(l[v],(ll)depth[v]*x,tr2);
    add(l[w],-x,tr1);
    add(l[w],(ll)depth[w]*(-x),tr2);
    add(l[par[w]],-x,tr1);
    add(l[par[w]],(ll)depth[par[w]]*(-x),tr2);
}

ll query(int u)
{
   ll sum1=sum(r[u],tr2)-sum(l[u]-1,tr2); 
   ll sum2=sum(r[u],tr1)-sum(l[u]-1,tr1);
   return sum1-sum2*(depth[u]-1);
}

void solve()
{
    cin >> n >> m >> root;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(root,0);

    for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=tot;i++)
            if(depth[p[j-1][i]]<depth[p[j-1][i+(1<<j-1)]]) p[j][i]=p[j-1][i];
            else p[j][i]=p[j-1][i+(1<<j-1)];
    
    for(int i=1;i<=n;i++) add_list(i,i,a[i]);

    while(m--)
    {
        int opt,a,b,x;
        scanf("%d%d",&opt,&a);
        if(opt==1)
        {
            scanf("%d%d",&b,&x);
            add_list(a,b,x);
        }
        else if(opt==2) printf("%lld\n",sum(r[a],tr1)-sum(l[a]-1,tr1));
        else printf("%lld\n",query(a));
    }
}

int main()
{
    solve();
    return 0;
}