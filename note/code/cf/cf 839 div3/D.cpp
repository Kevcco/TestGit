/*
给定一个长度为n的数组，1 <= ai <= 1e8    n= 2e5
询问是否存在x，让所有ai替换成abs(ai-x) 使得 数组变成 非严格 升序数组
考虑相邻的两项 ai,ai+1 
if ai < ai+1 考虑x的取值，不难发现要使得数组变成升序序列，x必须 <= ( ai + ai+1 ) / 2   (下取整);
同理 若 ai > ai+1   x >=  ( ai + ai+1 ) / 2   (上取整);
因此可以线性考察数组相邻两项，求出关于x的范围，来确定x是否有解
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2e5+10;

int a[N],n;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i=0;i<n;i++) scanf("%d",a+i);

        int l=0,r=1e9;
        for(int i=1;i<n;i++)
        {
            if(a[i]>a[i-1]) r=min(r,(a[i]+a[i-1])/2);
            else if(a[i]<a[i-1]) l=max(l,(a[i]+a[i-1]-1)/2+1);
            if(l>r) break;
        }
        if(l>r) printf("-1\n");
        else printf("%d\n",l);
    }

    return 0;
}