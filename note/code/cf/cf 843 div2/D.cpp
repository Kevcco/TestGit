/*
给定一个长度为 n <=3e5 的数组 a ,如果 gcd(ai,aj)!=1,则在 i 和 j 之间连一条长1的边
求点s到u的最短距离



辅助点 虚点
建边技巧：建虚点,值为质数,
         实点指向其所有质因子的虚点,且边权为0,
         虚点指向所有能整除他的实点,边权为1
区分实点和虚点：只需要让所有虚点的值+N代表下标，就不会和实点下标冲突
然后01 bfs广搜
边的条数 nlogn  bfs nlogn


*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=3e5+100;

int n,idx,s,u,path[2*N];
int d[2*N],h[2*N],e[20*N],ne[20*N],w[20*N];

void add(int a,int b,int c)
{
    e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}

void solve()
{
    memset(d,-1,sizeof d);
    memset(h,-1,sizeof h);
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        for(int j=2;j*j<=x;j++)
        {
            if(x%j==0)
            {
                add(i,N+j,0);
                add(N+j,i,1);
                while(x%j==0) x/=j;
            }
        }
        if(x>1) add(i,N+x,0),add(N+x,i,1);
    }

    cin >> s >> u;
    if(s==u)
    {
        cout << 1 << "\n" << s << endl;
        return;
    }
    queue<int> q;
    d[s]=0;
    q.push(s);
    while(q.size())
    {
        int t=q.front();
        q.pop();
        for(int i=h[t];~i;i=ne[i])
        {
            int j=e[i],c=w[i];
            if(~d[j]) continue;
            d[j]=d[t]+c;
            path[j]=t;
            q.push(j);
        }
    }
    if(d[u]==-1)
    {
        cout << "-1" << endl;
        return;
    }
    cout << d[u]+1 << endl;
    stack<int> stack;
    while(path[u])
    {
        stack.push(u);
        u=path[u];
    }
    stack.push(s);
    while(stack.size())
    {
        int x=stack.top();
        stack.pop();
        if(x<N) printf("%d ",x);
    }
}

int main()
{
    solve();
    return 0;
}