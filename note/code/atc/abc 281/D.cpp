/*
给定长度为 n 的数组，在数组中选 k 个数相加组成新的元素，求所有组成的新元素中 d 的最大倍数
  n,k,d <= 100




选k个数 -> 01背包  价值为a[i],体积为1
要求的是d的最大倍数，两维肯定不够，再加一维表示 mod d 的余数

f[i][j][k] 前i个物品，体积是j， mod d = k 的最大值
答案就是f[n][k][0]
f[i][j][k] = max( f[i-1][j][k] , f[i-1][j-1][(k-w%d+d)%d]+w)

第二项是选w这个数，要使余数为k，即 
(x+w)%d=k 
( x + w%d ) %d = k
x = (k-w%d+d) %d

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=110;

int n,K,d;
ll f[N][N];

int main()
{
    cin >> n >> K >> d;
    memset(f,-0x3f,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        int w;
        scanf("%d",&w);
        int t=w%d;
        for(int j=K;j>0;j--)
        {
            for(int k=0;k<d;k++)
            {
                f[j][k]=max(f[j][k],f[j-1][(k-t+d)%d]+w);
            }
        }
    }
    if(f[K][0]<0)f[K][0]=-1;
    cout << f[K][0];

    return 0;
}
