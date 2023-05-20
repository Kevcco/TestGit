
//数颜色: 带修 求区间不重复的数的个数
#include <bits/stdc++.h>

using namespace std;

const int N=14e4+10,s=1e6+10;

int n,m,tot,qot,len;
int cnt[s],a[N],res,ans[N];
struct q
{
    int id,l,r,t;
}Q[N];

struct modify
{
    int x,y;
}M[N];

bool cmp(q &a,q &b)
{
    if(a.l/len!=b.l/len) return a.l<b.l;
    if(a.r/len!=b.r/len) return a.r<b.r;
    if(a.r/len&1)return a.t>b.t;
    return a.t<b.t;
}

inline void add(int x)
{
    if(!cnt[x]) res++;
    cnt[x]++;
}

inline void del(int x)
{
    cnt[x]--;
    if(!cnt[x]) res--;
}

inline void changet(int l,int r,int t)
{
    int x=M[t].x,y=M[t].y;
    if(x>=l&&x<=r) add(y),del(a[x]);
    M[t].y=a[x],a[x]=y;
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++)
    {
        char str[2];
        int x,y;
        scanf("%s%d%d",str,&x,&y);
        if(*str=='R')
        {
            ++tot;
            M[tot]={x,y};
        }
        else qot++,Q[qot]={qot,x,y,tot};
    }
    
    len=cbrt((double)n*n*max(1,tot)/qot)+1;
    sort(Q+1,Q+qot+1,cmp);
    
    for(int k=1,i=1,j=0,tt=0;k<=qot;k++)
    {
        int l=Q[k].l,r=Q[k].r,t=Q[k].t;
        while(j<r) add(a[++j]);
        while(i>l) add(a[--i]);
        while(j>r) del(a[j--]);
        while(i<l) del(a[i++]);
        while(tt<t) changet(i,j,++tt);
        while(tt>t) changet(i,j,tt--);
        ans[Q[k].id]=res;
    }
    
    for(int i=1;i<=qot;i++) printf("%d\n",ans[i]);
    
    return 0;
}