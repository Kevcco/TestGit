/*
给出一棵以 1 为根的树 判断这棵树是否对称
对称 ： 若有偶数个子树 则要求两两同构
        若有奇数个 可以有一个在中间 其他的两两同构 在中间的必须自己也对称



树哈希 + 异或
判断是否对称：将所有子树的hash值异或起来 如果为0 一定对称
             如果不为0 枚举放在中间那棵子树 
             如果 sum ^ 子树hash值 ==0 且子树本身也对称 那么整棵树就可以对称
*/



#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

ull hh[N];
int n,h[N],e[N*2],ne[N*2],idx;
bool f[N];

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dfs(int u,int fa)
{
    hh[u]=1;
    ull sum=0;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        dfs(j,u);
        hh[u]+=shift(hh[j]);
        sum^=shift(hh[j]);
    }

    if(!sum) f[u]=1;
    else
    {
        for(int i=h[u];~i;i=ne[i])
        {
            int j=e[i];
            if(j==fa) continue;
            if(sum==shift(hh[j])&&f[j])
            {
                f[u]=1;
                break;
            }
        }
    }
}

void solve()
{
    idx=0;
    cin >> n;
    for(int i=1;i<=n;i++) h[i]=-1,f[i]=0;
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }

    dfs(1,0);

    if(f[1]) puts("YES");
    else puts("NO");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}