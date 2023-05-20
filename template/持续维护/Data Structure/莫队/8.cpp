
// 二次离线
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+10;

int n,m,k,a[N],len;
vector<int> nums;
ll f[N],g[N],ans[N];
struct q
{
    int l,r,id;
    ll res;
}query[N];
struct node
{
    int l,r,id,t;
};
vector<node> range[N];

bool cmp(q &a,q &b)
{
    if(a.l/len!=b.l/len) return a.l<b.l;
    if(a.l/len&1) return a.r>b.r;
    return a.r<b.r;
}

int main()
{
    cin >> n >> m >> k;
    len=(int)sqrt((double)n*n/m)+1;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=0;i<(1<<14);i++)
        if(__builtin_popcount(i)==k)
            nums.push_back(i);
            
    for(int i=1;i<=n;i++)
    {
        for(auto x : nums) g[a[i]^x]++;
        f[i]=g[a[i+1]];
    }
    
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        query[i]={l,r,i};
    }
    
    sort(query+1,query+m+1,cmp);
    
    for(int i=1,L=1,R=0;i<=m;i++)
    {
        int l=query[i].l,r=query[i].r;
        if(R<r) range[L-1].push_back({R+1,r,i,-1});
        while(R<r) query[i].res+=f[R++];
        if(R>r) range[L-1].push_back({r+1,R,i,1});
        while(R>r) query[i].res-=f[--R];
        if(L<l) range[R].push_back({L,l-1,i,-1});
        while(L<l) query[i].res+=f[L-1]+!k,L++;
        if(L>l) range[R].push_back({l,L-1,i,1});
        while(L>l) query[i].res-=f[L-2]+!k,L--;
    }

    
    memset(g,0,sizeof g);
    for(int i=1;i<=n;i++)
    {
        for(auto x : nums) g[a[i]^x]++;
        for(auto &q : range[i])
        {
            int l=q.l,r=q.r,id=q.id,t=q.t;
            for(int x=l;x<=r;x++)
                query[id].res+=g[a[x]]*t;
        }
    }
    
    for(int i=2;i<=m;i++) query[i].res+=query[i-1].res;
    for(int i=1;i<=m;i++) ans[query[i].id]=query[i].res;
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    
    return 0;
}