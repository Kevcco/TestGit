/*
pushup() 子节点更新父节点
pushdown() 父节点信息传给子节点 更新子节点
build() 递归建树 回溯时 pushup 合并
modify() 单点修改 只用回溯时pushup  区间修改 递归前pushdown 回溯时 pushup
query() 递归前 pushdown


懒标记:当前节点的懒标记是对所有子节点的 不包括自己
      不考虑父节点的懒标记 当前节点的信息是正确的信息

1.query  O(4logn)
    递归找精确覆盖询问的若干个线段，然后合并子线段
    具体而言，如果询问只覆盖当前区间的某一半边，直接递归一半，否则，需要递归两边，然后将两边合并，
    相当于pushup 不同信息的合并操作不同
    也就是四类 (1)完全被查询区间包含 直接返回
             （2）r<=trmid 直接递归左儿子
             （3）l>trmid 直接递归右儿子
             （4）否则 需要分别递归两边 得到两边的信息 然后 node res; pushup(res,left,right)
                  返回 res

2.单点modify  O(logn)
    递归找到具体的某一点，直接修改这一点信息，然后pushup回溯修改相关的父节点

3.区间modify  懒标记 O(4logn)
    分类和查询一样
    修改时，如果全覆盖，直接修改，如果需要递归，并且当前有懒标记，需要先pushdown，把当前信息传给子节点，
    因为子节点信息并不是正确信息，回溯时用子节点信息重新算父节点信息会错
    直到找到完全覆盖的节点，修改节点信息使其呈现正确信息，并且修改懒标记
    也就是新的懒标记的递归上层必然没有旧的懒标记，经过时都下放了

    能使用lazy tag必须满足两点
    1.节点的信息能通过lazy tag更新
    2.lazy tag之间能快速合并

4.动态开点线段树: 不build 动态开点 结构体多存储 lson rson
  动态开点 适合处理l,r范围 [1,1e9] 但询问用到的点很少 或者 处理l,r范围有负数的情况
  这样就不用离散化(有的情况甚至不能离散化)

  空间复杂度 O(mlogn) m是询问个数 n是值域

  一开始认定所有元素是0 在pushdown时开点
  注意为了处理负数 mid=l+r-1>>1;
  需要手动初始化根节点


5.可持久化线段树
6.势能线段树
  

题目:
1.维护区间和
    tr[u].sum=tr[ls].sum+tr[rs].sum
    单点修改
    区间同加 懒标记add  

2.区间最值 
    tr[u].maxv=max(tr[ls].maxv,tr[rs].maxv);
    单点修改
    区间同加 懒标记add tr[son].maxv+=tr[u].add

3.维护区间和 区间修改可同加可同乘
    懒标记 add mul 表示先乘再加 (顺序很重要)
    pushdown: tr[son].mul*=tr[u].mul; tr[son].add=tr[son].add*tr[u].mul+tr[u].add;

4.维护区间最大公约数
    tr[u].d=gcd(tr[ls].d,tr[rs].d);
    单点修改 直接维护原数组的最大公约数
    区间修改:转化成维护原数组的差分数组的最大公约数，变成单点修改
            求原数组的最大公约数
            gcd(ai,ai+1,ai+2,...,aj) = gcd ( ai , ai+1 - ai , ai+2 - ai+1 ,..., aj - aj-1 );
                                     = gcd ( prefix(bi) , bi+1 , bi+2 , ... bj );
            注意 gcd(ai,ai+1,ai+2,...,aj) != gcd(ai - ai-1,ai+1 - ai,ai+2 - ai+1,...,aj - aj-1);
            同时维护差分数组的 区间和 和 最大公约数，或者单开一个树状数组或线段树

5.维护区间最大连续子序列和  主要考虑分治后的合并操作 如何合并两个子段 分类讨论
    tr[u].tmax = max { tr[ls].tmax , tr[rs].tmax , tr[ls].rmax+tr[rs].lmax };
    lmax表示最大前缀和，rmax表示最大后缀和
    求lmax/rmax  两种情况
    tr[u].lmax = max { tr[ls].lmax , tr[ls].sum + tr[rs].ls};

    因此最终维护 tmax lmax rmax sum
    单点修改
    区间修改似乎不行

    一些拓展：
    (1)单点修改，[x1,y1] [x2,y2] 询问左端点在[x1,y1] 右端点在[x2,y2] 的最大连续子序列和
        1. y1<=x2 此时[y1,x2]段必须包含[y1,x2]  tmax = sum(y1+1,x2-1) + rmax[x1,y1] + lmax[x2,y2]
        2.两区间有交集：
            (1)完全包含:y2<=y1  tmax = max ( tmax(x2,y2) , rmax(x1,x2)+lmax(x2,y2))
            (2)y2>y1  tmax = max ( tmax(x2,y1) , rmax(x1,x2)+lmax(x2,y2) , rmax(x1,y1)+lmax(y1,y2));
    
    (2)给定01序列，操作是区间取反，即将1变0，0变1，操作和询问随机发生，询问区间[l,r]内最长的连续的1的个数
        01序列 特殊的区间修改 
            维护 tmax0 tmax1 lmax0 lmax1 rmax0 rmax1 add
            懒标记add 取值 0 1 因为两次取反就变回去了
            pushdown操作: if(add) 交换所有的 0 1 信息
        https://ac.nowcoder.com/acm/contest/992/K

    (3)最长连续上升子序列 单点修改
            维护 tmax rmax lmax 
            tr[u].tmax = max ( tr[ls].tmax , tr[rs],tmax , 
                               a[trmid]<a[trmid+1] ? tr[ls].rmax+tr[rs].lmax : 0);
            tr[u].lmax= tr[ls].lmax;
            if(tr[ls].lmax == trlen(ls)) tr[u].lmax += tr[rs].lmax



*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,a[N];

//普通线段树
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
    node res,ls=query(u<<1,L,mid,l,r),rs=query(u<<1|1,mid+1,R,l,r);
    pushup(res,ls,rs);
    return res;
}


// //动态开点 初始时元素全为0
// //root=1;
// struct node
// {
//     int ls,rs;

// }tr[N*4];
// int root=1,id=1;

// void pushup(node &u,node &left,node &right)
// {

// }

// void pushup(int u)
// {
//     pushup(tr[u],tr[tr[u].ls],tr[tr[u].rs]);
// }

// void pushdown(int u,int len)
// {
//      if(!tr[u].ls) tr[u].ls=++id;
//      if(!tr[u].rs) tr[u].rs=++id;
//
// }

// //区间修改
// void modify(int &u,int L,int R,int l,int r,int d)
// {
//     if(!u) u=++id;
//     if(L>=l&&R<=r)
//     {
        
//         return;
//     }
//     pushdown(u,R-L+1);
//     int mid=L+R-1>>1;
//     if(l<=mid) modify(tr[u].ls,L,mid+1,l,r,d);
//     if(r>mid) modify(tr[u].rs,mid,R,l,r,d);
//     pushup(u);
// }

// //单点修改
// void modify(int &u,int L,int R,int x,int v)
// {
//     if(!u) u=++id;
//     if(L==R)
//     {

//         return;
//     }
//     int mid=L+R-1>>1;
//     if(x>mid) modify(tr[u].rs,mid+1,R,x,v);
//     else modify(tr[u].ls,L,mid,x,v);
//     pushup(u);
// }

// //查询 注意一定要保证 l <= r 
// node query(int u,int L,int R,int l,int r)
// {
//     if(!u) return node(); // 元素没有修改过 为0
//     if(L>=l&&R<=r) return tr[u];
//     pushdown(u,R-L+1);
//     int mid=L+R-1>>1;
//     if(l>mid) return query(tr[u].rs,mid+1,R,l,r);
//     else if(r<=mid) return query(tr[u].ls,L,mid,l,r);
//     node res;
//     node left=query(tr[u].ls,L,mid,l,r);
//     node right=query(tr[u].rs,mid+1,R,l,r);
//     pushup(res,left,right);
//     return res;
// }


