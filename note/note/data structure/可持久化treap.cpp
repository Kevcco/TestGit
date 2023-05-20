/*
fhq_treap 可持久化
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=5e5+10,INF=(1ll<<31)-1;

int n,m,root[N],idx;
struct node
{
    int l,r;
    int key,val;
    int size;
}tr[N*52];

int get_node(int key)
{
    tr[++idx].key=key;
    tr[idx].val=rand();
    tr[idx].size=1;
    return idx;
}

void pushup(int p)
{
    tr[p].size=1+tr[tr[p].l].size+tr[tr[p].r].size;
}

void split_by_key(int p,int key,int &x,int &y)
{
    if(!p) x=y=0;
    else
    {
        int res;
        if(tr[p].key<=key) x=get_node(0),res=x,tr[x]=tr[p],split_by_key(tr[p].r,key,tr[x].r,y);
        else y=get_node(0),res=y,tr[y]=tr[p],split_by_key(tr[p].l,key,x,tr[y].l);
        pushup(res);
    }
}

void split_by_size(int p,int k,int &x,int &y)
{
    if(!p) x=y=0;
    else
    {
        int res;
        if(tr[tr[p].l].size<k) x=get_node(0),res=x,tr[x]=tr[p],split_by_size(tr[p].r,k-tr[tr[p].l].size-1,tr[x].r,y);
        else y=get_node(0),res=y,tr[y]=tr[p],split_by_size(tr[p].l,k,x,tr[y].l);
        pushup(res);
    }
}

int merge(int x,int y)
{
    if(!x||!y) return x+y;
    int root;
    if(tr[x].val>tr[y].val) root=get_node(0),tr[root]=tr[x],tr[root].r=merge(tr[x].r,y);
    else root=get_node(0),tr[root]=tr[y],tr[root].l=merge(x,tr[y].l);
    pushup(root);
    return root;
}

void insert(int &root,int odd,int key)
{
    int x,y,z;
    y=get_node(key);
    split_by_key(odd,key-1,x,z);
    root=merge(merge(x,y),z);
}

void dele(int &root,int odd,int key)
{
    int x,y,z;
    split_by_key(odd,key-1,x,y);
    split_by_key(y,key,y,z);
    y=merge(tr[y].l,tr[y].r);
    root=merge(merge(x,y),z);
}

int get_rank(int &root,int odd,int key)
{
    int x,y,res;
    split_by_key(odd,key-1,x,y);
    res=tr[x].size+1;
    root=merge(x,y);
    return res;
}

int get_key(int &root,int odd,int rank)
{
    int x,y,z;
    split_by_size(odd,rank-1,x,y);
    split_by_size(y,1,y,z);
    int res=tr[y].key;
    root=merge(merge(x,y),z);
    return res;
}

int get_pre(int &root,int odd,int key)
{
    int x,y,z;
    split_by_key(odd,key-1,y,z);
    split_by_size(y,tr[y].size-1,x,y);
    int res;
    if(y) res=tr[y].key;
    else res=-INF;
    root=merge(merge(x,y),z);
    return res;
}

int get_next(int &root,int odd,int key)
{
    int x,y,z;
    split_by_key(odd,key,x,y);
    split_by_size(y,1,y,z);
    int res;
    if(y) res=tr[y].key;
    else res=-INF;
    root=merge(merge(x,y),z);
    return res;
}


int main()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int v,opt,x;
        scanf("%d%d%d",&v,&opt,&x);
        if(opt==1) insert(root[i],root[v],x);
        else if(opt==2) dele(root[i],root[v],x);
        else if(opt==3) printf("%d\n",get_rank(root[i],root[v],x));
        else if(opt==4) printf("%d\n",get_key(root[i],root[v],x));
        else if(opt==5) printf("%d\n",get_pre(root[i],root[v],x));
        else printf("%d\n",get_next(root[i],root[v],x));
    }
    
    return 0;
}