// Luogu P5490
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m;
vector<array<int,4>> event;
vector<int> nums;

struct node
{
    //minv : 区间被覆盖的次数的最小值
    //mincnt : 等于最小值的区间长度的和
    int minv,mincnt,tag=0;
}tr[N*8];

void pushup(node &u,node &l,node &r)
{
    u.minv=min(l.minv,r.minv);
    u.mincnt=0;
    if(l.minv==u.minv) u.mincnt+=l.mincnt;
    if(r.minv==u.minv) u.mincnt+=r.mincnt;
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].tag)
    {
        tr[u<<1].minv+=tr[u].tag;
        tr[u<<1].tag+=tr[u].tag;
        tr[u<<1|1].minv+=tr[u].tag;
        tr[u<<1|1].tag+=tr[u].tag;
        tr[u].tag=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={0,nums[L]-nums[L-1],0};
        return;
    }
    int mid=L+R>>1;
    build(u<<1,L,mid),build(u<<1|1,mid+1,R);
    pushup(u);
}

void modify(int u,int L,int R,int l,int r,int d)
{
    if(L>=l&&R<=r)
    {
        tr[u].minv+=d;
        tr[u].tag+=d;
        return;
    }
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r,d);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r,d);
    pushup(u);
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int x1,x2,y1,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        nums.push_back(x1);
        nums.push_back(x2);
        event.push_back({y1,1,x1,x2});
        event.push_back({y2,-1,x1,x2});
    }

    sort(event.begin(),event.end());
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    m=nums.size()-1;
    build(1,1,m);
    int totcnt=tr[1].mincnt;
    ll res=0;
    int prey=0,cover=0;
    for(auto eve : event)
    {
        if(tr[1].minv) cover=totcnt;
        else cover=totcnt-tr[1].mincnt;
        res+=(ll)(eve[0]-prey)*cover;
        prey=eve[0];
        int x1=lower_bound(nums.begin(),nums.end(),eve[2])-nums.begin()+1; 
        int x2=lower_bound(nums.begin(),nums.end(),eve[3])-nums.begin();
        if(x1>x2) continue;
        modify(1,1,m,x1,x2,eve[1]); 
    }

    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}