/*
特殊的图论
一条边a,b,c, a->b,权为c,b->a,权为-c
给定n个点m条边，q个询问，问x，y之间的最长路，如果不通输出nan，如果无穷大输出inf


1.连通性用并查集
2.思考任意两点间的路径，如果a->b有两条路径，且这两条路径权重不一样，则必定存在正环
    反之，不存在正环，走哪条路径都是一样权重，因此求最长路直接随便找一点dfs，如果发现两次到达同一点的路径不一样
    记录一下表示连通块中有正环，这一连通块中任意两点都是inf
    否则最长路就是d[y],初始时随便找一点d[i]=0,然后dfs
    x->y的最长路就是d[y]-d[x]；

*/


#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N=1e5+10;

int h[N],e[2*N],ne[2*N],w[2*N],p[N],n,m,q,idx;
bool st[N],state[N];

ll d[N];

void add(int a,int b,int c)
{
    e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}

int find(int u)
{
    if(p[u]!=u) p[u]=find(p[u]);
    return p[u];
}

void dfs(int u)
{
    state[u]=true;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i],c=w[i];
        if(state[j])
        {
            if(d[j]!=d[u]+c)
            {
                st[find(u)]=true;
                return;
            }
        }
        else
        {
            d[j]=d[u]+c;
            dfs(j);
        }
    }
    return;
}

int main()
{
    cin >> n >> m >> q;
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c),add(b,a,-c);
        p[find(a)]=find(b);
    }
    
    for(int i=1;i<=n;i++)
    {
        if(find(i)==i)
        {
            dfs(i);
        }
    }
    
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int a=find(x),b=find(y);
        if(a!=b) puts("nan");
        else if(st[a]) puts("inf");
        else printf("%lld\n",d[y]-d[x]);
    }
    
    return 0;
}
