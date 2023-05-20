/*
特定条件二分: 给定n个点 每个点有一个花费 bi = ai + min(i,n+1-i) 
             有m元钱  要求包含至少一个点 其花费为 i+ai 求最多能包含几个点

排序+前缀和  枚举 ai+i  m -= ai+i
二分前缀和s[] 找到最多包含的点的下标 x 
如果发现 bx < bi  代表前x个点不包含第i个点 没有重复使用第i个点  res=max(res,x+1)
else bx >= bi 有可能重复使用 那么我们让 m += bi(相当于跳过bi) 重新二分 找到 x 那么 res=max(res,x-1+1);
甚至不用重新二分 因为结果要么是x 要么是x+1 只需要验证 b[x+1] 能否在跳过bi的前提下被包含即可



*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int a[N],p[N];
ll s[N];

void solve()
{
    cin >> n >> m;

    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        p[i]=a[i]+min(i,n+1-i);
    }

    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) s[i]=s[i-1]+p[i];

    int res=0;
    for(int i=1;i<=n;i++)
    {
        int t=m-a[i]-i;
        if(t<0) continue;
        k=a[i]+min(i,n+1-i);
        int x=upper_bound(s+1,s+1+n,t)-s-1;
        if(k>p[x]) res=max(res,x+1);
        else
        {
            if(x<n&&p[x+1]==k) x++;
            res=max(res,x-1);
            // 重新二分
            //t+=k;
            //x=upper_bound(s+1,s+n+1,t)-s-1;
            //res=max(res,x);
        }
    }
    
    printf("%d\n",res);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}