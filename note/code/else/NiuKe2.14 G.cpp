/*
给定 长度 n 数组  n,ai <= 2e5
求有多少对 (i,j) 满足  ai / aj 是 无限循环小数



考虑求不是无限循环小数的对数 即 分子分母约分后 分母的质因子只有 2 5
对所有 ai 循环除2 除 5 剩余 x  hh[x]++

考虑枚举所有 x 作分母 O(n) 有 hh[x]个 考虑什么样的分子满足
现在分母除2^a 5^b 剩 x  必须用分子消掉 x 则分子 除2 除5 剩的 y 必须是 x 的倍数 O(n/i)
 cnt += hh[x]*hh[y];
 O(n/1 + n/2 + ... + n/n) = O(nlogn)
 res = n * n - res

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        while(x%2==0) x/=2;
        while(x%5==0) x/=5;
        p[x]++;
    }

    ll res=0;
    for(int i=1;i<N;i++)
        for(int j=i;j<N;j+=i)
            res+=(ll)p[i]*p[j];

    res=(ll)n*n-res;
    cout << res;
}

int main()
{
    solve();
    return 0;
}