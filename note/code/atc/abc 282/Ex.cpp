/*
给定长度n的数组a 给定整数s   n<=2e5
数对[l,r] 满足 min[l,r] + sum[l,r] >= s 求满足条件的数对个数


将所有区间按最小值分成n类,最小值是a[1],a[2],...,a[i],...,a[n]  O(n)
对于某一区间,最小值确定,剩下l r两个变量,枚举少的那一侧,sum具有单调性，二分另一侧 (否则会TLE)
似乎总 O(n*nlogn) 但是全局最小值会将区间减半，还有其他的一些性质，最终结论是O(n*logn*logn)

单调队列求 l[i] 和 r[i] 时，l[i]求i左边第一个小于a[i]的数  r[i]求i右边第一个小于等于i的数
防止重复计算

类似: cf 845 F  max[l,r]^sumxor[l,r] 
同样的框架 枚举少的那一侧 可持久化trie查询另一侧的区间

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
ll a[N],b[N],s,res;
int l[N],r[N];

void solve()
{
    cin >> n >> s;
    for(int i=1;i<=n;i++) scanf("%lld",a+i);
    for(int i=1;i<=n;i++) scanf("%lld",b+i);
    for(int i=1;i<=n;i++) b[i]+=b[i-1];

    stack<pair<ll,int>> st;
    st.push({-1,0});
    for(int i=1;i<=n;i++)
    {
        while(st.top().first>=a[i]) st.pop();
        l[i]=st.top().second;
        st.push({a[i],i});
    }
    stack<pair<ll,int>> st2;
    st2.push({-1,n+1});
    for(int i=n;i>0;i--)
    {
        while(st2.top().first>a[i]) st2.pop();
        r[i]=st2.top().second;
        st2.push({a[i],i});
    }

    for(int i=1;i<=n;i++)
    {
        ll t=s-a[i];
        int x=l[i]+1,y=r[i]-1;
        int len1=i-x+1,len2=y-i+1;
        if(len1<len2)
        {
            for(int j=x-1;j<i;j++)
            {
                res+=upper_bound(b+i,b+y+1,t+b[j])-(b+i);
            }
        }
        else
        {
            for(int j=i;j<=y;j++)
            {
                res+=b+i-lower_bound(b+x-1,b+i,b[j]-t);
            }
        }
    }
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}