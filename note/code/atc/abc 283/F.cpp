/*
给定1-n的一个全排列    n=2e5
求所有数的 D 值
Di = min ( |ai - aj| + |i - j| )    i != j



1.线段树
2.曼哈顿距离最小生成树



1.
分类讨论打开绝对值
 (1) i>j && ai>=aj   Di=min(ai-aj+i-j) = ai+i - max(aj+j) 
 (2) i>j && ai<=aj   Di=min(aj-ai+i-j) = i-ai - max(j-aj) 
 (3) i<j && ai>=aj   Di=min(ai-aj+j-i) = ai-i - max(aj-j) 
 (4) i<j && ai<=aj   Di=min(aj-ai+j-i) = -ai-i - max(-aj-j) 

二维偏序问题 求在二维条件约束下的区间信息（最值，总和）
循环控制一维，数据结构维护另一维

 因此可以用 线段树 or 树状数组 查询区间最值
 对(1)而言，便是在满足  j<i 情况下，寻找 aj > ai 的所有元素中max(aj+j) 建立tr[aj]=aj+j,查询区间[aj,n]最值
 类似统计逆序对： 满足  j<i 情况下，寻找 aj > ai 的所有元素的数量 建立cnt[aj]=1,查询区间[aj,max]和


*/
#include <bits/stdc++.h>
#define ls u<<1
#define rs u<<1|1

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
int res[N];

struct node
{
    int l,r,maxv;
}tr[N*4];

void pushup(int u)
{
    tr[u].maxv=max(tr[ls].maxv,tr[rs].maxv);
}

void build(int u,int l,int r)
{
    if(l==r)
    {
        tr[u]={l,r,-0x3f3f3f3f};
        return;
    }
    tr[u]={l,r};
    int mid=l+r>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    pushup(u);
}

void modify(int u,int x,int c)
{
    if(tr[u].l==tr[u].r)
    {
        tr[u].maxv=c;
        return;
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(x>mid) modify(rs,x,c);
    else modify(ls,x,c);
    pushup(u);
}

int query(int u,int l,int r)
{
    if(l>r) return -0x3f3f3f3f;
    if(tr[u].l>=l&&tr[u].r<=r) return tr[u].maxv;
    int mid=tr[u].l+tr[u].r>>1;
    int res=-0x3f3f3f3f;
    if(l<=mid) res=max(res,query(ls,l,r));
    if(r>mid) res=max(res,query(rs,l,r));
    return res;
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i);

    memset(res,0x3f,sizeof res);

    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        res[i]=min(res[i],p[i]+i-query(1,1,p[i]));
        modify(1,p[i],p[i]+i);
    }
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        res[i]=min(res[i],i-p[i]-query(1,p[i],n));
        modify(1,p[i],i-p[i]);
    }
    build(1,1,n);
    for(int i=n;i>0;i--)
    {
        res[i]=min(res[i],p[i]-i-query(1,1,p[i]));
        modify(1,p[i],p[i]-i);
    }
    build(1,1,n);
    for(int i=n;i>0;i--)
    {
        res[i]=min(res[i],-p[i]-i-query(1,p[i],n));
        modify(1,p[i],-p[i]-i);
    }

    for(int i=1;i<=n;i++) printf("%d ",res[i]);
}

int main()
{
    solve();
    return 0;
}