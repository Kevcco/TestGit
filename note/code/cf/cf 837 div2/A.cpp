/*
找某两个数使得差值最大，求这样的对数的个数
解：统计最大值的个数和最小值的个数
注意最大值和最小值相等的情况特判
*/

#include <iostream>
#include <algorithm>

using namespace std;

int n;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        int maxa=0,mina=1e5+10;
        int x1=0,x2=0;
        for(int i=0;i<n;i++)
        {
            int x;
            scanf("%d",&x);
            if(x>maxa) maxa=x,x1=1;
            else if(x==maxa)
            {
                x1++;
            }
            if(x<mina) mina=x,x2=1;
            else if(x==mina) x2++;
        }
        long long cnt=0;
        if(maxa==mina) cnt=1ll*n*(n-1);
        else cnt=1ll*x1*x2*2;
        printf("%lld\n",cnt);
    }

    return 0;
}