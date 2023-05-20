/*
Luogu P 2163
单点加 矩阵查询
利用二维前缀和转化为二维限制 x <= xi, y <= yi
加点和询问都看作事件
扫描线维护y，树状数组维护x
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m;
vector<int> nums;
//y坐标，事件类型(0加，1/2查询，1正2负)，x坐标，询问id
vector<array<int,4>> event;
int ans[N],tr[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

int sum(int x)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        //只需要对点的x坐标离散化
        nums.push_back(x);
        event.push_back({y,0,x,0});
    }
    for(int i=1;i<=m;i++)
    {
        int x1,x2,y1,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        event.push_back({y2,1,x2,i});
        event.push_back({y2,2,x1-1,i});
        event.push_back({y1-1,2,x2,i});
        event.push_back({y1-1,1,x1-1,i});
    }
    sort(event.begin(),event.end());
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    
    for(auto x : event)
    {
        if(!x[1])
        {
            int y=lower_bound(nums.begin(),nums.end(),x[2])-nums.begin()+1;
            add(y,1);
        } 
        else
        {
            int y=upper_bound(nums.begin(),nums.end(),x[2])-nums.begin();
            int t=sum(y);
            if(x[1]==1) ans[x[3]]+=t;
            else ans[x[3]]-=t;
        }
    }

    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}

int main()
{
    solve();
    return 0;
}