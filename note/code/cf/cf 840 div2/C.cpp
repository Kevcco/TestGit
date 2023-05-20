/*
给定长为n(2 <= n <= 2e5) 的数组
规定如下操作：选择任意i，j，i<j 让数组中 [ai --- aj] 所有元素全部变成 |ai - aj|
询问可以对数组操作任意次，求 数组和的最大值








发现性质： 对同一段区间操作两次后，区间元素全部变成0
|ai - aj|执行任意次，所有元素 最大也不会超过 原本数组的最大值

考虑将数组元素全部变成原数组最大元素

如果最大元素在端点处，将另一端先操作成0，再操作整个区间即可
如果最大元素不在端点,可以先将一端变成0，再操作这一端到最大元素的区间，
使得最大元素移动到端点，就变成第一种情况
最终结论：max = maxv * n

注意对于n<=3，如果最大元素不在端点，则某一端不存在两个元素，无法操作成0
需要单独讨论

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=2e5+10;

int a[N],n;

ll hhh()
{
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    if(n==2)
    {
        ll res1=(ll)a[1]+a[2];
        ll res2=(ll)abs(a[1]-a[2])*2;
        return max(res1,res2);
    }
    else
    {
        ll res=(ll)a[1]+a[2]+a[3];
        res=max(res,abs((ll)a[1]-a[3])*3);
        res=max(res,abs((ll)a[1]-a[2])*3);
        res=max(res,abs((ll)a[2]-a[3])*3);
        res=max(res,(ll)a[1]*3);
        res=max(res,(ll)a[3]*3);
        return res;
    }
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        ll res=0;
        if(n<=3) res=hhh();
        else
        {
            int m=0;
            for(int i=1;i<=n;i++)
            {
                scanf("%d",a+i);
                m=max(m,a[i]);
            }
            res=(ll)m*n;
        }
        printf("%lld\n",res);
    }
    return 0;
}