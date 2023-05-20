
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e4+10;

int n,m,k,cnt[N],a[N];
int len;
ll ans[N],res;
struct q
{
    int id,l,r;
}Q[N];

bool cmp(q &a,q &b)
{
    if(a.l/len!=b.l/len) return a.l<b.l;
    if(a.l/len&1) return a.r>b.r;
    return a.r<b.r;
}

void add(int x)
{
    res-=(ll)cnt[x]*cnt[x];
    cnt[x]++;
    res+=(ll)cnt[x]*cnt[x];
}

void dele(int x)
{
    res-=(ll)cnt[x]*cnt[x];
    cnt[x]--;
    res+=(ll)cnt[x]*cnt[x];
}

int main()
{
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=0;i<m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        Q[i]={i,l,r};
    }

    len=max(1,(int)sqrt((double)n*n/m));

    sort(Q,Q+m,cmp);

    int i=0,j=1;
    for(int k=0;k<m;k++)
    {
        int l=Q[k].l,r=Q[k].r;
        while(i<r) add(a[++i]);
        while(j>l) add(a[--j]);
        while(i>r) dele(a[i--]);
        while(j<l) dele(a[j++]);
        ans[Q[k].id]=res;
    }

    for(int i=0;i<m;i++) printf("%lld\n",ans[i]);

    return 0;
}