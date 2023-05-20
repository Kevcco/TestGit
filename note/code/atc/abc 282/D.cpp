/*
给定n个点m条边的无向图   n,m<=2e5
若给两点之间再加一条边，使得图是二分图，则满足要求
询问满足要求的边的个数



考虑染色法先染色，若本来就不是二分图，输出0
图有可能不是连通的，有若干连通块
朴素做法是遍历所有点对(i,j) ,i<j,若不在同一个连通块(并查集)，cnt++，若在同一连通块，若颜色不同，cnt++
最后 cnt-m

先考虑连通块内部加边：整个连通块是二分图，分成a个黑，b个白，加边只能在黑与白之间加边，因此边数a*b

再考虑连通块之间；对某个连通块而言，任意一点与其他连通块的任意一点都可加边，因此边数cnt*(n-cnt)

各连通块相加之后，连通块之间的边数重复加了，需要/2，并且本来有m条边，需要-m

*/



#include <iostream>
#include <cstring>
#include <algorithm>
#pragma GCC optimize(2)

using namespace std;

typedef long long ll;

const int N=2e5+10;

int h[N],e[2*N],ne[2*N],idx,n,m,cnt1,cnt2;
int c[N];
ll ans;

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

bool dfs(int u,int x)
{
    c[u]=x;
    if(x==1) cnt1++;
    else cnt2++;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(!c[j])
        {
            if(!dfs(j,3-x)) return false;
        }
        else
        {
            if(c[j]==x) return false;
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    memset(h,-1,sizeof h);
    for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }
    
    bool flag=true;
    for(int i=1;i<=n;i++)
    {
        if(!c[i])
        {
            cnt1=0,cnt2=0;
            if(!dfs(i,1))
            {
                flag=false;
                break;
            }
            else
            {
                ans+=(ll)cnt1*cnt2*2;
                ans+=(ll)(cnt1+cnt2)*(n-cnt1-cnt2);
            }
        }
    }
    
    if(!flag) printf("0");
    else printf("%lld",ans/2-m);

    
    return 0;
}