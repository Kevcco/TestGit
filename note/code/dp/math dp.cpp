/*
给定 n m  0 < n < m
有如下两种操作
1.当前数 * 2
2.当前数 - 1
询问将 n 操作成 m 的最少操作次数



考虑贪心 将 a 变成 b (a<b)  因为只有 *2 才能变大 所以 如果b是奇数 那么他的上一步一定是 -1 b变成偶数
    考虑 a 变 b (b是偶数,a >= b/2)  考虑最后几步 要么是 a*2 再减 要么是 a 先减 再*2 （也有可能直接a*2=b) 
    a*2-x=b  (a-x)*2=b
   x=a*2-b    x=(a*2-b)/2   x代表使用操作2的次数 使用操作1都是1次 明显 后一种永远不输前一种
现在考虑逆向 m 变 n   如果m是奇数 先加1变成偶数
    如果m先加任意次 再/2 那么一定不如 先/2 再加 
    因此 m/=2 一定是最优
    然后循环执行此过程 直至 m<=n 然后再加 n-m 便完成 m -> n

如果给两个操作各加上权值 x y 也不影响贪心的思路


如果变成三种操作
1.当前数 * 2
1.当前数 - 1
1.当前数 + 1

贪心性质依然满足: 先加再/2 一定不如 先/2 再加
dp：考虑 f[i] 为 0 -> i 的最小步数  
        如果 i是偶数 他一定不会是从 i+1 转移过来 因为 先 *2 再 - 一定不如 先 - 再 *2
        所以f[i] 可以是从 f[i/2] 转移 也可以是 f[i-1] 转移
        如果i是奇数 可以从 f[i-1] 转移 也可以从 f[(i+1)/2] 转移 *2 -1 
        换种说法 由  n -> i 最后一步要么是 +1 要么 -1  如果是 +1 则变成  f[i-1] 
        如果是 - 由 x*2 变成 i+1 或者 i+3 ,i+5 再减 那么一定不如 x先减 再*2 变成 i+1 再减
        也就是说 一定是 x * 2 - 1 = i 那么 f[i]便是由 f[(i+1)/2] 转移
        因此满足dp特性 可以递推
如果加上权重依然可以dp 只不过每一步都要加上权重

cf 295 B
acwing 1100
acwing 4805

*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=1e5+10;

int n,m;
int f[N];

void solve()
{
    cin >> n >> m;
    if(n>=m)
    {
        printf("%d\n",n-m);
        return;
    }
    
    memset(f,0x3f,sizeof f);
    for(int i=0;i<=n;i++) f[i]=n-i;
    for(int i=n+1;i<=m;i++)
    {
        if(i&1)
        {
            f[i]=min(f[i-1]+1,f[(i+1)/2]+2);
        }
        else f[i]=min(f[i-1],f[i/2])+1;
    }
    
    printf("%d\n",f[m]);
}

int main()
{
    solve();
    return 0;
}