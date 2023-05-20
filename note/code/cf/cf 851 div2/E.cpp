/*
给定数组 n <=2e5
要求选择若干个不相交的连续子序列 使得每一个子序列的 和>=0
询问最多能覆盖多少元素



考虑 dp
 dp[i] 如果不选择a[i] dp[i]=dp[i-1]
 如果选择a[i] 那么就是考虑所有的 j 满足 s[j] <= s[i]
 dp[i]= dp[j] + i-j
  O(n^2)
考虑优化 dp[i] = i + dp[j] - j
在所有 s[j] <= s[i] 的 j 中选择 max dp[j] - j
可以权值树状数组/线段树 优化  O(n*logn)
 s[i] 范围太大需要离散化 
注意初始化不能是 0 因为 值是 dp[j] - j 是负数
必须初始化成负无穷 
注意s[0] 要特殊处理  update(find(0),0)
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
ll p[N];
vector<ll> alls;
int tr[N],dp[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=m;i+=lowbit(i)) tr[i]=max(c,tr[i]);
}

int sum(int x)
{
    int res=-1e9;
    for(int i=x;i;i-=lowbit(i)) res=max(res,tr[i]);
    return res;
}

int find(ll x)
{
    int l=0,r=alls.size()-1;
    while(l<r)
    {
        int mid=l+r>>1;
        if(alls[mid]>=x) r=mid;
        else l=mid+1;
    }
    return r+1;
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        p[i]=p[i-1]+x;
        alls.push_back(p[i]);
    }

    alls.push_back(0ll);
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());

    m=alls.size();
    for(int i=1;i<=m;i++) tr[i]=-1e9;
    int t=find(0);
    add(t,0);

    for(int i=1;i<=n;i++)
    {
        t=find(p[i]);
        int x=sum(t);
        dp[i]=max(dp[i-1],x+i);
        add(t,dp[i]-i);
    }
    printf("%d\n",dp[n]);
}

int main()
{
    solve();
    return 0;
}