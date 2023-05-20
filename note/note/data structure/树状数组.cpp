#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=2e5+10;

int tr[N],n,a[N],tr1[N],tr2[N],m;
int tree[N][N];


int lowbit(int x)
{
    return x&-x;
}

//单点修改
//注意x不能等于0，x=0会tle，如果用到 0，一定要映射
void add(int x,int c)
{
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

//维护区间异或时修改操作
//修改a[x]=c;
void Add(int x,int c)
{
    int t=a[x]^c;
    a[x]=c;
    for(int i=x;i<=n;i+=lowbit(i))
        tr[i]^=t;
}

//区间求和
int sum(int x,int tr[]=tr)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

//建树状数组
void init()
{
    //第一种 O(nlogn)
    for(int i=1;i<=n;i++) add(i,a[i]);

    //第二种 O(n) 递推
    for(int i=1;i<=n;i++)
    {
        tr[i]=a[i];
        for(int j=i-1;j>i-lowbit(i);j-=lowbit(j))
        {
            tr[i]+=tr[j];
        }
    }

    //第三种 O(n) 原始定义
    int s[N];
    for(int i=1;i<=n;i++)
    {
        s[i]=s[i-1]+a[i];
        tr[i]=s[i]-s[i-lowbit(i)];
    }
}

//（区间求和 区间修改） 求前缀和
int pre(int x)
{
    return (x+1)*sum(x,tr1)-sum(x,tr2);
}


//二维树状数组
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


//维护区间最值
void build()
{
    for(int i=1;i<=n;i++)
    {
        tr[i]=a[i];
        for(int j=i-1;j>i-lowbit(i);j-=lowbit(j))
            tr[i]=max(tr[i],tr[j]);
    }
}


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

int query(int l,int r)
{
    if(l>r) return 0;
    int res=0;
    if(r-lowbit(r)+1<l) res=max(a[r],query(l,r-1));
    else res=max(tr[r],query(l,r-lowbit(r)));
    return res;
}


/*
树状数组：求前缀信息 单点修改
         tr[i] 保存的是 (i-lowbit(i),i]这一段的和

一.基本
维护特定区间和     O(logn)计算前缀和   O(logn)修改所有包含某一点的区间的和
利用前缀思想 计算区间和
类似可求区间积,区间异或,具有前缀性质的运算(先 / or ^ 原值,再 * or ^ 新值)


1.区间查询 单点修改:  对原数组建树状数组  sum() add()      O(logn)
2.区间修改 单点查询： 对原数组的差分数组建树状数组 sum() add(l,d) add(r+1,-d)      O(logn)
3.区间查询 区间修改(加法)： 维护两个树状数组：tr1 原数组的差分数组的树状数组
                                     tr2 原数组的差分数组，且每个元素乘 i 的树状数组
                    区间修改：tr1 tr2 add(l),add(r+1)
                    区间求和： prefix[x]=(x+1)*sum(tr1,x) - sum(tr2,x)
                                    = x*c[1] + (x-1)*c[2] + ... + 1*c[x]
                             s[l - r]=pre[r]-pre[l-1]

4.二维树状数组：sum() add() 两重循环  O(logn*logm)
              区间修改 单点求和 二维差分
              区间求和 区间修改 维护四个树状数组 tr1 Cij,tr2 i*Cij ,tr3 j*Cij ,tr4 (i-1)*(j-1)*Cij
                推公式 pre[n][m] = (n*m+n+m) * sum(tr1) + sum(tr4) - m * sum(tr2) - n * sum(tr3)




二.拓展 
1.维护区间最值:  如果是求前缀最值 query O(logn)
                如果每次更新都不会变小 也可以直接update  O(logn)
                最值没有前缀性质，但是有结合律，可以通过子区间得到
                update(int x,int c) 所有包含x的区间都要更新，并且每个区间更新时要用子区间重新计算
                    非常像第二种初始化代码  T=O(logn*logn)
                 query(int l,int r) 最值无法用两个前缀和推出，只能精确覆盖
                 if r-lowbit(r)+1 < l 不能使用tr[r],直接使用a[r],递归处理[l,r-1]
                 else 使用tr[r],递归处理[l,r-lowbit(r)]  T=O(logn*logn)

                如果单纯求前缀最值 query() O(logn)
                如果每次更新元素都不会变小 update() O(logn)
                update() query() O(logn*logn)

2.维护区间最大公约数：和 max min 一样 有 gcd(father) =gcd(gcd(son1),gcd(son2),...)
                和维护区间最值一样，update() query() O(logn*logn)
                
                特殊的是，gcd(原数组) = gcd(原数组的差分数组)
                如果是区间同时修改,可以转化成差分数组变成单点修改
                求 gcd (l,r) 需要先得到a[l] (原值) 然后res = gcd( a[l] , gcd(b[l+1,r])) ;
                gcd(b[l+1,r])对应query()操作 a[l] 对应差分数组前缀和
            说明: 直接 gcd(b[l,r]) 是错误的
                gcd(al,al+1,...,ar) = gcd( al , al+1 - al , al+2 - al+1 ,..., ar - ar-1)
                                   != gcd( al - al-1 , al+1 - al , ... , ar - ar-1);

应用：
1.二维偏序问题
    求 1 - i-1 中有多少元素小于/大于 a[i] (求逆序对)  1 <= i <= n   O(nlogn)
    权值树状数组
    定义t[i]数组表示i出现的次数是t[i]   (a[i]范围太大可以保序离散化)
    对t[i]建立树状数组tr[i], 则res[i]=sum(a[i]-1);最后再将a[i]放入集合 add(a[i],1);

2.动态维护一个有序序列，并且每次查询序列里第k小的数(查询全局第k小)
    权值树状数组  第k大转化为第n-k+1小
    插入 O(logn) 

    查询 
    (1)在1的基础上加上二分  O(logn*logn)
        int l=1,r=n (l=min(a[]),r=max(a[])) ; 
        if(sum(mid)<k) l=mid+1; else r=mid; 
        
    (2)倍增 O(logn) 因为树状数组 tr[i] 的特性  从大到小倍增 
       那么 tr[pos + (1<<i)] 记录的就是 pos + 1  ——  pos + (1<<i) 的和
       找 sum < k 的最大的位置 最大的位置的下一个位置就是答案
        int pos=0;
        for(int i=20;i>=0;i--)
        {
            if(pos + (1<<i) <= n && tr[pos + (1<<i)] < k)
                pos += 1<<i, k -= tr[pos];
        }
        return pos+1;

    POJ 2985

3.维护数组 1.单点修改 2.询问前缀不大于s的最大位置
  二分：O(logn*logn)
  倍增: O(logn)
    int query(ll s)
    {
        int pos=0;
        for(int j=20;j>=0;j--)
        {
            if(pos + (1<<j) <= n && tr[pos + (1<<j)] <= s)
                pos += 1<<j, s -= tr[pos];
        }
        return pos;
    } 

题目:
一.推公式
    （1）区间和 区间修改
    （2）求区间方差 单点修改  方差 = sum(ai^2)/n - average^2  维护一个和 一个平方和 即可
        Luogu 5142
*/