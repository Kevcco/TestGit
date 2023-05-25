/*
给出n个底边在x轴上的矩形，求轮廓线的顶点坐标

按x轴扫，维护高度h的最大值，如果一次事件后最大值有变化，那么将会产生两个顶点
一个是事件前的最大值，一个是事件后的最大值
注意相同x坐标的，先处理插入再处理删除
插入先处理y更大的，删除先处理y更小的
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,k;
vector<pii> event;

void solve()
{
    cin >> n;
    for(int i=0;i<n;i++)
    {
        int h,l,r;
        scanf("%d%d%d",&h,&l,&r);
        event.push_back({l,-h});
        event.push_back({r,h});
    }

    sort(event.begin(),event.end());
    multiset<int> s;
    s.insert(0);
    vector<pii> ans;
    int h=0;
    for(auto e : event)
    {
        if(e.second<0) s.insert(-e.second);
        else s.erase(s.find(e.second));
        if(*s.rbegin()!=h)
        {
            ans.push_back({e.first,h});
            ans.push_back({e.first,*s.rbegin()});
            h=*s.rbegin();
        }
    }
    printf("%d\n",ans.size());
    for(auto x : ans) printf("%d %d\n",x.first,x.second);
}

int main()
{
    solve();
    return 0;
}