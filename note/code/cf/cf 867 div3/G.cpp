/*
给定长为n的数组 n<=2e5  ai<=1e9
求三元组[i,j,k]的个数
三元组满足 i,j,k互不相同 且 存在正整数x 使得 ai * x = aj = ak / b


开一个map记录所有数出现的个数
考虑枚举 aj，然后枚举x  x的枚举次数 = min(aj,maxA/aj) 因此总时间 O(n*根号A)
考虑如何优化枚举 可以将aj分解因子 然后直接枚举因子 由于因子个数很少 所以瓶颈在分解因子 仍然是O(n*根号A)
想到了类似根号分治的做法 将两种方式均衡一下
按值域分治
对于 aj <= s 那么分解因子  aj > s 那么直接暴力枚举 x
总时间 O(n * 根号s + n * min(s, maxA/s)) 让s适当的大 取 s = 1e6
那么时间就是 O(n * 1e3 + n * 1e3) = 2e8 可以接受

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10,S=1e6+10,S2=1e9+10;

int n,m,k;
map<int,int> mp;
int p[N];

ll c3(int x)
{
    return (ll)x*(x-1)*(x-2);
}

vector<int> breakdown(int x)
{
    vector<int> res;
    for(int i=1;i<=x/i;i++)
    {
        if(x%i==0)
        {
            res.push_back(i);
            if(x/i!=i) res.push_back(x/i);
        }
    }
    return res;
}

void solve()
{
    cin >> n;
    ll res=0;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1;i<=n;i++) mp[p[i]]++;
    for(auto u : mp)
    {
        res+=c3(u.second);
        if(u.first<S)
        {
            auto fact=breakdown(u.first);
            sort(fact.begin(),fact.end());
            for(auto x : fact)
            {
                if(x==1) continue;
                if((ll)x*u.first>=S2) break;
                if(mp.count(u.first/x)&&mp.count(u.first*x))
                    res+=(ll)u.second*mp[u.first/x]*mp[u.first*x];
            }
        }
        else
        {
            for(int i=2;(ll)i*u.first<S2;i++)
            {
                if(u.first%i) continue;
                if(mp.count(u.first/i)&&mp.count(u.first*i))
                res+=(ll)u.second*mp[u.first/i]*mp[u.first*i];
            }
        }
    }

    printf("%lld\n",res);
    mp.clear();
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}