
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+10,INF=1e8+10;

int n,m,idx,root;
int a[N],st[N];
//相同权值的点不会去重 同时存在
struct node
{
    int l,r;
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

//按照key将树分成<=key和>key的两棵子树
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

//按前k个分配 将树分成前k个点组成的树和剩余点组成的树
void split_by_size(int p,int k,int &x,int &y)
{
    if(!p) x=y=0;
    else
    {
        if(tr[tr[p].l].size<k) x=p,split_by_size(tr[p].r,k-tr[tr[p].l].size-1,tr[x].r,y);
        else y=p,split_by_size(tr[p].l,k,x,tr[y].l);
        pushup(p);
    }
}

//合并x和y两棵树 其中x.key<y.key 返回合并后的根
int merge(int x,int y)
{
    if(!x||!y) return x+y;
    int res;
    if(tr[x].val>tr[y].val) res=x,tr[x].r=merge(tr[x].r,y);
    else res=y,tr[y].l=merge(x,tr[y].l);
    pushup(res);
    return res;
}

//插入:按照key分裂 开新点 合并左和新点 再合并右
void insert(int &p,int key)
{
    int x,y;
    split_by_key(p,key,x,y);
    int new_node=get_node(key);
    p=merge(merge(x,new_node),y);
}

//删除:按照key分裂成三部分 删除中间部分的根 合并三次
void dele(int &p,int key)
{
    int x,y,z;
    split_by_key(p,key,x,z);
    split_by_key(x,key-1,x,y);
    y=merge(tr[y].l,tr[y].r);
    p=merge(merge(x,y),z);
}

//获得key的排名:按key-1分裂 排名就是左子树的大小+1
int get_rank(int &p,int key)
{
    int x,y,res;
    split_by_key(p,key-1,x,y);
    res=tr[x].size+1;
    p=merge(x,y);
    return res;
}

//rank对应的key rank<1返回最小数 rank>sum_node返回INF
int get_key(int &p,int rank)
{
    int x,y,z,res;
    split_by_size(p,rank-1,x,y);
    split_by_size(y,1,y,z);
    if(y) res=tr[y].key;
    else res=INF;
    p=merge(merge(x,y),z);
    return res;
}

//前驱 不存在返回-INF
int get_pre(int &p,int key)
{
    int x,y,z,res;
    split_by_key(p,key-1,y,z);
    split_by_size(y,tr[y].size-1,x,y);
    if(y) res=tr[y].key;
    else res=-INF;
    p=merge(merge(x,y),z);
    return res;
}

//后继 不存在返回INF
int get_next(int &p,int key)
{
    int x,y,z,res;
    split_by_key(p,key,x,y);
    split_by_size(y,1,y,z);
    if(y) res=tr[y].key;
    else res=INF;
    p=merge(merge(x,y),z);
    return res;
}

void dfs(int p)
{
    if(!p) return;
    dfs(tr[p].l),dfs(tr[p].r);
    pushup(p);
}

//a[]是有序序列 O(n)建树建成 treap 别忘记最后dfs更新信息
void build(int &root,int len)
{
    int top=0;
    for(int i=1;i<=len;i++)
    {
        int k=top;
        int new_id=get_node(a[i]);
        while(k&&tr[st[k]].val<tr[new_id].val) k--;
        if(k) tr[st[k]].r=new_id;
        if(k<top) tr[new_id].l=st[k+1];
        st[++k]=new_id;
        top=k;
    }
    root=st[1];
    dfs(root);
}


int main()
{
    cin >> n >> m;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        insert(root,x);
    }
    int last=0;
    int ans=0;
    while(m--)
    {
        int opt,x;
        scanf("%d%d",&opt,&x);
        x^=last;
        if(opt==1) insert(root,x);
        else if(opt==2) dele(root,x);
        else if(opt==3) last=get_rank(root,x);
        else if(opt==4) last=get_key(root,x);
        else if(opt==5) last=get_pre(root,x);
        else last=get_next(root,x);
        if(opt>2) ans^=last;
    }
    
    printf("%d\n",ans);
    
    return 0;
}
