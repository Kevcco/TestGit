
// 莫队 + 分块 ： 统计区间中在[a,b]值域内数的个数和不重复的数的个数

#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,len;
int a[N],cnt[N],sum1[N],sum2[N];
pii ans[N];
struct q
{
    int id,l,r,a,b;
}Q[N];

bool cmp(q &A,q &B)
{
    if(A.l/len!=B.l/len) return A.l<B.l;
    if(A.l/len&1) return A.r>B.r;
    return A.r<B.r;
}

void add(int x)
{
    sum1[x/len]++;
    if(!cnt[x]) sum2[x/len]++;
    cnt[x]++;
}

void del(int x)
{
    sum1[x/len]--;
    cnt[x]--;
    if(!cnt[x]) sum2[x/len]--;
}

void query(int l,int r,int id)
{
    int res1=0,res2=0;
    if(l/len==r/len)
    {
        for(int i=l;i<=r;i++)
            res1+=cnt[i],res2+=(cnt[i]>0);
    }
    else
    {
        int i=l,j=r;
        while(i/len==l/len) res1+=cnt[i],res2+=(cnt[i]>0),i++;
        while(j/len==r/len) res1+=cnt[j],res2+=(cnt[j]>0),j--;
        for(int k=i/len;k<=j/len;k++) res1+=sum1[k],res2+=sum2[k];
    }
    ans[id].first=res1,ans[id].second=res2;
}

void solve()
{
    cin >> n >> m;
    len=(int)sqrt((double)n*n/m/2)+1;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++)
    {
        int l,r,a,b;
        scanf("%d%d%d%d",&l,&r,&a,&b);
        Q[i]={i,l,r,a,b};
    }

    sort(Q+1,Q+m+1,cmp);

    for(int k=1,i=0,j=1;k<=m;k++)
    {
        int l=Q[k].l,r=Q[k].r;
        while(i<r) add(a[++i]);
        while(j>l) add(a[--j]);
        while(i>r) del(a[i--]);
        while(j<l) del(a[j++]);
        query(Q[k].a,Q[k].b,Q[k].id);
    }

    for(int i=1;i<=m;i++) printf("%d %d\n",ans[i].first,ans[i].second);
}

int main()
{
    solve();
    return 0;
}