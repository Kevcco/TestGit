/*
给定长度为 n 的数组 给定 k 
每次可对长度为k的连续区间内的每一个元素 + c  c任取
给出q个询问
对于每个询问 [l,r] 回答 子序列 [l,r] 能否通过任意次操作 使 元素全变为 0
 n,q <=2e5
 k <= min(10,n)




考虑差分 每次操作相当于 c[i]+=c, c[i+k]-=c
观察可以发现 对差分数组按 % k 分成 k 类元素 
每类 %k 相同的元素 相加求和 无论怎么操作 sum 永远不变
考虑子数组  a[l,r]  差分数组  c[l,r+1] 将  a[l,r] 全变成0 相当于 c[l+1,r] 全变成0 并且 c[l] == -c[l-1] 
考虑将 差分数组 mod k分成 k 类  那么每一类和是固定的  
如果某一类 和是0 那么一定可以将这一类的所有元素全部变成0
如果和不是0 那么一定不可能将所有元素全变成0
因此 问题 等价于 判断这k类的和是否全为 0  使用前缀和即可做到 每次询问是 O(k) 的
注意特判 包含 c[l] 的那一类 sum必须 = -c[l-1] 因为要使 c[l]= -c[l-1] 其他的都是0
还要特判 包含 c[r+1] 的那一类 因为对 c[r+1] 没有要求 所以不管和是多少 
都能通过c[r+1] 调节使得这一类的其他元素满足条件
*/


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N],c[N];
ll s[N];

void solve()
{
    cin >> n >> k;
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    for(int i=1;i<=n;i++) c[i]=p[i]-p[i-1];
    for(int i=1;i<=n;i++)
    {
        s[i]=c[i];
        if(i>k) s[i]+=s[i-k];
    }

    cin >> m;
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        bool ok=true;
        vector<ll> b(k,0);
        for(int i=l-1,j=0;i&&j<k;i--,j++)
            b[i%k]-=s[i];
        for(int i=r+1,j=0;j<k;i--,j++)
            b[i%k]+=s[i];

        for(int i=0;i<k;i++)
        {
            if(i==(r+1)%k) continue;
            if(i==l%k)
            {
                if(b[i]!=-p[l-1])
                {
                    ok=0;
                    break;
                }
            }
            else
            {
                if(b[i])
                {
                    ok=0;
                    break;
                }
            }
        }

        if(ok) puts("Yes");
        else puts("No");
    }
}

int main()
{
    solve();
    return 0;
}