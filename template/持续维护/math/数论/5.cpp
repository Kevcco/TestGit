/*
因子个数上界  
n <= 1e8 d(n) <= 1e3
n <= 1e18 d(n) <= 1e5

n = a * b  a,b <= 1e9 
分解质因数后dfs出n的因子
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

// dfs 枚举因子
vector<pii> prime;
vector<pair<ll,ll>> factor;
void dfs(int id,ll k1,ll k2) 
{
    if(id==prime.size()) 
    {
        factor.push_back({k1,k2});
        return;
    }
    int p=prime[id].first,cnt=prime[id].second;
    ll pow=1; 
    for(int i=1;i<=cnt;i++) pow*=p;
    ll res=1;
    for(int i=0; i<=cnt;i++) 
    {
        dfs(id+1,k1*res,k2*(pow/res));
        res*=p;
    }
}