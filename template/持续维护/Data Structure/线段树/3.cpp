//势能线段树 区间开根

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
ll p[N];
struct node
{
    ll sum,v;
}tr[N*4];

void pushup(node &u,node &l,node &r)
{
    u.sum=l.sum+r.sum;
    u.v=max(l.v,r.v);
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u].sum=p[L];
        tr[u].v=p[L];
        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

void modify(int u,int L,int R,int l,int r)
{
    if(tr[u].v<=1) return;
    if(L==R)
    {
        tr[u].sum=sqrt(tr[u].sum);
        tr[u].v=tr[u].sum;
        return;
    }
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r);
    pushup(u);
}

ll query(int u,int L,int R,int l,int r)
{
    if(L>=l&&R<=r) return tr[u].sum;
    int mid=L+R>>1;
    ll res=0;
    if(l<=mid) res+=query(u<<1,L,mid,l,r);
    if(r>mid) res+=query(u<<1|1,mid+1,R,l,r);
    return res;
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) scanf("%lld",p+i);
    build(1,1,n);
    while(m--)
    {
        int k,l,r;
        scanf("%d%d%d",&k,&l,&r);
        if(l>r) swap(l,r);
        if(k==2) printf("%lld\n",query(1,1,n,l,r));
        else modify(1,1,n,l,r);
    }
}

int main()
{
    solve();
    return 0;
}