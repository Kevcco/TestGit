
// 求无根树是否同构 : hash + 换根
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int mod=1e9+7,N=110;

const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

ull hh[N],res;
int n,m,k;
map<ull,int> mp;
vector<int> e[N];

// 求以u为根的树的hash值
void dfs(int u)
{
    hh[u]=1;
    for(auto v : e[u])
    {
        dfs(v);
        hh[u]+=shift(hh[v]);
    }
}

//换根
void dp(int u)
{
    res=min(res,hh[u]);
    for(auto v : e[u])
    {
        hh[v]+=shift(hh[u]-shift(hh[v]));
        dp(v);
    }
}

void solve()
{
    cin >> m;
    for(int t=1;t<=m;t++)
    {
        cin >> n;
        for(int i=1;i<=n;i++) e[i].clear();
        int root=-1;
        for(int i=1;i<=n;i++)
        {
            int b;
            scanf("%d",&b);
            if(b) e[b].push_back(i);
            else root=i;
        }
        res=18446744073709551615ull;
        dfs(root);
        dp(root);
        if(!mp.count(res)) mp[res]=t;
        printf("%d\n",mp[res]);
    }
}

int main()
{
    solve();
    return 0;
}