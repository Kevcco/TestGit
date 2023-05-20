//动态开点 root=1

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
struct node
{
    int ls,rs;
    
}tr[N];//O(mlogn) 尽量开大
int root=1,id=1;

void pushup(node &u,node &left,node &right)
{
    
}

void pushup(int u)
{
    pushup(tr[u],tr[tr[u].ls],tr[tr[u].rs]);
}

void pushdown(int u,int L,int R)
{
    if(!tr[u].tag) return;
    if(!tr[u].ls) tr[u].ls=++id;
    if(!tr[u).rs) tr[u].rs=++id;
    
}

//区间修改
void modify(int &u,int L,int R,int l,int r,int d)
{
    if(!u) u=++id;
    if(L>=l&&R<=r)
    {
        
        return;
    }
    pushdown(u,L,R);
    int mid=L+R-1>>1;
    if(l<=mid) modify(tr[u].ls,L,mid,l,r,d);
    if(r>mid) modify(tr[u].rs,mid+1,R,l,r,d);
    pushup(u);
}

//单点修改
void modify(int &u,int L,int R,int x,int d)
{
    if(!u) u=++id;
    if(L==R)
    {

        return;
    }
    int mid=L+R-1>>1;
    if(x>mid) modify(tr[u].rs,mid+1,R,x,d);
    else modify(tr[u].ls,L,mid,x,d);
    pushup(u);
}

//区间查询 要保证 l <= r 
node query(int u,int L,int R,int l,int r)
{
    if(!u) return node();
    if(L>=l&&R<=r) return tr[u];
    pushdown(u,L,R);
    int mid=L+R-1>>1;
    if(l>mid) return query(tr[u].rs,mid+1,R,l,r);
    else if(r<=mid) return query(tr[u].ls,L,mid,l,r);
    node res;
    node left=query(tr[u].ls,L,mid,l,r);
    node right=query(tr[u].rs,mid+1,R,l,r);
    pushup(res,left,right);
    return res;
}