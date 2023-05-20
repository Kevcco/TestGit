/*
给定一个长n的排列 给出m对下标元素的相对大小 询问能否确定这个排列 
如果能 输出排列



拓扑排序 
如果能确定这个排列 给定的大小关系形成的图的拓扑序一定唯一
如果发现有多个入度为0的点或者排序过程中有多个点同时入队 则不唯一
注意n个点不一定连通 如果不连通一定不唯一
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

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int h[N],e[N*2],ne[N*2],d[N],res[N],idx;
map<pii,int> hh;

void add(int a,int b)
{
    d[b]++,e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) h[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(hh.count({a,b})) continue;
        add(a,b);
        hh[{a,b}]=1;
    }

    int ans=1;
    queue<int> q;
    for(int i=1;i<=n;i++)
    {
        if(!d[i])
        {
            if(!q.empty()) { No; return;}
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        res[t]=ans++;
        for(int i=h[t];~i;i=ne[i])
        {
            int j=e[i];
            d[j]--;
            if(!d[j])
            {
                if(!q.empty()) { No; return;}
                q.push(j);
            }
        }
    }

    if(ans<=n) { No; return;}
    Yes;
    for(int i=1;i<=n;i++) printf("%d ",res[i]);
}

int main()
{
    solve();
    return 0;
}
