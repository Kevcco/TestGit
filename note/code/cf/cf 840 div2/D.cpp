/*
单峰排列：先单增后单减的排列
给定 1-n n个数 构造长度为n的排列是单峰排列，并且第i个位置的数是x，第j个位置的数是y，（x！=y）i,j,x,y给定
求这样的排列有多少个







排列组合问题
1.x>y 问题可以转化成 x<y  也就是反着看
2.只考虑 x<y
    因为排列是单峰排列，容易想到峰值一定是n,可以以n的位置分类分成n类
    1.n在x左边，由于 x<y 此种情况不可能构造出合法序列
    2.n在y右边  ___ x ___ y ___ n ___
            分成四段，只要向前三段填数，剩下的数只有唯一的顺序填入第四段
            第一段从 <x 的数里选（数不够填说明不能构造出来合法排列）
            第二段从 x<i<y中选  第三段从 y<i<n 中选
            也就是三个组合数相乘
    3.n在 x,y 之间  ___ x ___ n ___ y ___
            先填第一段 1 - x-1 选，选剩下的只能填到第四段最后面
            如果1 - x-1 将第一段和第四段填满还有剩余，没有地方可以填了，证明不存在合法序列
            填好第四段后面的部分，再从 x - y 之间选，如果还填不满返回0
            现在x和y之间还剩下一些数，只能填到第二段里面
            再从 n - y 之间选数填第三段，剩余的填到第二段没填满的地方
            也是三个组合数相乘
3.若y==n 则峰已经确定了，直接算
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=101;

int n,l,r,x,y;
int c[N][N];

int check1(int u)
{
    int s1=l-1,s2=u-l-1,s3=r-u-1,s4=n-r;
    if(x-1<s1) return 0;
    if(y-2<s1+s4) return 0;
    if(n-y-1<s3) return 0;
    if(n-x-2<s2+s3) return 0;
    return (ll)c[n-y-1][s3]*c[x-1][s1]%mod*c[y-x-1][n-r-x+l]%mod;
}

int check2(int u)
{
    int s1=l-1,s2=r-l-1,s3=u-r-1,s4=n-u;
    if(x-1<s1) return 0;
    if(y-x-1<s2) return 0;
    if(n-y-1<s3) return 0;
    return (ll)c[x-1][s1]*c[y-x-1][s2]%mod*c[n-y-1][s3]%mod;
}

int main()
{
    for(int i=1;i<N;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(j==0||j==i) c[i][j]=1;
            else c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
        }
    }
    c[0][0]=1;

    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> l >> r >> x >> y;
        int cnt=0;
        if(x==n)
        {
            if(l!=1&&x-y>=r-l&&y-1>=n-r)
            {
                cnt=(ll)c[x-y-1][r-l-1]*c[y-1][n-r]%mod;
            }
        }
        else if(y==n)
        {
            if(r!=n&&y-x>=r-l&&x-1>=l-1)
            {
                cnt=(ll)c[y-x-1][r-l-1]*c[x-1][l-1]%mod;
            }
        }
        else
        {
            if(x>y)
            {
                l=n-l+1,r=n-r+1;
                swap(l,r);
                swap(x,y);
            }
            for(int i=l+1;i<r;i++) cnt=(check1(i)+cnt)%mod;
            for(int i=r+1;i<n;i++) cnt=(check2(i)+cnt)%mod;
        }
        printf("%d\n",cnt);
    }
    return 0;
}