/*
异或运算性质：
1.交换律：a^b = b^a
2.a^a=0,a^0=a
3.可移项：a^b=c  ->  a=b^c  推：a^b=c,a^b^c=0 a=b^c,b=a^c,c=a^b;

可移项性使得异或前缀存在且成立
a[l]^a[l+1]^...^a[r]= s[l-1] ^ s[r]



题意：长度为n的数组，找出数组的连续子序列且子序列的所有项的异或值不是完全平方数（包括0） ，这样的子序列个数
     n<=2e5

求子序列异或值：异或前缀

求异或值不是完全平方数  ->  总的子序列个数 - 是完全平方数的子序列个数

求子序列异或值是完全平方数：枚举完全平方数x，x^s=0;

假设a[l]^...^a[r]=x,如果x是完全平方数  s[l-1]^s[r]=x,s[r]^x=s[l-1]；

也就是说，只要枚举长度1-n的前缀（每次考虑以i结尾的子序列），
如果s[i]^x = 0 代表 1-i 这个子序列满足
如果s[i]^x = k ,其中 k是前面出现过的s[i]值，令其为s[j],则代表 j+1 - i 是满足的子序列
只要用hash表统计每个s[i]出现的值和次数就行

完全平方数需要枚举到 2*n  因为一堆 <=n 的数异或起来 值 < 2*n      100000 -> 111111边界情况



1.计数：求异或和为x的子序列个数 ：思路一样，处理前缀，hash表记录出现的次数
2.查询：给出m组[l,r]区间询问能否异或出x
        查询hash[sum^x],如果存在，记录一下sum^x出现的最新位置，开一个l[N]数组
        l[N]代表每个r(以r为后缀的序列)最近的l，但不一定是区间内最近的l
        然后每次要更新当前sum值的位置
        可以遍历一遍l[N]数组，维护一个maxl代表 1 - i-1 中最大的l，if maxv>l[i],那么必然要更新l[i]
        因为 maxv -- r 比 l[r]--r 更短，并且是l[r]-r中最短的了
        现在可以直接查询l[r] 判断 l是否<=l[r] 

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int cnt[2*N],n;

void solve()
{
    cin >> n;
    memset(cnt,0,sizeof cnt);
    cnt[0]=1;
    ll ans=0;
    int s=0;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        s^=x;
        for(int j=0;j*j<=2*n;j++)
        {
            ans+=cnt[s^(j*j)];
        }
        cnt[s]++;
    }
    ll res=(ll)n*(n+1)/2;
    res-=ans;
    printf("%lld\n",res);
    return;
}

int main()
{
    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}
