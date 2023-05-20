/*

有旋treap: tree (key) + heap (val) + zig zag
struct node
{
    int l,r;
    int key,val;
    int size,cnt;
}

(1)  get_node(int key) 新开节点
(2)  pushup(int p)  向上更新
(3)  zig(int &p) 右旋
(4)  zag(int &p) 左旋
(6)  insert(int &p,int key) 插入键值为key的节点 插入完判断是否要旋转来保持堆的性质 更新节点
(7)  delete(int &p,int key) 删除键值为key的节点 判断要删除的类型 如果有儿子 要旋转成叶子节点
(8)  get_rank_by_key(int p,int key) 
     找到键值key在树中的排名 即 树中比key小的数的个数+1
     键值key在树中可以不存在 if(!p) return 1;
(9)  get_key_by_rank(int p,int rank) 
     找到排名rank对应的键值key 如果不存在 返回INF
(10) get_pre(int p,int key) 
     找到小于key的最大数 键值key在树中可以不存在 
     如果答案不存在 返回-INF
     对代码微调可以找小于等于key的最大数
(11) get_next(int p,int key) 
     找到大于key的最小数  
     如果答案不存在 返回INF
     对代码微调可以找大于等于key的最小数

(6)插入时的旋转操作是保证treap期望深度的关键
(8)(9)(10)(11)是二叉搜索树的通用方法

*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N=1e5+10,INF=1e9+10;
 
int n,root,idx;
struct node
{
    int l,r;
    int key,val;
    int cnt,size;
}tr[N];

int get_node(int key)
{
    tr[++idx].key=key;
    tr[idx].val=rand();
    tr[idx].cnt=tr[idx].size=1;
    return idx;
}

void pushup(int p)
{
    tr[p].size=tr[tr[p].l].size+tr[p].cnt+tr[tr[p].r].size;
}

void zig(int &p)
{
    int q=tr[p].l;
    tr[p].l=tr[q].r,tr[q].r=p,p=q;
    pushup(tr[p].r),pushup(p);
}

void zag(int &p)
{
    int q=tr[p].r;
    tr[p].r=tr[q].l,tr[q].l=p,p=q;
    pushup(tr[p].l),pushup(p);
}

void insert(int &p,int key)
{
    if(!p) p=get_node(key);
    else if(tr[p].key==key) tr[p].cnt++;
    else if(tr[p].key>key)
    {
        insert(tr[p].l,key);
        if(tr[tr[p].l].val>tr[p].val) zig(p);
    }
    else
    {
        insert(tr[p].r,key);
        if(tr[tr[p].r].val>tr[p].val) zag(p);
    }

    pushup(p);
    
}

void dele(int &p,int key)
{
    if(!p) return;
    if(tr[p].key==key)
    {
        if(tr[p].cnt>1) tr[p].cnt--;
        else if(tr[p].l||tr[p].r)
        {
            if(!tr[p].r||tr[tr[p].l].val>tr[tr[p].r].val)
            {
                zig(p);
                dele(tr[p].r,key);
            }
            else
            {
                zag(p);
                dele(tr[p].l,key);
            }
        }
        else p=0;
    }
    else if(tr[p].key>key) dele(tr[p].l,key);
    else dele(tr[p].r,key);
    
    pushup(p);
}

int get_rank(int p,int key)
{
    if(!p) return 1;
    if(tr[p].key==key) return tr[tr[p].l].size+1;
    if(tr[p].key>key) return get_rank(tr[p].l,key);
    return get_rank(tr[p].r,key)+tr[p].cnt+tr[tr[p].l].size;
}

int get_key(int p,int rank)
{
    if(!p) return INF;
    if(tr[tr[p].l].size>=rank) return get_key(tr[p].l,rank);
    if(tr[tr[p].l].size+tr[p].cnt>=rank) return tr[p].key;
    return get_key(tr[p].r,rank-tr[p].cnt-tr[tr[p].l].size);
}

int get_pre(int p,int key)
{
    if(!p) return -INF;
    if(tr[p].key>=key) return get_pre(tr[p].l,key);
    return max(tr[p].key,get_pre(tr[p].r,key));
}

int get_next(int p,int key)
{
    if(!p) return INF;
    if(tr[p].key<=key) return get_next(tr[p].r,key);
    return min(tr[p].key,get_next(tr[p].l,key));
}

int main()
{
    cin >> n;
    while(n--)
    {
        int opt,x;
        scanf("%d%d",&opt,&x);
        if(opt==1) insert(root,x);
        else if(opt==2) dele(root,x);
        else if(opt==3) printf("%d\n",get_rank(root,x));
        else if(opt==4) printf("%d\n",get_key(root,x));
        else if(opt==5) printf("%d\n",get_pre(root,x));
        else printf("%d\n",get_next(root,x));
    }
    
    return 0;
}