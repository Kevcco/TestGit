/*
判断分数是否是无限循环小数

将分数约分最简  如果分母质因子只含有 2 和 5 则不是无限循环小数 反之必然是
假设分母m是2^a * 5^b
 if a==b m = 10^x 必然能写成小数
 if a<b 分子分母同 * 2^(b-a)  分母化成 10^x
 a>b 同理

具体做法 a/b: 
1. 求 gcd(a,b)
2. b/=gcd 用 2 5 除 b 判断 b是否是 1

NiuKe 情人节 G

*/
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];

int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

//判断 分数 是否是 无限不循环小数
bool judge(int a,int b)
{
    int t=gcd(a,b);
    b/=t;
    while(b%2==0) b/=2;
    while(b%5==0) b/=5;
    if(b==1) return true;
    return false;
}

int main()
{
    return 0;
}