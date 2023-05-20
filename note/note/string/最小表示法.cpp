/*
将一个长为n的字符串s首尾相连形成环  在任意位置断开 我们能得到字符串t  t与s循环同构
在这n个与s循环同构的字符串里 字典序最小的 被称作 s 的最小表示
求一个字符串的最小表示

(1) 暴力 O(N^2)
(2) 二分 + 字符串哈希  在比较两个字符串大小时 二分前缀相等的最大长度 然后比较后一位
(3) 双指针 i j 表示两个可能的最小字符串的头 先求出 两个字符串的最长的相同前缀长度k
    然后再比较下一位 s[i+k] s[j+k]  如果 s[j+k] > s[i+k] 那么 j - j+k 这一段一定不可能是最小的
    因为 s[j+x] > s[i+x]  x <= k 所以 j 直接跳到 j+k+1
    如果 i==j 随便让某一个指针向后移1位
    最后 任意指针 > n 算法结束 最小表示就是 < n 的那个指针所指的位置

应用
(1) 判断两个字符串是否是循环同构 ： 即判断两个字符串的最小表示是否一样

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;

int n;
char s[N*2];

void getmin()
{
    for(int i=1;i<=n;i++) s[i+n]=s[i];
    int i=1,j=2;
    while(j<=n)
    {
        int k=0;
        while(k<n&&s[i+k]==s[j+k]) k++;
        if(s[i+k]>s[j+k]) i+=k+1;
        else j+=k+1;
        if(i==j) j++;
        if(i>j) swap(i,j);
    }

    for(int l=i;l<=i+n-1;l++) printf("%c",s[l]);
}

void solve()
{
    scanf("%d%s",&n,s+1);
    getmin();
}

int main()
{
    solve();
    return 0;
}