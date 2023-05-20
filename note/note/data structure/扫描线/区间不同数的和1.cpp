/*
https://ac.nowcoder.com/acm/contest/1084/B
求区间不同数的和，即出现多次的只算一次

预处理(i,pre[i]) pre[i]表示a[i]这个数上一次出现的下标
那么ans[l,r] = sum(a[i]) ，其中 l <= i <= r , pre[i] < l
转化为二维数点
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,a[N];
int cnt[N];
vector<array<int,4>> event;
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
        event.push_back({cnt[x],0,i,0});
        cnt[x]=i;
    }
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        event.push_back({l-1,1,r,i});
        event.push_back({l-1,2,l-1,i});
    }
    sort(event.begin(),event.end());
    
    for(auto x : event)
    {
        if(!x[1]) add(x[2],a[x[2]]);
        else
        {
            int t=sum(x[2]);
            if(x[1]==1) ans[x[3]]+=t;
            else ans[x[3]]-=t;
        }
    }

    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}

int main()
{
    solve();
    return 0;
}