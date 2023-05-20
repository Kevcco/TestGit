/*
反射问题: 给定 n*m 的一个有边界的点阵 初始小球在(0,0) 向(1,1)方向运动 每次遇到边界都会反弹
如果碰到一个角就会停止
k组询问 每次给定一个点 求小球经过这个点的最早时间 或者始终没有经过 输出-1

如果每次反弹都调整小球 细节非常多 非常麻烦
考虑让小球的方向始终不变 每次碰到边界 将点阵对称过去延伸 而不是调整小球方向
 
   cd|dc
   ab|ba               
   --|--  
   ab|ba
   cd|dc             初始是左下角 一共四种对称的矩阵 其他的都是这四个矩阵平移过去的

    对于在原矩阵是(x,y) 的点 在整个平面的点 是  (x,y),(2n-x,y) (x,2m-y),(2n-x,2m-y) 
    其他的点都是这四个点平移2n,2m得到 因此 在模 2n 2m 意义下是 (x,y) (-x,y) (x,-y) (-x,-y)

小球的坐标在 y=x 直线上 因此对于四种情况 分别求两个同余方程的最小解
t = x mod 2n   t = y mod 2m  将两个方程合并 然后求最小的 t

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;
const long long INF=1e18;

ll n,m,k;
ll T;

ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    ll t=exgcd(b,a%b,y,x);
    y=y-a/b*x;
    return t;
}

ll help(ll a,ll c)
{
    a=(a+n)%n;
    c=(c+m)%m;
    ll x,y,g=exgcd(n,m,x,y);
    if((c-a)%g) return INF;
    ll d=m/g;
    ll t0=(c-a)/g%d*x%d;
    if(t0<0) t0+=d;
    ll res=n*t0+a;
    if(res>T) return INF;
    return res;
}

ll check(int x,int y)
{
    ll res=min({help(x,y),help(x,-y),help(-x,y),help(-x,-y)});
    if(res==INF) return -1;
    return res;
}

void solve()
{
    cin >> n >> m >> k;
    T=n/gcd(n,m)*m; 
    n*=2,m*=2;
    while(k--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%lld\n",check(x,y));
    }
}

int main()
{
    solve();
    return 0;
}