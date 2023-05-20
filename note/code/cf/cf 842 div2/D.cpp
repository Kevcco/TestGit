/*
  置换环
  注意unorder_map被卡
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k,a[N];
map<int,bool> hh;
bool st[N],flag;

void dfs(int u)
{
    st[u]=true;
    hh[u]=true;
    int p=a[u];
    if(hh[p-1]||hh[p+1]) flag=true;
    if(!st[p]) dfs(p);
}

void solve()
{
    cin >> n;
    flag=false;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) st[i]=0;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(!st[i])
        {
            hh.clear();
            cnt++;
            dfs(i);
        }
    }
    if(flag) printf("%d\n",n-cnt-1);
    else printf("%d\n",n-cnt+1);
    
    return;
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    
    return 0;
}
