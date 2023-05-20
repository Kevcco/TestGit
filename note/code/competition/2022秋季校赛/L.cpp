/*
    空瓶换酒：k个空瓶换一瓶酒，可以借一个空瓶，但是借的得还
    公式：n/(k-1)
    将酒瓶拆成两部分 瓶+酒  ka=a+b -> (k-1)a=1b
    也就是k-1空瓶可以换一个酒，因为k个瓶换完后，喝掉，又增加一个瓶，折合相当于k-1瓶换1酒
    但是存在只有k-1个瓶，无法操作上述过程变成只消耗 k-1 个瓶
    但是题目有条件，可以借一瓶，最后顺利推出 res = n / (k - 1)
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=998244353,N=510;

ll n,m,k;

void solve()
{
    scanf("%lld%lld",&n,&k);
    printf("%lld\n",n/(k-1));
    return;
}

int main()
{
    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}