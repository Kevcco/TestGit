/*
一个游戏有n关 n <= 1e5  
每关有一个boss，血量是 hi，杀死这个boss，其他所有的boss血量会增加 ai，你的攻击力会增加 bi
攻击力大于boss血量即可杀死boss
询问初始攻击力最小是多少 能将 n 个boss全部杀死
此外，还有额外的 k 关 k <= 1000
每增加一关，再次询问初始攻击力的最小值（也就是通过  n+1, n+2, ... , n+k 关分别的最小值） 

考虑转化，其他所有boss血量加 ai , 攻击力加 bi ，可以转化成 攻击力加 bi - ai,设为 ci
现在考虑贪心
(1) 一定是先杀完所有 ci >= 0 的boss更优
    假设相邻两关 hi,ci , hj,cj 其中 ci<0,cj>=0
    如果按当前顺序能杀死这两个boss，即 x >= hi , x + ci >= hj
    那么交换顺序闯关 由于 x >= hj -ci  故 x > hj 可以杀死第一个 而 x + cj >= x >= hi 必然也可以杀死第二个
    故得证 

(2) ci >= 0 的, 按 hi 从小到大排序闯关
    hi >= hj 若有  x >= hi, x + ci >= hj
    必然有 x >= hi >= hj, x + cj >= x >= hi

(3) ci < 0 的 ，按照 hi + ci 从大到小排序
    假设有情况是先打 i ，可以打 j ，但是先打 j，不能打 i 了
    那么有 x >= hi , x + ci >= hj ,  x >= hj , x + cj < hi
    那么必然有  hi - cj > x >= hj - ci 即 hi + ci > hj + cj
    故按照 hi + ci 从大到小 必然是最优的

如此排序后贪心闯关， 即可 O(n)求出最小值
对于额外的k个关卡，每次找到多的关卡应该插入的位置，然后插入，O(n)求得答案
O(nlogn + k*n) = O(1e8)
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
pair<ll,ll> st[N],st2[N]; 

bool cmp(pair<ll,ll> &a,pair<ll,ll> &b)
{
    if(a.second>=0&&b.second>=0) return a.first<b.first;
    else if(a.second<0&&b.second<0) return a.first+a.second>b.first+b.second;
    return a.second>b.second;
}

ll check()
{
    ll res=-1e9;
    ll t=0;
    for(int i=1;i<=n;i++)
    {
        if(res+t<st[i].first) res=st[i].first-t;
        t+=st[i].second;
    }
    return res;
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%lld",&st[i].first);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        st[i].second=y-x;
    }
    cin >> k;
    for(int i=1;i<=k;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        st2[i].first=x,st2[i].second=z-y;
    }
    st[0]={-2e9,1e9};
    sort(st+1,st+n+1,cmp);
    printf("%lld\n",check());
    for(int i=1;i<=k;i++)
    {
        int pos=0;
        while(pos<=n&&cmp(st[pos],st2[i])) pos++;
        for(int j=n+1;j>pos;j--) st[j]=st[j-1];
        st[pos]=st2[i];
        n++;
        printf("%lld\n",check());
    }
}

int main()
{
    solve();
    return 0;
}