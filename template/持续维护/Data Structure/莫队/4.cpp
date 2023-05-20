
// 只加不删的莫队 ： 求区间 a[i]*cnt[a[i]]的最大值
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+10;

int n,m,len,a[N],cnt[N];
ll ans[N];
struct q
{
    int id,l,r;
}Q[N];
vector<int> num;

bool cmp(q &a,q &b)
{
    if(a.l/len!=b.l/len) return a.l<b.l;
    return a.r<b.r;
}

int main()
{
    cin >> n >> m;
    len=(int)sqrt((double)n*n/m)+1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        num.push_back(a[i]);
    }
    
    sort(num.begin(),num.end());
    num.erase(unique(num.begin(),num.end()),num.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(num.begin(),num.end(),a[i])-num.begin();
    
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        Q[i]={i,l,r};
    }
    
    sort(Q+1,Q+m+1,cmp);
    
    for(int k=1;k<=m;)
    {
        int p=k;
        while(p<=m&&Q[p].l/len==Q[k].l/len) p++;
        int right=Q[k].l/len*len+len-1;
        
        while(k<p&&Q[k].r<=right)
        {
            ll res=0;
            int l=Q[k].l,r=Q[k].r;
            for(int i=l;i<=r;i++)
            {
                cnt[a[i]]++;
                res=max(res,(ll)cnt[a[i]]*num[a[i]]);
            }
            ans[Q[k].id]=res;
            for(int i=l;i<=r;i++) cnt[a[i]]--;
            k++;
        }
        
        ll res=0;
        int j=right;
        while(k<p)
        {
            int l=Q[k].l,r=Q[k].r;
            while(j<r)
            {
                ++j;
                cnt[a[j]]++;
                res=max(res,(ll)cnt[a[j]]*num[a[j]]);
            }
            ll backup=res;
            for(int i=right;i>=l;i--)
            {
                cnt[a[i]]++;
                res=max(res,(ll)cnt[a[i]]*num[a[i]]);
            }
            ans[Q[k].id]=res;
            res=backup;
            for(int i=l;i<=right;i++) cnt[a[i]]--;
            k++;
        }
        
        memset(cnt,0,sizeof cnt);
    }
    
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    
    return 0;
}