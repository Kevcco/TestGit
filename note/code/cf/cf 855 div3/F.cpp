/*
给定 n 个由小写字母组成的字符串  n <= 2e5
寻找数对 <i,j> 1 <= i <= j <= n 的个数
使得new string = si + sj
new string 满足
(1)恰好包含25种字母
(2)每种字母的个数都是奇数


异或哈希
统计每个字符串中26种字母的个数 cnt[26] 并且给出二进制 26位数 mask 其中 0代表cnt是偶数 1代表奇数
考虑 某一字符串为 sj 寻找 si 
枚举cnt[] 如果cnt[i]==0 考虑将这一种字母i作为缺的字母
 其余25种必须是奇数 出现次数是奇数也就保证了这25种字母的存在 (最小的奇数是1)
 如何保证 字母 i 不存在 ? 因为出现 0次和2次都被归为 0 
 因此需要开26个map 每一个map存的都是缺某一种的字符串
这样 cnt[i]==0
直接查询 map[i] 寻找map[i][target[i] ^ mask]
target[i] 为第i位为0其他位都是1的数

开26个map的异或哈希

不限制种数 只考虑字母出现次数为偶数 直接单个map查询

限制出现25个字母且次数为奇数 
    单纯的指定某一位异或起来为0不可行 因为包含这一位为 0 2 两种情况
    所以开26个map 代表这一位不存在 其他位为 0或1 （0包含0和2两种） 


不限制字母种数 只要求出现字母的次数都为奇数 ? 
限制出现25个字母且次数都为偶数 ？ 
似乎不太好扩展
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n,target[26];
map<int,int> hh[26];
ll res;

void solve()
{

    for(int i=0;i<26;i++) target[i]=((1<<26)-1)^(1<<i);

    cin >> n;
    for(int q=1;q<=n;q++)
    {

        string s;
        cin >> s;

        int cnt[26]={0},mask=0;
        for(auto c : s) cnt[c-'a']++;
        for(int i=0;i<26;i++)
            if(cnt[i]&1) mask+=1<<i;

        for(int i=0;i<26;i++)
        {
            if(!cnt[i]&&hh[i].count(target[i]^mask))
                res+=hh[i][target[i]^mask];
        }

        for(int i=0;i<26;i++)
            if(!cnt[i]) hh[i][mask]++;

    }

    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}