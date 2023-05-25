/*
x和y分别计算
扫描线 每修改一次，他的贡献就是修改前和修改后覆盖长度的差值
注意y相同时，需要先处理插入，再处理删除
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m;
vector<array<int,4>> event,event2;
vector<int> nums,nums2;
ll res;
struct node
{
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

void build2(int u,int L,int R)
{
    if(L==R)
    {
        tr[u]={0,nums2[L]-nums2[L-1],0};
        return;
    }
    int mid=L+R>>1;
    build2(u<<1,L,mid),build2(u<<1|1,mid+1,R);
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

void atlantis()
{
    sort(event.begin(),event.end());
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    m=nums.size()-1;
    build(1,1,m);
    int totcnt=tr[1].mincnt;
    for(auto eve : event)
    {
        int cover1=0;
        if(tr[1].minv) cover1=totcnt;
        else cover1=totcnt-tr[1].mincnt;
        int x1=lower_bound(nums.begin(),nums.end(),eve[2])-nums.begin()+1; 
        int x2=lower_bound(nums.begin(),nums.end(),eve[3])-nums.begin();
        if(x1>x2) continue;
        modify(1,1,m,x1,x2,-eve[1]);
        int cover2=0;
        if(tr[1].minv) cover2=totcnt;
        else cover2=totcnt-tr[1].mincnt;
        res+=abs(cover1-cover2);
    }
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
        nums2.push_back(y1);
        nums2.push_back(y2);
        event.push_back({y1,-1,x1,x2});
        event.push_back({y2,1,x1,x2});
        event2.push_back({x1,-1,y1,y2});
        event2.push_back({x2,1,y1,y2});
    }

    atlantis();
    for(int i=1;i<=8*n;i++) tr[i].tag=0;
    nums.swap(nums2);
    event.swap(event2);
    atlantis();
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}