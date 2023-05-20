/*
https://ac.nowcoder.com/acm/contest/1084/B
求区间不同数的和，即出现多次的只算一次

枚举 r，考虑维护ans[l],表示[l,r]的答案
每次增加一个a[r],假设a[r]上一次出现的位置是p
那么ans[1]-ans[p]的答案不变，ans[p+1]-ans[r]的答案增加a[r]
因此区间加，单点查询，树状数组即可
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,a[N];
int cnt[N];
vector<pii> query[N];
ll ans[N],tr[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

ll sum(int x)
{
    ll res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        a[i]=x;
    }
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        query[r].push_back({l,i});
    }
    
    for(int r=1;r<=n;r++)
    {
        add(cnt[a[r]]+1,a[r]);
        add(r+1,-a[r]);
        cnt[a[r]]=r;
        for(auto x : query[r])
        {
            int l=x.first,id=x.second;
            ans[id]=sum(l);
        }
    }

    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}

int main()
{
    solve();
    return 0;
}