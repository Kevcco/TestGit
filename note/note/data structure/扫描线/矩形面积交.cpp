/*
求至少被矩形覆盖两次的面积
维护被覆盖次数最小值。次小值
和最小值的长度，次小值长度
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10,inf=1e9;

int n,m;
vector<array<double,4>> event;
vector<double> nums;

struct node
{
    int minv,minv2;
    double mincnt,mincnt2;
    int tag;
}tr[N*8];

void pushup(node &u,node &l,node &r)
{
    u.minv=min(l.minv,r.minv);
    u.mincnt=0;
    if(l.minv==u.minv) u.mincnt+=l.mincnt;
    if(r.minv==u.minv) u.mincnt+=r.mincnt;
    
    if(l.minv==r.minv) u.minv2=min(l.minv2,r.minv2);
    else u.minv2=min(max(l.minv,r.minv),min(l.minv2,r.minv2));
    u.mincnt2=0;
    if(u.minv2!=u.minv)
    { 
        if(l.minv==u.minv2) u.mincnt2+=l.mincnt;
        if(r.minv==u.minv2) u.mincnt2+=r.mincnt;
        if(l.minv2==u.minv2) u.mincnt2+=l.mincnt2;
        if(r.minv2==u.minv2) u.mincnt2+=r.mincnt2;
    }
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
        tr[u<<1].minv2+=tr[u].tag;
        tr[u<<1].tag+=tr[u].tag;
        tr[u<<1|1].minv+=tr[u].tag;
        tr[u<<1|1].minv2+=tr[u].tag;
        tr[u<<1|1].tag+=tr[u].tag;
        tr[u].tag=0;
    }
}

void build(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={0,inf,nums[L]-nums[L-1],0,0};
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
        tr[u].minv2+=d;
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
    nums.clear();
    event.clear();
    for(int i=1;i<=8*n;i++) tr[i].tag=0,tr[i].minv2=inf;
    for(int i=1;i<=n;i++)
    {
        double x1,x2,y1,y2;
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
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
    double totcnt=tr[1].mincnt;
    double res=0;
    double prey=0;
    for(auto eve : event)
    {
        double cover=0;
        if(tr[1].minv>1) cover=totcnt;
        else if(tr[1].minv==1) cover=totcnt-tr[1].mincnt;
        else
        {
            if(tr[1].minv2>1) cover=totcnt-tr[1].mincnt;
            else cover=totcnt-tr[1].mincnt-tr[1].mincnt2;
        }
        res+=(eve[0]-prey)*cover;
        prey=eve[0];
        int x1=lower_bound(nums.begin(),nums.end(),eve[2])-nums.begin()+1; 
        int x2=lower_bound(nums.begin(),nums.end(),eve[3])-nums.begin();
        if(x1>x2) continue;
        modify(1,1,m,x1,x2,(int)eve[1]); 
    }

    printf("%.2lf\n",res);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}