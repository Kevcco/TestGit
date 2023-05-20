/*
康托展开: 将 1 - n 的任一排列 映射到 1 - n! 某个唯一的数上 (其实是字典序的排名) 
逆康托展开: 逆映射 数 -> 排列

应用:(1)将某一排列映射到唯一的数字上,便于记录,如八数码
     (2)单纯求 某一排列 有多少个排列 字典序比他小
     (3)求排在第x位的排列是什么 (逆康托展开) 

康托展开: 数位dp的思考方式 先考虑第一位不同的 
找 2 - n 中比 a1 小的数的个数 b1 那么 res+=b1*(n-1)!
现在将第一位固定为a1 考虑第二位 .. 类推
到 b[] 数组 表示数组右边比这一位的元素小的元素个数  res = sum ( bi * (n-i)! )
(1) O(n^2) 朴素求法
(2) O(nlogn) 树状数组优化

逆康托展开: 类似进制转换 每次 bi = x / (n-i)!  x %= (n-i)!
           得到 b[]数组 再推出 a[] 暴力O(n^2) 
                    平衡树优化 O(nlogn)

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=998244353,N=1e6+10;

int n,m,k;
int a[N],tr[N];
int fact[N];

void init()
{
    fact[0]=fact[1]=1;
    for(int i=2;i<=n;i++) fact[i]=(ll)fact[i-1]*i%mod;
}

// 暴力做法
ll cantor()
{
    ll ans=1;
    for(int i=1;i<n;i++)
    {
        int cnt=0;
        for(int j=i+1;j<=n;j++)
            if(a[j]<a[i]) cnt++;
        ans+=cnt*fact[n-i];
    }
    return ans;
}

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}

int sum(int x)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

//树状数组
int cantor2()
{
    ll ans=1;
    for(int i=n;i>0;i--)
    {
        int cnt=sum(a[i]);
        ans+=(ll)cnt*fact[n-i]%mod;
        add(a[i],1);
        ans%=mod;
    }

    return ans;
}

vector<int> decantor(ll x)
{
    x--;
    vector<int> b(n+1,0),a(n+1,0);
    for(int i=1;i<=n;i++)
    {
        b[i]=x/fact[n-i];
        x%=fact[n-i];
    }

    bool st[N]={0};
    for(int i=1;i<=n;i++)
    {
        int cnt=0;
        int j;
        for(j=1;j<=n;j++)
        {
            if(st[j]) continue;
            if(cnt==b[i]) break;
            cnt++;
        }
        a[i]=j,st[j]=1;
    }

    return a;
}

int main()
{
    cin >> n;
    init();
    return 0;
}