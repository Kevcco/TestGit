
#include <bits/stdc++.h>

using namespace std;

const int N=50010;

int tr[N],n,m,a[N],tree[N][N];
int tr1[N],tr2[N];

// 树状数组
int lowbit(int x)
{
    return x&-x;
}

void init()
{
    for(int i=1;i<=n;i++)
    {
        tr[i]=a[i];
        for(int j=i-1;j>i-lowbit(i);j-=lowbit(j))
        {
            tr[i]+=tr[j];
        }
    }
}

void add(int x,int c,int tr[]=tr)
{
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

int sum(int x,int tr[]=tr)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}


// 二维树状数组
void add(int x,int y,int c)
{
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j))
            tree[i][j]+=c;
}

int sum(int x,int y)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            res+=tree[i][j];
}


// 区间加，区间求和 ：tr1维护差分数组d[i], tr2维护 i*d[i]
// 求 sum 1-x 
int pre(int x)
{
    return (x+1)*sum(x,tr1)-sum(x,tr2);
}


// 维护区间最值
void update(int x,int c)
{
    //剪枝优化
    if(c==a[x]) return;
    if(c>a[x])
    {
        for(int i=x;i<=n;i+=lowbit(i))
            tr[i]=max(tr[i],c);
        a[x]=c;
        return;
    }

    a[x]=c;
    for(int i=x;i<=n;i+=lowbit(i))
    {
        tr[i]=a[i];
        for(int j=i-1;j>i-lowbit(i);j-=lowbit(j))
            tr[i]=max(tr[i],tr[j]);
    }
}

//如果是前缀最值可以直接O(logn)求
int query(int l,int r)
{
    if(l>r) return 0;
    int res=0;
    if(r-lowbit(r)+1<l) res=max(a[r],query(l,r-1));
    else res=max(tr[r],query(l,r-lowbit(r)));
    return res;
}


// 倍增求序列第k小
int k_min(int k)
{
    int pos=0;
    for(int i=20;i>=0;i--)
    {
        if(pos+(1<<i)<=n && tr[pos+(1<<i)]<k)
            pos+=1<<i,k-=tr[pos];
    }
    return pos+1;
}