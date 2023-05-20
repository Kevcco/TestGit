/*

一. 倍增求LCA (无修改)
(1) 预处理depth 和 祖先节点 O(nlogn) 询问两点LCA O(logn)
(2) 可以求某个点的第k个祖先
(3) 可以求两点的路径信息：路径上边权/点权的最值


二. 欧拉序求LCA
(1) 欧拉序，对两个点u,v 他们的lca一定是区间 pos[u] - pos[v] 中深度最小的那个点
    所以转化为RMQ问题 st表解决 空间 2*n 预处理 O(n*logn) 查询 O(1)
    注意一定要开二倍空间
(2) 欧拉序区间内并不是简单路径，有重复和其他多余信息，所以并不能解决求路径信息的问题，只能求LCA


三. Tarjan求LCA (离线算法)
(1) 将所有询问存下来，然后在一次dfs中处理所有询问 
    具体而言 并查集初始化 p[i]=i
    对于某一节点 先将其标记为已访问 然后递归处理所有儿子 处理完每一个儿子后，都将儿子指向自己
    最后处理当前节点u的询问：如果询问的另一个节点v已访问过，那么这次询问的答案就是find(p[v]) 
    时间复杂度：O(n + m)  (并查集的常数)
(2) Tarjan也可以求路径信息，和求LCA一样 不过求得LCA(u,v)之后并不能立即处理，
    而是将他存到LCA处，回溯到LCA时再最后处理，因为当前的u并没有连LCA，路径信息并不是正确的
    只有到最后处理完LCA的u所在的分支，将儿子指向自己后，才能正确计算 

    例题：https://vjudge.csgrandeur.cn/problem/SPOJ-DISQUERY


感性理解：在dfs过程中 每次dfs到某一点，相当于要处理以这一点为lca的所有询问
         先置st[u]=1 因为会有某个询问是(x,u) 
         然后先递归处理子树，不要改变子树的任何信息，递归完某一子树后，相当于这棵子树内部的询问处理完了
         将这棵子树信息合并到 u，再递归其他儿子时，就可以处理子树间的询问了，当然只有先访问到的那个点的信息
         是到LCA的信息，另一个点的信息并不是，所有不能直接就处理路径信息，而是传给LCA，等LCA将所有儿子处理完
         并将儿子信息合并后，此时都是正确的信息，再统一求得路径信息
         这是一个自深节点到浅节点的过程
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,root;
int h[N],e[N*2],ne[N*2],idx;

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

// 倍增求LCA
int p[N][20],d[N];
void dfs(int u,int fa)
{
    p[u][0]=fa;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        d[j]=d[u]+1;
        dfs(j,u);
    }
}

void solve()
{
    cin >> n >> m >> root;
    memset(h,-1,sizeof h);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
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
        if(a==b)
        {
            printf("%d\n",a);
            continue;
        }
        for(int j=19;j>=0;j--)
            if(p[a][j]!=p[b][j]) a=p[a][j],b=p[b][j];

        printf("%d\n",p[a][0]);
    }
}

//欧拉序求LCA
int depth[N],pos[N],tot;
pii id[N*2],f[21][N*2];
 
void dfs2(int u,int fa)
{
    depth[u]=depth[fa]+1;
    pos[u]=++tot;
    id[tot]={depth[u],u};
    f[0][tot]=id[tot];
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        dfs(j,u);
        id[++tot]={depth[u],u};
        f[0][tot]=id[tot];
    }
}

void solve2()
{
    cin >> n >> m >> root;
    for(int i=1;i<=n;i++) h[i]=-1;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }

    dfs2(root,0);
    for(int j=1;j<=20;j++)
        for(int i=1;i+(1<<j)-1<=tot;i++)
            f[j][i]=min(f[j-1][i],f[j-1][i+(1<<j-1)]);
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(pos[a]>pos[b]) swap(a,b);
        int k=31-__builtin_clz(pos[b]-pos[a]+1);
        printf("%d\n",min(f[k][pos[a]],f[k][pos[b]-(1<<k)+1]).second);
    }

}

int main()
{
    solve();
    return 0;
}
