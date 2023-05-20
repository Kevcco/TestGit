/*
最长回文子串问题
(1) 枚举中点 二分+字符串哈希  O(nlogn)
(2) manacher O(n)

mamacher
1.首先插入无关字符 避免奇偶分类讨论 全部变成奇数情况 同时在首尾插入一个不可能和其他位置相等的哨兵 避免判边界
2.记录一个 p[i] 表示以i为中点的最长回文半径(包括中点)
3.从前往后枚举中点 i 维护一个[L,R] 区间 表示 < i 里 回文区间的R最大的区间 也就是 [m-p[m]+1,m+p[m]-1]
4.考虑求 p[i]
  (1) 如果 R < i 直接暴力求 p[i]
  (2) 如果 R >= i  求点i在区间[L,R] 里的对称点 k = 2m-i
       若 Lk > L 那么 p[i] = p[k]
       否则 Lk <= L 那么 p[i] 至少 = p[k] 然后暴力扩展
  求完 p[i] 别忘记更新[L,R]
  最后 res = max(p[i]) - 1

每次暴力扩展时 R一定会增大 而R最多增大 O(n)  因此总时间 O(n)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=11e6+10;

int n,m,k;
int p[N*2];
char s[N],t[N*2];

void manacher()
{
    t[0]='@';
    t[++m]='$';
    for(int i=1;i<=n;i++) t[++m]=s[i],t[++m]='$';
    t[m+1]='~';
    int M=0,R=0;
    for(int i=1;i<=m;i++)
    {
        if(i>R) p[i]=1;
        else p[i]=min(p[2*M-i],R-i+1);
        while(t[i-p[i]]==t[i+p[i]]) p[i]++;
        if(i+p[i]-1>R) M=i,R=i+p[i]-1;
    }
    int res=0;
    for(int i=1;i<=m;i++) res=max(res,p[i]);
    printf("%d\n",res-1); 
}

void solve()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    manacher();
}

int main()
{
    solve();
    return 0;
}