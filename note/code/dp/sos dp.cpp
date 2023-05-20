/*
sum over subsets dp 子集和dp
a[i] <= m
给定 a[i] 解决 f[mask]=sum(a[i]) 的求解 （其中 i是所有mask的子集 即 i&mask == i） 
例如 mask = 1010  mask所有子集 = 0000,0010,1000,1010

定义 dp[i][mask] 代表只有二进制低i位和mask不同的 sum(a[i])
    if( mask>>i &1 == 0) dp[i][mask] = dp[i-1][mask]
    else dp[i][mask] = dp[i-1][mask] + dp[i-1][mask^(1<<i)]

    1000 1 0101 dp[5][mask] = dp[4][1000 1 0101] + dp[4][1000 0 0101]


优化空间 注意循环顺序 mask 从大到小 O(mlogm)
模板

    for(int i=0;i<M;i++) dp[i]=a[i];
    for(int i=0;i<N;i++)
        for(int j=M-1;j>=0;j--)
            if(j>>i&1) dp[j]+=dp[j^(1<<i)];



1. 牛客 上理同步赛 G https://ac.nowcoder.com/acm/contest/52244/G
    给定数组 n <= 1e5 ai <= 2e5 求 满足 ai^aj = ai+aj 的<i,j>对数
    对于 ai aj 必须满足  ai&aj == 0 即 寻找 dp[~ai] 

2. cf round 112 E
    给定数组 询问 任意i ai&aj == 0 aj是否存在
    对于ai 找dp[~ai] dp[mask]直接存子集中的任意一个存在的元素即可
    询问 ai&ai == 0 这样的 <i,j>对数
    枚举 ai 直接 + dp[~ai]

3. cf 1208 F    
    给定数组 求所有  ai | （aj & ak) (其中 i<j<k)  的最大值
    倒序 插入和查询 
    dp[i][mask] 表示 只有与mask的低i位不同的子集的个数 
    这里的子集是 如果mask是1,子集必须为1 mask是0 子集是 0或1

    查询: 要求最大值 一开始mask=0 所以贪心地从高位到低位 如果 ai这一位是1 那么答案加上
          否则如果 ai这一位是0 查询 dp[20][mask|(1<<i)] 是否大于等于2 如果是 答案就加上 
          并且mask这一位也更新成1

    插入: 低位到高位插入 dp[i][mask]++ update(i+1,mask) if(mask>>i&1) update(i,mask^(1<<i))
         因为查询时只要求有2个 因此如果dp[i][mask]>=2 直接return剪枝 因此插入的总时间复杂度不超过2*(1<<20)




集合枚举:
(1) 枚举所有状态的非空子集    O(3^n)
    for(int i = 1; i < 1<<n; i++)
        for(int j = i; j; j = (j-1)&i)
(2) 枚举超集    O(3^n)
    for(int  i = 1; i < 1<<n; i++)
        for(int j = i; j < 1<<n ; j = (j+1)|i)
*/

#include <bits/stdc++.h>

using namespace std;

const int mod=1e9+7,N=1e6+10,M=1<<21;

int n,m,k,p[N];
int dp[21][M];

void insert(int mask,int u)
{
    if(u>20) return;
    if(dp[u][mask]>1) return;
    dp[u][mask]++;
    insert(mask,u+1);
    if(mask>>u&1) insert(mask^(1<<u),u);
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    int ans=0;

    for(int i=n;i>=1;i--)
    {
        int res=0;
        int mask=0;
        for(int j=20;j>=0;j--)
        {
            if(p[i]>>j&1) res+=1<<j;
            else if(dp[20][mask|(1<<j)]>1)
                mask|=1<<j,res+=1<<j;
        }

        insert(p[i],0);

        if(i<n-1) ans=max(ans,res);
    }

    cout << ans << endl;
}
