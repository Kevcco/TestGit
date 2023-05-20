/*
A 和 B 玩 n 轮游戏，每轮各自面对一个boss，血量分别是ai bi, 每轮游戏A先手打boss ai k 点伤害，然后B再打
bi k 点伤害，循环，谁先打死boss 谁获胜 ，问 k 可以取多少，使得 A n 轮游戏都获胜
  n<=2e5   1 <= ai , bi <= n



每轮互不相关，考虑某一轮，ai,bi
如果ai<=bi 因为A先手，不论k取多少，A必然获胜
如果ai>bi 考虑k满足什么条件B获胜。假设进行了x轮，B胜，推得
     (x-1)*k < bi <= x*k
      x*k < ai
==>   bi <= x*k < ai
==>   存在 某一x  使得  bi <= x*k < ai
 反之，如果A获胜，推得
     (x-1)*k < ai <= x*k 
     (x-1)*k < bi
==>   x*k >= ai 
      (x-1)*k <bi
    也就是不存在x 使得  bi <= x*k < ai  

    ===> 如果 存在 x ，使得  bi <= x*k < ai, 则 k 不满足条件，否则，必然满足（充要）
最终，只要预处理出来所有[bi,ai)，（建一个差分数组d[i]，将区间+1,最后前缀和）
再枚举k，然后枚举k的倍数，如果 d[x*k]>0 则k不满足条件，反之加入到答案中

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int a[N],b[N];
int d[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    for(int i=1;i<=n;i++) d[i]=0;

    for(int i=1;i<=n;i++)
    {
        if(a[i]<=b[i]) continue;
        d[b[i]]++,d[a[i]]--;
    }
    for(int i=1;i<=n;i++) d[i]+=d[i-1];
    vector<int> ans;
    for(int i=1;i<=n;i++)
    {
        bool flag=true;
        for(int j=i;j<=n;j+=i)
        {
            if(d[j])
            {
                flag=false;
                break;
            }
        }
        if(flag) ans.push_back(i);
    }
    cout << ans.size() << '\n';
    for(auto i: ans) printf("%d ",i);
    puts("");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}