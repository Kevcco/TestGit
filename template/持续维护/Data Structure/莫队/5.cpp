
// 只删不加 ： 求区间 mex
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+10;

int n,m,len,a[N],cnt[N];
int ans[N];
struct q
{
    int id,l,r;
}Q[N];
vector<int> num;

bool cmp(q &a,q &b)
{
    if(a.l/len!=b.l/len) return a.l<b.l;
    return a.r>b.r;
}

int main()
{
    cin >> n >> m;
    len=(int)sqrt(n)+1;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    
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
        int left=Q[k].l/len*len;
        int right=left+len-1;
        
        while(k<p&&Q[k].r<=right)
        {
            int res=0;
            int l=Q[k].l,r=Q[k].r;
            for(int i=l;i<=r;i++) cnt[a[i]]++;
            while(cnt[res]) res++;
            ans[Q[k].id]=res;
            for(int i=l;i<=r;i++) cnt[a[i]]--;
            k++;
        }
        if(k>=p) continue;
        int res=0;
        int j=Q[k].r;
        for(int i=left;i<=j;i++) cnt[a[i]]++;
        while(cnt[res]) res++;
        while(k<p)
        {
            int l=Q[k].l,r=Q[k].r;
            while(j>r)
            {
                cnt[a[j]]--;
                if(!cnt[a[j]]) res=min(res,a[j]);
                --j;
            }
            int backup=res;
            for(int i=left;i<l;i++)
            {
                cnt[a[i]]--;
                if(!cnt[a[i]]) res=min(res,a[i]);
            }
            ans[Q[k].id]=res;
            res=backup;
            for(int i=left;i<l;i++) cnt[a[i]]++;
            k++;
        }
        
        memset(cnt,0,sizeof cnt);
    }
    
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    
    return 0;
}