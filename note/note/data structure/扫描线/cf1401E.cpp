/*
在左下角(0,0)右上角(1e6,1e6)的矩形内
给出n条横线m条竖线，每条线都至少有一个端点在矩形的边上
问矩形内被划分成了几块

结论：
ans=(内部交点数 p) + (1e6长度线段数 s) + 1
证明：
s=0的情况，所有线段都贴且仅贴一边又互相不重合，所以每多一个交点多一个块易证。
s>0的情况
如果一条长度为1e6的线段不穿过线段，那么固然把正方形分成两块多一块。
否则从一条被穿过的线段把它拆成两条线段考虑，答案也会 +1

综上，ans=p+s+1
。
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m;
vector<int> nums;
vector<array<int,3>> event;
struct node
{
    int cnt=0;
}tr[N*4];

void pushup(node &u,node &l,node &r)
{
    u.cnt=l.cnt+r.cnt;
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void modify(int u,int L,int R,int x,int d)
{
    if(L==R)
    {
        tr[u].cnt=d;
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
    int mid=L+R>>1;
    if(l>mid) return query(u<<1|1,mid+1,R,l,r);
    else if(r<=mid) return query(u<<1,L,mid,l,r);
    node res,ls=query(u<<1,L,mid,l,r),rs=query(u<<1|1,mid+1,R,l,r);
    pushup(res,ls,rs);
    return res;
}

int find1(int x)
{
    return upper_bound(nums.begin(),nums.end(),x)-nums.begin();
}

int find2(int x)
{
    return lower_bound(nums.begin(),nums.end(),x)-nums.begin()+1;
}


void solve()
{
    cin >> n >> m;
    ll res=1;
    for(int i=0;i<n;i++)
    {
        int h,l,r;
        scanf("%d%d%d",&h,&l,&r);
        if(r-l==1000000) res++;
        nums.push_back(h);
        event.push_back({l,0,h});
        event.push_back({r,3,h});
    }
    for(int i=0;i<m;i++)
    {
        int h,l,r;
        scanf("%d%d%d",&h,&l,&r);
        if(r-l==1000000) res++;
        if(!l) event.push_back({h,1,r});
        else event.push_back({h,2,l});
    }

    nums.push_back(0);
    nums.push_back(1000000);
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    n=nums.size();

    sort(event.begin(),event.end());
    for(auto e : event)
    {
        if(e[1]==1)
        {
            int t=find1(e[2]);
            res+=query(1,1,n,1,t).cnt;
        }
        else if(e[1]==2)
        {
            int t=find2(e[2]);
            res+=query(1,1,n,t,n).cnt;

        }
        else if(e[1]==0)
        {
            int t=find2(e[2]);
            modify(1,1,n,t,1);
        }
        else
        {
            int t=find2(e[2]);
            modify(1,1,n,t,0);
        }
    }
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}