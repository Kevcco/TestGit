/*
启发式合并: 合并集合时 将小集合合并到大集合 对于任一元素 被移动次数不超过 logn 故总时间 O(nlogn)
abc 279 F

DSU on tree: 解决统计子树信息的问题
计算某一节点时 保留重儿子的信息 再暴力枚举其他轻儿子的信息合并 与重儿子合并
每个节点被重复算的次数不超过 logn 故总时间 O(nlogn)

具体写法: 先预处理 dfs序 重儿子 
然后 dfs 先dfs轻儿子 再dfs重儿子(重儿子的信息保留) 然后按dfs序把其他所有节点全部加入重儿子的信息 
得到这个节点的完整信息 最后判断要不要清空这个节点的信息

Luogu U41492
cf 600 E
2020 ccpc changchun F


*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

const int N=1e5+10;

int n,c[N],h[N],e[N*2],ne[N*2],idx;
int son[N],siz[N],cnt[N];
int l[N],r[N],id[N],tot;
ll ans[N],sum,maxv;

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dfs(int u,int fa)
{
    l[u]=++tot;
    id[tot]=u;
    siz[u]=1;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        dfs(j,u);
        siz[u]+=siz[j];
        if(siz[j]>siz[son[u]]) son[u]=j;
    }
    r[u]=tot;
}

void dfs2(int u,int fa,bool keep)
{
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa||j==son[u]) continue;
        dfs2(j,u,0);
    }

    if(son[u]) dfs2(son[u],u,1);

    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
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
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }
    
    dfs(1,0);
    dfs2(1,0,1);
    
    for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
    
    return 0;
}