/*
给你一颗有n个点的树 n<=1e5 每个点都有权重
给你 q <=1e5 次询问 每次询问 给出两个深度相同的点
让你求 f(x,y)的值
f(x,y)是递归定义
ans=0
while(x>0&&y>0)
{
    ans+=w[x]*w[y];
    x=p[x],y=p[y];
}


根号分治
假设深度为i的节点有si个 那么这一层的状态有 si*si个
那么总的状态有sum (si*si) 个  又sum(si) = n 
总共要查询的状态 = sum( min( q , si*si ) );
估计上界 <= n * sqrt(n) 个

因此记忆化理论上可以通过 但是 使用map来记忆化 会有常数 而使用hash有可能被hack
因此使用数组来存 但是直接开 mp[N][N] 太大了

考虑根号分治 即 
若这一层 si >= sqrt(n) 那么 不记忆化 直接暴力求
由于满足 si >= sqrt(n) 的层数  <=sqrt(n) 因此暴力做的这部分复杂度不超过 O(n * sqrt(n))

若这一层 si < sqrt(n) 记忆化：给这一层的节点编号 1 - k  k不超过 sqrt(n) 因此这样就可以开 mp[N][sqrt(N)]
查询 f(x y) 即 mp[x][id[y]] 而mp的状态个数也是 n * sqrt(n)



*/

#include <bits/stdc++.h>

#define YES puts("YES")
#define Yes puts("Yes")
#define NO puts("NO")
#define No puts("No")

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,k;
int p[N],w[N];
int h[N],e[N*2],ne[N*2],idx;
int depth[N],s[N],id[N];
ll mp[N][300];

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void pre(int u,int d)
{
    depth[u]=d;
    s[d]++;
    id[u]=s[d];
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        pre(j,d+1);
    }

}

ll dfs(int x,int y)
{
    if(!x) return 0;
    if(x>y) swap(x,y);
    if(s[depth[x]]<300&&mp[x][id[y]]) return mp[x][id[y]];

    ll res=(ll)w[x]*w[y]+dfs(p[x],p[y]);
    if(s[depth[x]]<300) mp[x][id[y]]=res;
    return res;
}


void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d",w+i),h[i]=-1;
    for(int i=2;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        p[i]=x;
        add(x,i);
    }
    pre(1,1);
    while(m--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ll res=dfs(x,y);
        printf("%lld\n",res);
    }
}

int main()
{
    solve();
    return 0;
}