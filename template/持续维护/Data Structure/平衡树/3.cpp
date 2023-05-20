
#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=1e5+10;

int n,m,idx,root;
struct node
{
    int l,r;
    int tag;
    int key,val;
    int size;
}tr[N];

int get_node(int key)
{
    tr[++idx].key=key;
    tr[idx].val=rand();
    tr[idx].size=1;
    return idx;
}

void pushup(int p)
{
    tr[p].size=tr[tr[p].l].size+tr[tr[p].r].size+1;
}

void pushdown(int p)
{
    if(!tr[p].tag) return;
    swap(tr[p].l,tr[p].r);
    if(tr[p].l) tr[tr[p].l].tag^=1;
    if(tr[p].r) tr[tr[p].r].tag^=1;
    tr[p].tag=0;
}

void split_by_key(int p,int key,int &x,int &y)
{
    if(!p) x=y=0;
    else
    {
        if(tr[p].key<=key) x=p,split_by_key(tr[p].r,key,tr[x].r,y);
        else y=p,split_by_key(tr[p].l,key,x,tr[y].l);
        pushup(p);
    }
}

void split(int p,int k,int &x,int &y)
{
    if(!p) x=y=0;
    else
    {
        pushdown(p);
        if(tr[tr[p].l].size+1<=k)
        {
            x=p;
            split(tr[p].r,k-tr[tr[p].l].size-1,tr[x].r,y);
        }
        else
        {
            y=p;
            split(tr[p].l,k,x,tr[y].l);
        }
        pushup(p);
    }
}

int merge(int x,int y)
{
    if(!x||!y) return x+y;
    pushdown(x),pushdown(y);
    int res;
    if(tr[x].val>tr[y].val)
    {
        res=x;
        tr[x].r=merge(tr[x].r,y);
    }
    else
    {
        res=y;
        tr[y].l=merge(x,tr[y].l);
    }
    pushup(res);
    return res;
}

// 区间翻转
void rever(int l,int r)
{
    int x,y,z;
    split(root,r,y,z);
    split(y,l-1,x,y);
    tr[y].tag^=1;
    root=merge(merge(x,y),z);
}

void insert(int &p,int key)
{
    int x,y;
    split_by_key(p,key,x,y);
    int new_node=get_node(key);
    p=merge(merge(x,new_node),y);
}

void print(int p)
{
    if(!p) return;
    pushdown(p);
    print(tr[p].l);
    printf("%d ",tr[p].key);
    print(tr[p].r);
}


void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) insert(root,i);
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        rever(l,r);
    }
    print(root);
}

int main()
{
    solve();
    return 0;
}