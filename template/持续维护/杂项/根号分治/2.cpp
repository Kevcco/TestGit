
/*
1.给一个n点m边的图，每个点初始为白色 q 个询问 有两种类型  n <= 2e5  m,q <= 4e5
1.将一个点变色 即白变黑 黑变白
2.查询一个点邻接有多少个黑点

n个点 按照度的不同 分成两类 deg > sqrt(n) 的称为大点 个数不超过 sqrt(n) 个
deg < sqrt(n) 的称为小点
考虑查询 : 如果是 小点 那么可以直接暴力统计  
如果是大点 那么不能暴力统计了 可以修改时维护大点的答案 O(sqrt(n))
考虑修改 : 要维护大点的答案 所以将这个点所有邻接的大点的答案都修改一下 O(sqrt(n)) 
当然每个点周围的大点需要先预处理 O(m)


2.给定无向图 n个点 m条边 求三元环的个数
根号分治
按 点的度 重新建边 任意一条边 点度小的指向点度大的 点度相同的，编号小的指向编号大的 变成新图
不难知道新图是有向无环的
点度小的指向点度大的 保证了 新图 任意一个点的出度 <= sqrt(m)

而原图中的任意三元环 i-j-k  i<j<k 在新图中一定会以 i->j j->k i->k 出现
因此第一层循环点 i 第二层循环出边 对应的点j 第三层循环点j的出边 对应点k 判断i是否指向k (预处理)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=1e5+10,M=2*N;

int n,m,k;
int h[N],e[M],ne[M],d[N],in[N],idx;
pair<int,int> edge[M];

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void solve()
{
    cin >> n >> m;;
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        d[u]++,d[v]++;
        edge[i]={u,v};
    }

    for(int i=1;i<=n;i++) h[i]=-1;
    for(int i=0;i<m;i++)
    {
        int u=edge[i].first,v=edge[i].second;
        if(d[u]>d[v]) swap(u,v);
        else if(d[u]==d[v])
            if(u>v) swap(u,v);
        add(u,v);
    }

    ll res=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=h[i];~j;j=ne[j]) in[e[j]]=i;
        for(int j=h[i];~j;j=ne[j])
        {
            int u=e[j];
            for(int k=h[u];~k;k=ne[k])
                if(in[e[k]]==i) res++;
        }
    }

    cout << res;
}

int main()
{
    solve();
    return 0;
}