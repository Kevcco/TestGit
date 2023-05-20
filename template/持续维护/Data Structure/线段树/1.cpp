
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
struct node
{

}tr[N*4];

void pushup(node &u,node &l,node &r)
{

}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{

}

void build(int u,int L,int R)
{
    if(L==R)
    {

        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

//区间修改
void modify(int u,int L,int R,int l,int r,int d)
{
    if(L>=l&&R<=r)
    {

        return;
    }
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r,d);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r,d);
    pushup(u);
}

//单点修改
void modify(int u,int L,int R,int x,int d)
{
    if(L==R)
    {

        return;
    }
    int mid=L+R>>1;
    if(x<=mid) modify(u<<1,L,mid,x,d);
    else modify(u<<1|1,mid+1,R,x,d);
    pushup(u);
}

node query(int u,int L,int R,int l,int r)
{
    if(L>=l&&R<=r) return tr[u];
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l>mid) return query(u<<1|1,mid+1,R,l,r);
    else if(r<=mid) return query(u<<1,L,mid,l,r);
    node res;
    node ls=query(u<<1,L,mid,l,r);
    node rs=query(u<<1|1,mid+1,R,l,r);
    pushup(res,ls,rs);
    return res;
}