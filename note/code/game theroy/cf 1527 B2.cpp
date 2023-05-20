/*
有一个长为n的01串。两个人在一起做游戏，ALICE先手，Bob后手，他们可以从以下两种操作中选一个：
1. 任选某个为0的位置将其变为1，代价为1。
2. 若该01串目前不为回文串，且上一个操作不为操作2的情况下可以将整个01串翻转。

当str全1时，游戏结束，代价少的人获胜，否则平局。 t组数据 ， t, n <= 1e3 


首先考虑抽象，因为需要知道字符串是否回文，
可以将字符串看成对称位置的 00，01，11对 当然如果长度是奇数，再加上中间的0/1
本题只对0操作，因此11可以忽略，因此可以将状态设计成 
dp[00_number][01_number][中间是否有0][上一次操作是否是翻转]   状态之间是有向无环的
一般的题目是考虑状态的 N/P类型，但是本题需要考虑代价
因此定义状态值为当前玩家最多能比另一个玩家少花多少代价到终态
考虑最优策略，就是在所有能到达的状态里面取max
因此可以dp出初态的值，>0则先手胜，<0后手胜，=0平局
状态有1e6个，因此记忆化，最坏 O(1e6)

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10,INF=0x3f3f3f3f;

int n,m,k;
int dp[501][501][2][2];
char s[1010];

void dfs(int a,int b,int c,int d)
{
    if(dp[a][b][c][d]!=INF) return;
    int maxv=-INF;
    if(a)
    {
        dfs(a-1,b+1,c,0);
        maxv=max(maxv,-dp[a-1][b+1][c][0]-1);
    }
    if(b)
    {
        dfs(a,b-1,c,0);
        maxv=max(maxv,-dp[a][b-1][c][0]-1);
        if(!d)
        {
            dfs(a,b,c,1);
            maxv=max(maxv,-dp[a][b][c][1]);  
        }
    }
    if(c)
    {
        dfs(a,b,0,0);
        maxv=max(maxv,-dp[a][b][0][0]-1);
    }
    dp[a][b][c][d]=maxv;
}

void solve()
{
    scanf("%d%s",&n,s);
    int a=0,b=0,c=0;
    for(int i=0,j=n-1;i<j;i++,j--)
        if(s[i]!=s[j]) b++;
        else if(s[i]=='0') a++;
    if(n&1) c+=(s[n/2]-'0')^1;
    dfs(a,b,c,0);
    if(dp[a][b][c][0]>0) puts("ALICE");
    else if(dp[a][b][c][0]<0) puts("BOB");
    else puts("DRAW");
}

int main()
{
    memset(dp,0x3f,sizeof dp);
    dp[0][0][0][0]=0;
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}