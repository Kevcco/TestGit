/*
给定 n  n<=2e5
求 pair[i,j]
满足  1<=i,j<=n and  i*j是平方数
的对数




考虑定 i 求 j 对于 一个确定的 i 来说 要使 i*j 是平方数
考虑对平方数分解质因数 必然满足所有的底数的指数都是偶数
因此考虑对 i 分解质因数 将指数为奇数的质因子相乘 得到了最小的j 也就是将指数为奇数的补成偶数
现在考虑对 1 - n 分解质因数 每次得到一个对应的j map[j]++  类似于一个数的特征值

考虑答案 对于一个 i 而言 他如果归属map[j,cnt] 那么pair[i,x] 共有cnt个 因为如果两个数同属j
那么两个数相乘 质因子的指数是奇数的会互补 变成偶数 因此是平方数 
因此答案就是遍历map  每次 res+=cnt*cnt  

*/
#include <bits/stdc++.h>

#define YES puts("YES")
#define Yes puts("Yes")
#define NO puts("NO")
#define No puts("No")

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
map<int,int> hh;

void solve()
{
    ll res=0;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        m=i;
        ll ans=1;
        for(int j=2;j*j<=m;j++)
        {
            if(m%j==0)
            {
                int cnt=0;
                while(m%j==0) cnt++,m/=j;
                if(cnt&1) ans*=j;
            }
        }
        if(m>1) ans*=m;
        hh[ans]++;
    }

    for(auto x : hh)
    {
        res+=(ll)x.second*x.second;
    }

    cout << res;
}

int main()
{
    solve();
    return 0;
}